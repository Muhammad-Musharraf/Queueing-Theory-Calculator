#include "gui_splash.h"
#include "resource.h"

const char* const kSplashClassName = "StartWin";
bool openMain = false;

// ── Fonts (scoped to this file) ────────
static HFONT hFontTitle  = NULL;
static HFONT hFontBold   = NULL;
static HFONT hFontNormal = NULL;

// ── Dark/bold theme for the splash pop-up ────────
static HBRUSH hBrushSplashBg = NULL;
static const COLORREF kSplashBg   = RGB(18,18,18);
static const COLORREF kSplashText = RGB(235,235,235);

static void setFont(HWND h, HFONT f) {
    SendMessage(h, WM_SETFONT, (WPARAM)f, TRUE);
}

// ─────────────────────────────
// SPLASH WINDOW PROCEDURE
// ─────────────────────────────
LRESULT CALLBACK StartProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        if (!hBrushSplashBg) hBrushSplashBg = CreateSolidBrush(kSplashBg);

        hFontTitle = CreateFont(46,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_SWISS,"Segoe UI");
        hFontBold  = CreateFont(21,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_SWISS,"Segoe UI");
        hFontNormal= CreateFont(18,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_SWISS,"Segoe UI");

        // Title
        HWND h = CreateWindow("static","Queue Theory Calculator",
            WS_VISIBLE|WS_CHILD|SS_CENTER,
            20,50,720,56,hwnd,NULL,NULL,NULL);
        setFont(h, hFontTitle);

        // Top divider
        CreateWindow("static","",WS_VISIBLE|WS_CHILD|SS_ETCHEDHORZ,
            20,118,720,2,hwnd,NULL,NULL,NULL);

        // Subject label
        h = CreateWindow("static","Queueing Theory  |  Operations Research",
            WS_VISIBLE|WS_CHILD|SS_CENTER,
            20,132,720,26,hwnd,NULL,NULL,NULL);
        setFont(h, hFontBold);

        // Mid divider
        CreateWindow("static","",WS_VISIBLE|WS_CHILD|SS_ETCHEDHORZ,
            20,170,720,2,hwnd,NULL,NULL,NULL);

        // Group label
        h = CreateWindow("static","Group  #  10",
            WS_VISIBLE|WS_CHILD|SS_CENTER,
            20,186,720,28,hwnd,NULL,NULL,NULL);
        setFont(h, hFontBold);

        // Member names
        h = CreateWindow("static",
            "1.   Muhammad Musharraf\r\n"
            "2.   Bilal\r\n"
            "3.   Wahaj\r\n"
            "4.   Abdul Rafy\r\n"
            "5.   Ahmed Hashmi",
            WS_VISIBLE|WS_CHILD,
            300,230,300,170,hwnd,NULL,NULL,NULL);
        setFont(h, hFontNormal);

        // Bottom divider
        CreateWindow("static","",WS_VISIBLE|WS_CHILD|SS_ETCHEDHORZ,
            20,468,720,2,hwnd,NULL,NULL,NULL);

        // Open button
        h = CreateWindow("button","Open Calculator",
            WS_VISIBLE|WS_CHILD,
            305,488,170,46,hwnd,(HMENU)ID_BTN_OPEN,NULL,NULL);
        setFont(h, hFontBold);
        break;
    }
    case WM_CTLCOLORSTATIC: {
        HDC dc = (HDC)wParam;
        SetTextColor(dc, kSplashText);
        SetBkColor(dc, kSplashBg);
        SetBkMode(dc, OPAQUE);
        return (LRESULT)hBrushSplashBg;
    }
    case WM_COMMAND:
        if (LOWORD(wParam)==ID_BTN_OPEN) { openMain=true; DestroyWindow(hwnd); }
        break;
    case WM_DESTROY:
        if(hFontTitle)    { DeleteObject(hFontTitle);    hFontTitle   =NULL; }
        if(hFontBold)     { DeleteObject(hFontBold);     hFontBold    =NULL; }
        if(hFontNormal)   { DeleteObject(hFontNormal);   hFontNormal  =NULL; }
        if(hBrushSplashBg){ DeleteObject(hBrushSplashBg); hBrushSplashBg=NULL; }
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
