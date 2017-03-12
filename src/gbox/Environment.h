#ifndef GBOX_ENVIRONMENT_H_
#define GBOX_ENVIRONMENT_H_

#include <string.h>
#include <EGL/egl.h>

#include "../core/fio/InputFile.h"

namespace gbox {

	struct CallBackHolder {
		void (*onContextCreate)();
		void (*onContextDestroy)();
		void (*onContextConfigure)(int width, int height);
		void (*onButtonPress)(unsigned button, int x, int y);
		void (*onButtonRelease)(unsigned button, int x, int y);
		void (*onPointerMotion)(int x, int y);
		void (*onUpdate)(float deltaTime);
		void (*onDraw)();
	};

	class Environment {

	protected:
		CallBackHolder callBackHolder;

	public:
		Environment() {
			memset(&callBackHolder, 0, sizeof(callBackHolder));
		}

		virtual ~Environment() = default;

		CallBackHolder* getCallBackHolder() {
			return &callBackHolder;
		}

		virtual bool createContext() = 0;
		virtual bool destroyContext() = 0;
		virtual EGLNativeWindowType* getNativeWindow() = 0;
		virtual bool handleEvents() = 0;
		virtual core::InputFile* openFile(const char* fileName) = 0;

	private:
		Environment(const Environment& other);
		Environment& operator=(const Environment&);

	};

} /* namespace gbox */

#endif /* GBOX_ENVIRONMENT_H_ */
