#ifndef PLATFORMX11_X11ENVIRONMENT_H_
#define PLATFORMX11_X11ENVIRONMENT_H_

#include <string>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include "../gbox/Environment.h"

namespace gbox {

struct X11Context {
	Display* display;
	Window window;
	int width;
	int height;
};

class X11Environment: public Environment {

	X11Context x11Context;

public:
	X11Environment() {
		memset(&x11Context, 0, sizeof(x11Context));
	}

	virtual ~X11Environment() = default;

	virtual void createNotify() override {
		if (callBackHolder.configureNotify != nullptr) {
			callBackHolder.configureNotify(x11Context.width, x11Context.height);
		}
	}

	virtual EGLNativeWindowType* getNativeWindow() override {
		return &(x11Context.window);
	}

	virtual bool handleEvents() override {
		XEvent event;

		while (XPending(x11Context.display)) {

			XNextEvent(x11Context.display, &event);

			switch (event.type) {
			case ButtonPress:
				if (callBackHolder.buttonPress != nullptr) {
					callBackHolder.buttonPress(event.xbutton.button,
							event.xbutton.x, event.xbutton.y);
				}
				break;

			case ButtonRelease:
				if (callBackHolder.buttonRelease != nullptr) {
					callBackHolder.buttonRelease(event.xbutton.button,
							event.xbutton.x, event.xbutton.y);
				}
				break;

			case MotionNotify:
				if (callBackHolder.motionNotify != nullptr) {
					callBackHolder.motionNotify(event.xmotion.x,
							event.xmotion.y);
				}
				break;

			case ConfigureNotify:
				if (event.xconfigure.width != x11Context.width
						|| event.xconfigure.height != x11Context.height) {
					if (callBackHolder.configureNotify != nullptr) {
						callBackHolder.configureNotify(event.xconfigure.width,
								event.xconfigure.height);
					}
					x11Context.width = event.xconfigure.width;
					x11Context.height = event.xconfigure.height;
				}
				break;

			case ClientMessage:
				if (callBackHolder.destroyNotify != nullptr) {
					callBackHolder.destroyNotify();
				}
				return false;
			}
		}
		return true;
	}

	bool initX11Context(const char *title, int width, int height) {
		Window root;
		XSetWindowAttributes swa;
		XSetWindowAttributes xattr;
		Atom wm_state;
		XWMHints hints;
		XEvent xev;

		x11Context.display = XOpenDisplay(NULL);
		if (x11Context.display == NULL) {
			return false;
		}

		root = DefaultRootWindow(x11Context.display);

		swa.event_mask = ButtonPressMask | ButtonReleaseMask | ButtonMotionMask
				| ExposureMask | KeyPressMask | StructureNotifyMask;
		x11Context.window = XCreateWindow(x11Context.display, root, 0, 0, width, height, 0,
		CopyFromParent, InputOutput,
		CopyFromParent, CWEventMask, &swa);

		xattr.override_redirect = false;
		XChangeWindowAttributes(x11Context.display, x11Context.window, CWOverrideRedirect, &xattr);

		hints.input = true;
		hints.flags = InputHint;
		XSetWMHints(x11Context.display, x11Context.window, &hints);

		// make the window visible on the screen
		XMapWindow(x11Context.display, x11Context.window);
		XStoreName(x11Context.display, x11Context.window, title);

		// get identifiers for the provided atom name strings
		wm_state = XInternAtom(x11Context.display, "_NET_WM_STATE", false);

		Atom WM_DELETE_WINDOW = XInternAtom(x11Context.display, "WM_DELETE_WINDOW", false);
		XSetWMProtocols(x11Context.display, x11Context.window, &WM_DELETE_WINDOW, 1);

		memset(&xev, 0, sizeof(xev));
		xev.type = ClientMessage;
		xev.xclient.window = x11Context.window;
		xev.xclient.message_type = wm_state;
		xev.xclient.format = 32;
		xev.xclient.data.l[0] = 1;
		xev.xclient.data.l[1] = false;
		XSendEvent(x11Context.display, DefaultRootWindow(x11Context.display), false,
		SubstructureNotifyMask, &xev);

		x11Context.width = width;
		x11Context.height = height;

		return true;
	}

private:
	X11Environment(const X11Environment& other);
	X11Environment& operator=(const X11Environment&);

};

} /* namespace gbox */

#endif /* PLATFORMX11_X11ENVIRONMENT_H_ */
