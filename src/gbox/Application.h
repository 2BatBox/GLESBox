#ifndef GBOX_APPLICATION_H_
#define GBOX_APPLICATION_H_

#include <string.h>
#include <sys/time.h>
#include <assert.h>

#include "Environment.h"
#include "utils/EGLUtils.h"
#include "../log/Log.h"

namespace gbox {

class Application {
	Environment* env;
	EGLRenderContext renderContext;

public:

	Application(Environment* env) : env(env) {
		memset(&renderContext, 0, sizeof(renderContext));
	}

	virtual ~Application() = default;

	bool init() {
		EGLNativeWindowType* nativeWindow = env->getNativeWindow();

		if(nativeWindow == nullptr){
			LOGE("Cannot get a native window");
			return false;
		}

		if (!initRenderContext(nativeWindow)) {
			LOGE("Can't initialize EGL");
			return false;
		}

		env->createNotify();
		return true;
	}

	void mainLoop() {
		struct timeval t1, t2;
		struct timezone tz;
		float deltatime;
		float totaltime = 0.0f;
		unsigned int frames = 0;

		gettimeofday(&t1, &tz);

		CallBackHolder* callBackHolder = env->getCallBackHolder();

		while (env->handleEvents()) {
			gettimeofday(&t2, &tz);
			deltatime = (float) (t2.tv_sec - t1.tv_sec
					+ (t2.tv_usec - t1.tv_usec) * 1e-6);
			t1 = t2;

			if (callBackHolder->update != nullptr) {
				callBackHolder->update(deltatime);
			}
			if (callBackHolder->draw != nullptr) {
				callBackHolder->draw();
			}

			eglSwapBuffers(renderContext.eglDisplay, renderContext.eglSurface);

			totaltime += deltatime;
			frames++;
			if (totaltime > 2.0f) {
				LOGI("%4d frames rendered in %1.4f seconds -> FPS=%3.4f",
						frames, totaltime, frames / totaltime);
				totaltime -= 2.0f;
				frames = 0;
			}
		}
	}

	bool initRenderContext(EGLNativeWindowType* nativeWindow) {

		EGLint configAttrs[] = {
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_DEPTH_SIZE, 1,
		EGL_NONE };

		EGLint windowAttrs[] = {
		EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
		EGL_NONE };

		EGLint contextAttrs[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE };

		EGLint size;

		renderContext.eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (renderContext.eglDisplay == EGL_NO_DISPLAY) {
			EGLUtils::eglChechError();
			LOGE("Unable to open connection to local windowing system");
			return false;
		}

		if (!eglInitialize(renderContext.eglDisplay,
				&renderContext.eglMajorVersion,
				&renderContext.eglMinorVersion)) {
			EGLUtils::eglChechError();
			LOGE("Unable to initialize EGL");
			return false;
		}

		if (!eglChooseConfig(renderContext.eglDisplay, configAttrs,
				&renderContext.eglConfig, 1, &size) || size != 1) {
			EGLUtils::eglChechError();
			LOGE("Unable to choose config");
			return false;
		}

		renderContext.eglSurface = eglCreateWindowSurface(
				renderContext.eglDisplay, renderContext.eglConfig,
				*nativeWindow, windowAttrs);
		if (renderContext.eglSurface == EGL_NO_SURFACE) {
			EGLUtils::eglChechError();
			LOGE("Can't create window surface");
			return false;
		}

		renderContext.eglContext = eglCreateContext(renderContext.eglDisplay,
				renderContext.eglConfig,
				EGL_NO_CONTEXT, contextAttrs);
		if (renderContext.eglContext == EGL_NO_CONTEXT) {
			EGLUtils::eglChechError();
			LOGE("Can't create opengl es context");
			return false;
		}

		if (!eglMakeCurrent(renderContext.eglDisplay, renderContext.eglSurface,
				renderContext.eglSurface, renderContext.eglContext)) {
			EGLUtils::eglChechError();
			LOGE("Can't set opengl es context");
			return false;
		}
		return true;
	}

};

} /* namespace gbox */

#endif /* GBOX_APPLICATION_H_ */
