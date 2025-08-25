#include "platform.h"
#ifndef _WIN32
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "core/safe.h"
#include "core/log.h"

static Display *display;
static Window window;
static GC gc;
static XImage *image;
static Atom wm_delete_window;
static int buffer_width;
static int buffer_height;

err_t platform_init(const char *title, int width, int height) {
    display = XOpenDisplay(NULL);
    if (!display)
        return ERR_INVALID;
    int screen = DefaultScreen(display);
    buffer_width = width;
    buffer_height = height;
    window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                 0, 0, (unsigned)width, (unsigned)height, 1,
                                 BlackPixel(display, screen),
                                 WhitePixel(display, screen));
    XStoreName(display, window, title ? title : "app");
    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);
    gc = XCreateGC(display, window, 0, NULL);
    XMapWindow(display, window);
    wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wm_delete_window, 1);

    char *data = SAFE_MALLOC((size_t)width * (size_t)height * 4);
    if (!data)
        return ERR_OOM;
    image = XCreateImage(display, DefaultVisual(display, screen), 24, ZPixmap, 0,
                         data, (unsigned)width, (unsigned)height, 32, 0);
    if (!image)
        return ERR_INVALID;
    return ERR_OK;
}

int platform_poll(void) {
    int had = 0;
    while (XPending(display)) {
        had = 1;
        XEvent event;
        XNextEvent(display, &event);
        if (event.type == ClientMessage && (Atom)event.xclient.data.l[0] == wm_delete_window)
            return 1;
        if (event.type == DestroyNotify)
            return 1;
    }
    if(!had) usleep(1000);
    return 0;
}

void platform_present(const uint32_t *pixels) {
    if (!image || !pixels)
        return;
    memcpy(image->data, pixels, (size_t)buffer_width * (size_t)buffer_height * 4);
    XPutImage(display, window, gc, image, 0, 0, 0, 0, (unsigned)buffer_width, (unsigned)buffer_height);
    XFlush(display);
}

void platform_sleep(int milliseconds) {
    usleep((useconds_t)milliseconds * 1000);
}

void platform_shutdown(void) {
    if (image) {
        XDestroyImage(image);
        image = NULL;
    }
    if (gc)
        XFreeGC(display, gc);
    if (window)
        XDestroyWindow(display, window);
    if (display)
        XCloseDisplay(display);
    display = NULL;
    window = 0;
    gc = 0;
}
#endif /* !_WIN32 */
