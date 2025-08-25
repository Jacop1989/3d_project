#include "platform.h"
#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#include <string.h>

static HWND hwnd;
static HDC hdc;
static void *backbuffer;
static BITMAPINFO bmi;
static int buffer_width;
static int buffer_height;
static int running = 1;

static LRESULT CALLBACK wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_CLOSE || msg == WM_DESTROY) {
        running = 0;
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int platform_init(const char *title, int width, int height) {
    buffer_width = width;
    buffer_height = height;
    WNDCLASS wc = {0};
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "three_d_app_class";
    if (!RegisterClass(&wc))
        return -1;

    hwnd = CreateWindowEx(0, wc.lpszClassName, title ? title : "app",
                          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                          CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                          NULL, NULL, wc.hInstance, NULL);
    if (!hwnd)
        return -1;

    hdc = GetDC(hwnd);

    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; /* top-down */
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    backbuffer = malloc(width * height * 4);
    return backbuffer ? 0 : -1;
}

int platform_poll(void) {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            running = 0;
            return 1;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return running ? 0 : 1;
}

void platform_present(const uint32_t *pixels) {
    if (!backbuffer)
        return;
    memcpy(backbuffer, pixels, buffer_width * buffer_height * 4);
    StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0,
                  buffer_width, buffer_height, backbuffer, &bmi,
                  DIB_RGB_COLORS, SRCCOPY);
}

void platform_sleep(int milliseconds) {
    Sleep(milliseconds);
}

void platform_shutdown(void) {
    if (backbuffer) {
        free(backbuffer);
        backbuffer = NULL;
    }
    if (hwnd && hdc)
        ReleaseDC(hwnd, hdc);
    if (hwnd)
        DestroyWindow(hwnd);
    hwnd = NULL;
    hdc = NULL;
    running = 0;
}
#endif /* _WIN32 */
