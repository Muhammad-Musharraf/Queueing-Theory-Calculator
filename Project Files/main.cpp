#include <windows.h>
#include "gui_splash.h"
#include "gui_main.h"

// ─────────────────────────────
// WINMAIN
// ─────────────────────────────
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    // Dark, bold pop-up theme — kept alive for the app's lifetime
    static HBRUSH hSplashBg = CreateSolidBrush(RGB(18,18,18));

    WNDCLASS wc1={};
    wc1.lpfnWndProc  = StartProc;
    wc1.hInstance    = hInst;
    wc1.lpszClassName= kSplashClassName;
    wc1.hbrBackground= hSplashBg;
    wc1.hCursor      = LoadCursor(NULL,IDC_ARROW);
    RegisterClass(&wc1);

    WNDCLASS wc2={};
    wc2.lpfnWndProc  = MainProc;
    wc2.hInstance    = hInst;
    wc2.lpszClassName= kMainClassName;
    wc2.hbrBackground= (HBRUSH)(COLOR_WINDOW+1);
    wc2.hCursor      = LoadCursor(NULL,IDC_ARROW);
    RegisterClass(&wc2);

    // ── Splash window ─────────────────────────────────────────────────
    HWND start = CreateWindowEx(0,kSplashClassName,
        "Queue Theory Calculator  -  Group #10",
        WS_OVERLAPPEDWINDOW&~WS_THICKFRAME&~WS_MAXIMIZEBOX,
        CW_USEDEFAULT,CW_USEDEFAULT,780,600,
        NULL,NULL,hInst,NULL);
    ShowWindow(start, nCmdShow);

    MSG msg={};
    while(GetMessage(&msg,NULL,0,0)){ TranslateMessage(&msg); DispatchMessage(&msg); }
    if(!openMain) return 0;

    // ── Calculator window ─────────────────────────────────────────────
    HWND hwnd = CreateWindowEx(0,kMainClassName,
        "Queue Theory Calculator",
        WS_OVERLAPPEDWINDOW&~WS_THICKFRAME&~WS_MAXIMIZEBOX,
        CW_USEDEFAULT,CW_USEDEFAULT,620,580,
        NULL,NULL,hInst,NULL);
    ShowWindow(hwnd, nCmdShow);

    while(GetMessage(&msg,NULL,0,0)){ TranslateMessage(&msg); DispatchMessage(&msg); }
    return 0;
}
