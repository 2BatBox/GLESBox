#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <string.h>
#include <sys/time.h>

#include "utils/EGLUtils.h"
#include "utils/X11Utils.h"

class Application {

public:

	struct CallBackHolder {
		void (*configureNotify)(int width, int height);
		void (*buttonPress)(unsigned button, int x, int y);
		void (*buttonRelease)(unsigned button, int x, int y);
		void (*motionNotify)(int x, int y);
		void (*destroyNotify)();
		void (*update)(float deltaTime);
		void (*draw)();
	};

	Application(){
		memset(&callBackHolder, 0, sizeof(callBackHolder));
		memset(&x11Context, 0, sizeof(x11Context));
		memset(&renderContext, 0, sizeof(renderContext));
	}

	CallBackHolder& getCallBackHolder(){
		return callBackHolder;
	}

	bool init(const char *title, int width, int height){
		if (!X11Utils::initX11Context(x11Context, title, width, height)){
			LOGE("Can't initialize X11");
			return false;
		}

		if (!EGLUtils::initRenderContext(renderContext, x11Context.window)) {
			LOGE("Can't initialize EGL");
			return false;
		}
//		EGLUtils::info(renderContext);

		if(callBackHolder.configureNotify != nullptr){
			callBackHolder.configureNotify(x11Context.width, x11Context.height);
		}

		return true;
	}

	void mainLoop(){
		struct timeval t1, t2;
		struct timezone tz;
		float deltatime;
		float totaltime = 0.0f;
		unsigned int frames = 0;

		gettimeofday(&t1, &tz);

		while (handleEvents()) {
			gettimeofday(&t2, &tz);
			deltatime = (float) (t2.tv_sec - t1.tv_sec
					+ (t2.tv_usec - t1.tv_usec) * 1e-6);
			t1 = t2;

			if(callBackHolder.update != nullptr){
				callBackHolder.update(deltatime);
			}
			if(callBackHolder.draw != nullptr){
				callBackHolder.draw();
			}

			eglSwapBuffers(renderContext.eglDisplay, renderContext.eglSurface);

			totaltime += deltatime;
			frames++;
			if (totaltime > 2.0f) {
				printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n",
						frames, totaltime, frames / totaltime);
				totaltime -= 2.0f;
				frames = 0;
			}
		}
	}

	virtual ~Application(){

	}

private:
	CallBackHolder callBackHolder;
	X11Context x11Context;
	EGLRenderContext renderContext;

	bool handleEvents() {
		XEvent event;

		while (XPending(x11Context.display)) {

			XNextEvent(x11Context.display, &event);

			switch (event.type) {
			case ButtonPress:
				if (callBackHolder.buttonPress != nullptr) {
					callBackHolder.buttonPress(event.xbutton.button,event.xbutton.x, event.xbutton.y);
				}
				break;

			case ButtonRelease:
				if (callBackHolder.buttonRelease != nullptr) {
					callBackHolder.buttonRelease(event.xbutton.button,event.xbutton.x, event.xbutton.y);
				}
				break;

			case MotionNotify:
				if (callBackHolder.motionNotify != nullptr) {
					callBackHolder.motionNotify(event.xmotion.x, event.xmotion.y);
				}
				break;

			case ConfigureNotify:
				if (event.xconfigure.width != x11Context.width || event.xconfigure.height != x11Context.height) {
					if(callBackHolder.configureNotify != nullptr){
						callBackHolder.configureNotify(event.xconfigure.width, event.xconfigure.height);
					}
					x11Context.width = event.xconfigure.width;
					x11Context.height = event.xconfigure.height;
				}
				break;

			case ClientMessage:
				if(callBackHolder.destroyNotify != nullptr){
					callBackHolder.destroyNotify();
				}
				return false;
			}

		}
		return true;
	}

};

#endif /* APPLICATION_H_ */
