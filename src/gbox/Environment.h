#ifndef GBOX_ENVIRONMENT_H_
#define GBOX_ENVIRONMENT_H_

#include <string.h>
#include <EGL/egl.h>

namespace gbox {

struct CallBackHolder {
	void (*configureNotify)(int width, int height);
	void (*buttonPress)(unsigned button, int x, int y);
	void (*buttonRelease)(unsigned button, int x, int y);
	void (*motionNotify)(int x, int y);
	void (*destroyNotify)();
	void (*update)(float deltaTime);
	void (*draw)();
};

class Environment {

protected:
	CallBackHolder callBackHolder;

public:
	Environment() {
		memset(&callBackHolder, 0, sizeof(callBackHolder));
	}

	virtual ~Environment() = default;

	CallBackHolder* getCallBackHolder(){
		return &callBackHolder;
	}

	virtual EGLNativeWindowType* getNativeWindow() = 0;
	virtual void createNotify() = 0;
	virtual bool handleEvents() = 0;

private:
	Environment(const Environment& other);
	Environment& operator=(const Environment&);

};

} /* namespace gbox */

#endif /* GBOX_ENVIRONMENT_H_ */
