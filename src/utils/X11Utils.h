#ifndef X11UTILS_H_
#define X11UTILS_H_

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include "../log/Log.h"

struct X11Context {
	Display* display;
	Window window;
	int width;
	int height;
};

class X11Utils {

public:

static bool initX11Context(X11Context& xc, const char *title, int width, int height) {
	Window root;
	XSetWindowAttributes swa;
	XSetWindowAttributes xattr;
	Atom wm_state;
	XWMHints hints;
	XEvent xev;

	xc.display = XOpenDisplay(NULL);
	if (xc.display == NULL) {
		return false;
	}

	root = DefaultRootWindow(xc.display);

	swa.event_mask = ButtonPressMask | ButtonReleaseMask | ButtonMotionMask
			| ExposureMask | KeyPressMask | StructureNotifyMask;
	xc.window = XCreateWindow(xc.display, root, 0, 0, width, height, 0,
	CopyFromParent, InputOutput,
	CopyFromParent, CWEventMask, &swa);

	xattr.override_redirect = false;
	XChangeWindowAttributes(xc.display, xc.window, CWOverrideRedirect, &xattr);

	hints.input = true;
	hints.flags = InputHint;
	XSetWMHints(xc.display, xc.window, &hints);

	// make the window visible on the screen
	XMapWindow(xc.display, xc.window);
	XStoreName(xc.display, xc.window, title);

	// get identifiers for the provided atom name strings
	wm_state = XInternAtom(xc.display, "_NET_WM_STATE", false);

	Atom WM_DELETE_WINDOW = XInternAtom(xc.display, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(xc.display, xc.window, &WM_DELETE_WINDOW, 1);

	memset(&xev, 0, sizeof(xev));
	xev.type = ClientMessage;
	xev.xclient.window = xc.window;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 1;
	xev.xclient.data.l[1] = false;
	XSendEvent(xc.display, DefaultRootWindow(xc.display), false,
	SubstructureNotifyMask, &xev);

	xc.width = width;
	xc.height = height;

	return true;
}

};

#endif /* X11UTILS_H_ */
