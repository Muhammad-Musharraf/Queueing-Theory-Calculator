#include "gui_main.h"
#include "resource.h"
#include "queueing.h"
#include <string>

using namespace std;

const char* const kMainClassName = "QueueGUI";

// ─────────────────────────────
// GLOBALS  (scoped to this file)
// ─────────────────────────────
static HWND hLambda, hMu, hC;
static HWND hSigmaS, hCa;
static HWND hOutput;
static HWND hRadioHr, hRadioMin;

static HFONT hFontLabel  = NULL;
static HFONT hFontBtn    = NULL;
static HFONT hFontSec    = NULL;
static HFONT hFontOutput = NULL;

// Dark/bold "result" console styling for the output box
static HBRUSH hBrushOutput = NULL;
static const COLORREF kOutputBg   = RGB(16,16,16);
static const COLORREF kOutputText = RGB(0,230,120);

// ─────────────────────────────
// HELPER — apply font to a control
// ─────────────────────────────
static void setFont(HWND h, HFONT f) {
    SendMessage(h, WM_SETFONT, (WPARAM)f, TRUE);
}

// ─────────────────────────────
// MAIN WINDOW PROCEDURE
// ─────────────────────────────
LRESULT CALLBACK MainProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

    case WM_CREATE: {
        // ── Create fonts ─────────────────────────────────────────────
        hFontLabel  = CreateFont(15,0,0,0,FW_SEMIBOLD,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"Segoe UI");
        hFontBtn    = CreateFont(14,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"Segoe UI");
        hFontSec    = CreateFont(13,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_SWISS,"Segoe UI");
        hFontOutput = CreateFont(17,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN,"Courier New");

        if (!hBrushOutput) hBrushOutput = CreateSolidBrush(kOutputBg);

        // ── Row 1: Arrival Rate | Service Rate | Servers (c) ─────────
        HWND h;
        h = CreateWindow("static","Arrival Rate",
                WS_VISIBLE|WS_CHILD, 12,18,110,18,hwnd,NULL,NULL,NULL);
        setFont(h, hFontLabel);
        hLambda = CreateWindow("edit","",
                WS_VISIBLE|WS_CHILD|WS_BORDER|ES_NUMBER,
                124,16,70,22,hwnd,NULL,NULL,NULL);
        setFont(hLambda, hFontLabel);

        h = CreateWindow("static","Service Rate",
                WS_VISIBLE|WS_CHILD, 210,18,108,18,hwnd,NULL,NULL,NULL);
        setFont(h, hFontLabel);
        hMu = CreateWindow("edit","",
                WS_VISIBLE|WS_CHILD|WS_BORDER,
                320,16,70,22,hwnd,NULL,NULL,NULL);
        setFont(hMu, hFontLabel);

        h = CreateWindow("static","Servers (c):",
                WS_VISIBLE|WS_CHILD, 402,18,76,18,hwnd,NULL,NULL,NULL);
        setFont(h, hFontLabel);
        hC = CreateWindow("edit","",
                WS_VISIBLE|WS_CHILD|WS_BORDER|ES_NUMBER,
                480,16,55,22,hwnd,NULL,NULL,NULL);
        setFont(hC, hFontLabel);

        // ── Row 2: Svc Std Dev | Arrival CV | Unit radios ────────────
        h = CreateWindow("static","Service Std Dev",
                WS_VISIBLE|WS_CHILD, 12,50,114,18,hwnd,NULL,NULL,NULL);
        setFont(h, hFontLabel);
        hSigmaS = CreateWindow("edit","0",
                WS_VISIBLE|WS_CHILD|WS_BORDER,
                128,48,66,22,hwnd,NULL,NULL,NULL);
        setFont(hSigmaS, hFontLabel);

        h = CreateWindow("static","Arrival CV (Ca):",
                WS_VISIBLE|WS_CHILD, 210,50,104,18,hwnd,NULL,NULL,NULL);
        setFont(h, hFontLabel);
        hCa = CreateWindow("edit","1",
                WS_VISIBLE|WS_CHILD|WS_BORDER,
                316,48,74,22,hwnd,NULL,NULL,NULL);
        setFont(hCa, hFontLabel);

        h = CreateWindow("static","Input Unit:",
                WS_VISIBLE|WS_CHILD, 406,48,70,18,hwnd,NULL,NULL,NULL);
        setFont(h, hFontLabel);
        hRadioHr  = CreateWindow("button","Per Hour",
                WS_VISIBLE|WS_CHILD|BS_AUTORADIOBUTTON|WS_GROUP,
                406,68,90,20,hwnd,(HMENU)ID_RADIO_HR,NULL,NULL);
        setFont(hRadioHr, hFontLabel);
        hRadioMin = CreateWindow("button","Per Minute",
                WS_VISIBLE|WS_CHILD|BS_AUTORADIOBUTTON,
                406,92,95,20,hwnd,(HMENU)ID_RADIO_MIN,NULL,NULL);
        setFont(hRadioMin, hFontLabel);
        SendMessage(hRadioHr, BM_SETCHECK, BST_CHECKED, 0);

        // ── Divider ───────────────────────────────────────────────────
        CreateWindow("static","",WS_VISIBLE|WS_CHILD|SS_ETCHEDHORZ,
                12,122,563,2,hwnd,NULL,NULL,NULL);

        // ── Section: Markovian Models ─────────────────────────────────
        h = CreateWindow("static","  Markovian Models",
                WS_VISIBLE|WS_CHILD, 12,130,180,18,hwnd,NULL,NULL,NULL);
        setFont(h, hFontSec);

        h = CreateWindow("button","M/M/1  -  Single Server",
                WS_VISIBLE|WS_CHILD, 12,152,200,30,hwnd,(HMENU)ID_BTN_MM1,NULL,NULL);
        setFont(h, hFontBtn);
        h = CreateWindow("button","M/M/c  -  Multi Server",
                WS_VISIBLE|WS_CHILD,222,152,200,30,hwnd,(HMENU)ID_BTN_MMC,NULL,NULL);
        setFont(h, hFontBtn);

        // ── Divider ───────────────────────────────────────────────────
        CreateWindow("static","",WS_VISIBLE|WS_CHILD|SS_ETCHEDHORZ,
                12,192,563,2,hwnd,NULL,NULL,NULL);

        // ── Section: General Distribution Models ─────────────────────
        h = CreateWindow("static","  General Distribution Models",
                WS_VISIBLE|WS_CHILD, 12,200,230,18,hwnd,NULL,NULL,NULL);
        setFont(h, hFontSec);

        h = CreateWindow("button","M/G/1  -  P-K Formula",
                WS_VISIBLE|WS_CHILD, 12,222,200,30,hwnd,(HMENU)ID_BTN_MG1,NULL,NULL);
        setFont(h, hFontBtn);
        h = CreateWindow("button","M/G/s  -  Allen Cunneen",
                WS_VISIBLE|WS_CHILD,222,222,200,30,hwnd,(HMENU)ID_BTN_MGS,NULL,NULL);
        setFont(h, hFontBtn);
        h = CreateWindow("button","G/G/1  -  Kingman",
                WS_VISIBLE|WS_CHILD, 12,260,200,30,hwnd,(HMENU)ID_BTN_GG1,NULL,NULL);
        setFont(h, hFontBtn);
        h = CreateWindow("button","G/G/s  -  Allen Cunneen",
                WS_VISIBLE|WS_CHILD,222,260,200,30,hwnd,(HMENU)ID_BTN_GGS,NULL,NULL);
        setFont(h, hFontBtn);

        // ── Divider ───────────────────────────────────────────────────
        CreateWindow("static","",WS_VISIBLE|WS_CHILD|SS_ETCHEDHORZ,
                12,300,563,2,hwnd,NULL,NULL,NULL);

        // ── Results label + output box ────────────────────────────────
        h = CreateWindow("static","  Results",
                WS_VISIBLE|WS_CHILD, 12,308,80,18,hwnd,NULL,NULL,NULL);
        setFont(h, hFontSec);

        hOutput = CreateWindow("edit","",
                WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_READONLY|WS_VSCROLL,
                12,330,563,192,hwnd,NULL,NULL,NULL);
        setFont(hOutput, hFontOutput);
        break;
    }

    case WM_COMMAND: {
        int id = LOWORD(wParam);
        if (id < ID_BTN_MM1 || id > ID_BTN_GGS) break;

        char b1[20],b2[20],b3[20],b4[20],b5[20];
        GetWindowText(hLambda, b1, 20);
        GetWindowText(hMu,     b2, 20);
        GetWindowText(hC,      b3, 20);
        GetWindowText(hSigmaS, b4, 20);
        GetWindowText(hCa,     b5, 20);

        double lambda = atof(b1);
        double mu     = atof(b2);
        int    c      = atoi(b3);
        double sigmaS = atof(b4);
        double Ca     = atof(b5);
        bool   hr     = (SendMessage(hRadioHr, BM_GETCHECK, 0, 0) == BST_CHECKED);

        string result;
        switch (id) {
            case ID_BTN_MM1: result = solveMM1(lambda, mu,                hr); break;
            case ID_BTN_MMC: result = solveMMc(lambda, mu, c,             hr); break;
            case ID_BTN_MG1: result = solveMG1(lambda, mu,    sigmaS,     hr); break;
            case ID_BTN_MGS: result = solveMGS(lambda, mu, c, sigmaS,     hr); break;
            case ID_BTN_GG1: result = solveGG1(lambda, mu,    Ca, sigmaS, hr); break;
            case ID_BTN_GGS: result = solveGGS(lambda, mu, c, Ca, sigmaS, hr); break;
        }
        SetWindowText(hOutput, result.c_str());
        break;
    }

    case WM_CTLCOLOREDIT: {
        HWND ctl = (HWND)lParam;
        if (ctl == hOutput) {
            HDC dc = (HDC)wParam;
            SetTextColor(dc, kOutputText);
            SetBkColor(dc, kOutputBg);
            SetBkMode(dc, OPAQUE);
            return (LRESULT)hBrushOutput;
        }
        break;
    }

    case WM_DESTROY:
        if(hFontLabel)  { DeleteObject(hFontLabel);  hFontLabel  = NULL; }
        if(hFontBtn)    { DeleteObject(hFontBtn);     hFontBtn    = NULL; }
        if(hFontSec)    { DeleteObject(hFontSec);     hFontSec    = NULL; }
        if(hFontOutput) { DeleteObject(hFontOutput);  hFontOutput = NULL; }
        if(hBrushOutput){ DeleteObject(hBrushOutput); hBrushOutput= NULL; }
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
