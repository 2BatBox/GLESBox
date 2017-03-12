#ifndef GBOX_APPLICATION_H_
#define GBOX_APPLICATION_H_

#include <string.h>
#include <sys/time.h>
#include <assert.h>

#include "Environment.h"
#include "utils/eglutils.h"
#include "../log/Log.h"

namespace gbox {

	class Application {
		Environment* env;
		EGLRenderContext renderContext;

	public:

		Application(Environment* env) :
				env(env) {
			memset(&renderContext, 0, sizeof(renderContext));
		}

		virtual ~Application() = default;

		bool createContext() {
			EGLNativeWindowType* nativeWindow = env->getNativeWindow();
			if (nativeWindow == nullptr) {
				LOGE("Cannot get a native window");
				return false;
			}

			if (!initEGLContext(nativeWindow)) {
				LOGE("Can't initialize EGL");
				return false;
			}

			return env->createContext();
		}

		bool destroyContext() {
			return env->destroyContext();
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
				deltatime = (float) (t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
				t1 = t2;

				if (callBackHolder->onUpdate != nullptr) {
					callBackHolder->onUpdate(deltatime);
				}
				if (callBackHolder->onDraw != nullptr) {
					callBackHolder->onDraw();
				}

				eglSwapBuffers(renderContext.eglDisplay, renderContext.eglSurface);

				totaltime += deltatime;
				frames++;
				if (totaltime > 2.0f) {
//					LOGI("FPS=%3.4f", frames / totaltime);
					totaltime -= 2.0f;
					frames = 0;
				}
			}
		}

		bool initEGLContext(EGLNativeWindowType* nativeWindow) {

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
			if (renderContext.eglDisplay == EGL_NO_DISPLAY || eglutils::eglChechError()) {
				LOGE("Unable to open connection to local windowing system");
				return false;
			}

			if (!eglInitialize(renderContext.eglDisplay, &renderContext.eglMajorVersion, &renderContext.eglMinorVersion)
					|| eglutils::eglChechError()) {
				LOGE("Unable to initialize EGL");
				return false;
			}

			if (!eglChooseConfig(renderContext.eglDisplay, configAttrs, &renderContext.eglConfig, 1, &size) || size != 1
					|| eglutils::eglChechError()) {
				LOGE("Unable to choose config");
				return false;
			}

			renderContext.eglSurface = eglCreateWindowSurface(renderContext.eglDisplay, renderContext.eglConfig,
					*nativeWindow, windowAttrs);
			if (renderContext.eglSurface == EGL_NO_SURFACE || eglutils::eglChechError()) {
				LOGE("Can't create window surface");
				return false;
			}

			renderContext.eglContext = eglCreateContext(renderContext.eglDisplay, renderContext.eglConfig,
			EGL_NO_CONTEXT, contextAttrs);
			if (renderContext.eglContext == EGL_NO_CONTEXT || eglutils::eglChechError()) {
				LOGE("Can't create opengl es context");
				return false;
			}

			if (!eglMakeCurrent(renderContext.eglDisplay, renderContext.eglSurface, renderContext.eglSurface,
					renderContext.eglContext) || eglutils::eglChechError()) {
				LOGE("Can't set opengl es context");
				return false;
			}
			return true;
		}

	};

} /* namespace gbox */

#endif /* GBOX_APPLICATION_H_ */
