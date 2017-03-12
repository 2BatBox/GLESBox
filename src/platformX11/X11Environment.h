#ifndef PLATFORMX11_X11ENVIRONMENT_H_
#define PLATFORMX11_X11ENVIRONMENT_H_

#include <string>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include "../gbox/Environment.h"
#include "../core/fio/RawInputFile.h"

namespace gbox {

	struct X11Context {
		Display* display;
		Window window;
		int width;
		int height;
	};

	class X11Environment: public Environment {

		X11Context x11Context;
		std::string baseDir;

	public:
		X11Environment(const char* baseDir) :
				baseDir(baseDir) {
			memset(&x11Context, 0, sizeof(x11Context));
		}

		virtual ~X11Environment() = default;

		virtual bool createContext() override {
			if (callBackHolder.onContextCreate != nullptr) {
				callBackHolder.onContextCreate();
			}
			if (callBackHolder.onContextConfigure != nullptr) {
				callBackHolder.onContextConfigure(x11Context.width, x11Context.height);
			}
			return true;
		}

		virtual bool destroyContext() {
			if (callBackHolder.onContextDestroy != nullptr) {
				callBackHolder.onContextDestroy();
			}
			return true;
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
					if (callBackHolder.onButtonPress != nullptr) {
						callBackHolder.onButtonPress(event.xbutton.button, event.xbutton.x, event.xbutton.y);
					}
					break;

				case ButtonRelease:
					if (callBackHolder.onButtonRelease != nullptr) {
						callBackHolder.onButtonRelease(event.xbutton.button, event.xbutton.x, event.xbutton.y);
					}
					break;

				case MotionNotify:
					if (callBackHolder.onPointerMotion != nullptr) {
						callBackHolder.onPointerMotion(event.xmotion.x, event.xmotion.y);
					}
					break;

				case ConfigureNotify:
					if (event.xconfigure.width != x11Context.width || event.xconfigure.height != x11Context.height) {
						if (callBackHolder.onContextConfigure != nullptr) {
							callBackHolder.onContextConfigure(event.xconfigure.width, event.xconfigure.height);
						}
						x11Context.width = event.xconfigure.width;
						x11Context.height = event.xconfigure.height;
					}
					break;

				case ClientMessage:
					return false;
				}
			}
			return true;
		}

		virtual core::InputFile* openFile(const char* fileName) override {
			core::InputFile* result = nullptr;
			std::string file = baseDir + "/" + fileName;
			try {
				result = core::RawInputFile::open(file.c_str());
			} catch (const core::NullPointerException& e) {
			} catch (const core::FIOException& e) {
			}
			return result;
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

			swa.event_mask = ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | ExposureMask | KeyPressMask
					| StructureNotifyMask;
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
