#include <windows.h>
#include <string>
#include <cmath>

using namespace std;

// ─────────────────────────────
// GLOBALS
// ─────────────────────────────
HWND hLambda, hMu, hC;
HWND hOutput;
bool openMain = false;

// ─────────────────────────────
// FACTORIAL
// ─────────────────────────────
double factorial(int n) {
    double f = 1;
    for(int i = 2; i <= n; i++) f *= i;
    return f;
}

// ─────────────────────────────
// M/M/1
// ─────────────────────────────
string solveMM1(double lambda, double mu) {
    if(lambda >= mu)
        return "System Unstable (lambda >= mu)\r\n";
    double rho = lambda / mu;
    double P0  = 1 - rho;
    double Lq  = (lambda * lambda) / (mu * (mu - lambda));
    double Wq  = Lq / lambda;
    double Ws  = Wq + 1.0 / mu;
    double Ls  = lambda * Ws;
    string out =
        "M/M/1 RESULTS\r\n"
        "----------------------\r\n" +
        string("Traffic Intensity (rho) = ") + to_string(rho) + "\r\n" +
        string("Idle Probability (P0)   = ") + to_string(P0)  + "\r\n" +
        string("Queue Length (Lq)       = ") + to_string(Lq)  + "\r\n" +
        string("System Length (Ls)      = ") + to_string(Ls)  + "\r\n" +
        string("Queue Wait Time (Wq)    = ") + to_string(Wq)  + "\r\n" +
        string("System Wait Time (Ws)   = ") + to_string(Ws)  + "\r\n";
    return out;
}

// ─────────────────────────────
// M/M/c
// ─────────────────────────────
string solveMMc(double lambda, double mu, int c) {
    if(lambda >= c * mu)
        return "System Unstable (lambda >= c*mu)\r\n";
    double a   = lambda / mu;
    double rho = lambda / (c * mu);
    double sum = 0;
    for(int n = 0; n < c; n++)
        sum += pow(a, n) / factorial(n);
    double P0 = 1.0 / (sum + pow(a, c) / (factorial(c) * (1 - rho)));
    double Pc = (pow(a, c) / (factorial(c) * (1 - rho))) * P0;
    double Lq = (Pc * a * rho) / (1 - rho);
    double Wq = Lq / lambda;
    double Ws = Wq + 1.0 / mu;
    double Ls = lambda * Ws;
    string out =
        "M/M/c RESULTS\r\n"
        "----------------------\r\n" +
        string("Traffic Intensity (rho)                    = ") + to_string(rho) + "\r\n" +
        string("Idle Probability (P0)                      = ") + to_string(P0)  + "\r\n" +
        string("Prob. of c customers in system (Pc)        = ") + to_string(Pc)  + "\r\n" +
        string("Queue Length (Lq)                          = ") + to_string(Lq)  + "\r\n" +
        string("System Length (Ls)                         = ") + to_string(Ls)  + "\r\n" +
        string("Queue Wait Time (Wq)                       = ") + to_string(Wq)  + "\r\n" +
        string("System Wait Time (Ws)                      = ") + to_string(Ws)  + "\r\n";
    return out;
}

// ─────────────────────────────
// MAIN WINDOW PROCEDURE  (page 2)
// ─────────────────────────────
LRESULT CALLBACK MainProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
    case WM_CREATE:
        CreateWindow("static","Lambda:",WS_VISIBLE|WS_CHILD,20,20,60,20,hwnd,NULL,NULL,NULL);
        hLambda = CreateWindow("edit","",WS_VISIBLE|WS_CHILD|WS_BORDER,80,20,80,20,hwnd,NULL,NULL,NULL);
        CreateWindow("static","Mu:",WS_VISIBLE|WS_CHILD,180,20,40,20,hwnd,NULL,NULL,NULL);
        hMu = CreateWindow("edit","",WS_VISIBLE|WS_CHILD|WS_BORDER,220,20,80,20,hwnd,NULL,NULL,NULL);
        CreateWindow("static","C:",WS_VISIBLE|WS_CHILD,320,20,20,20,hwnd,NULL,NULL,NULL);
        hC = CreateWindow("edit","",WS_VISIBLE|WS_CHILD|WS_BORDER,340,20,50,20,hwnd,NULL,NULL,NULL);
        CreateWindow("button","M/M/1",WS_VISIBLE|WS_CHILD,20,60,100,30,hwnd,(HMENU)1,NULL,NULL);
        CreateWindow("button","M/M/c",WS_VISIBLE|WS_CHILD,140,60,100,30,hwnd,(HMENU)2,NULL,NULL);
        hOutput = CreateWindow(
            "edit","",
            WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_READONLY|WS_VSCROLL,
            20,110,410,220,hwnd,NULL,NULL,NULL);
        break;
    case WM_COMMAND:
        if(LOWORD(wParam) == 1 || LOWORD(wParam) == 2) {
            char b1[20], b2[20], b3[20];
            GetWindowText(hLambda, b1, 20);
            GetWindowText(hMu,     b2, 20);
            GetWindowText(hC,      b3, 20);
            double lambda = atof(b1);
            double mu     = atof(b2);
            int    c      = atoi(b3);
            string result = (LOWORD(wParam) == 1)
                ? solveMM1(lambda, mu)
                : solveMMc(lambda, mu, c);
            SetWindowText(hOutput, result.c_str());
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ─────────────────────────────
// SPLASH WINDOW PROCEDURE  (page 1)
// ─────────────────────────────
HFONT hFontTitle  = NULL;
HFONT hFontBold   = NULL;
HFONT hFontNormal = NULL;

LRESULT CALLBACK StartProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {

    case WM_CREATE: {
        hFontTitle = CreateFont(
            28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");

        hFontBold = CreateFont(
            16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");

        hFontNormal = CreateFont(
            15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");

        // Heading
        HWND hTitle = CreateWindow(
            "static", "Queue Calculator",
            WS_VISIBLE | WS_CHILD | SS_CENTER,
            40, 20, 320, 36, hwnd, NULL, NULL, NULL);
        SendMessage(hTitle, WM_SETFONT, (WPARAM)hFontTitle, TRUE);

        // Divider
        CreateWindow("static", "",
            WS_VISIBLE | WS_CHILD | SS_ETCHEDHORZ,
            20, 62, 360, 2, hwnd, NULL, NULL, NULL);

        // Group label
        HWND hGroup = CreateWindow(
            "static", "Group # 10",
            WS_VISIBLE | WS_CHILD | SS_CENTER,
            40, 72, 320, 22, hwnd, NULL, NULL, NULL);
        SendMessage(hGroup, WM_SETFONT, (WPARAM)hFontBold, TRUE);

        // Member names
        HWND hNames = CreateWindow(
            "static",
            "1.  Muhammad Musharraf\r\n"
            "2.  Bilal\r\n"
            "3.  Wahaj\r\n"
            "4.  Abdul Wasay\r\n"
            "5.  Abdul Rafy\r\n"
            "6.  Ahmed Hashmi",
            WS_VISIBLE | WS_CHILD,
            100, 104, 200, 120, hwnd, NULL, NULL, NULL);
        SendMessage(hNames, WM_SETFONT, (WPARAM)hFontNormal, TRUE);

        // Divider
        CreateWindow("static", "",
            WS_VISIBLE | WS_CHILD | SS_ETCHEDHORZ,
            20, 234, 360, 2, hwnd, NULL, NULL, NULL);

        // Calculate button
        HWND hBtn = CreateWindow(
            "button", "Calculate",
            WS_VISIBLE | WS_CHILD,
            150, 248, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        SendMessage(hBtn, WM_SETFONT, (WPARAM)hFontBold, TRUE);

        break;
    }

    case WM_COMMAND:
        if(LOWORD(wParam) == 1) {
            openMain = true;
            DestroyWindow(hwnd);
        }
        break;

    case WM_DESTROY:
        if(hFontTitle)  { DeleteObject(hFontTitle);  hFontTitle  = NULL; }
        if(hFontBold)   { DeleteObject(hFontBold);   hFontBold   = NULL; }
        if(hFontNormal) { DeleteObject(hFontNormal); hFontNormal = NULL; }
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ─────────────────────────────
// WINMAIN — two-phase message loop
// ─────────────────────────────
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {

    WNDCLASS wc1 = {};
    wc1.lpfnWndProc   = StartProc;
    wc1.hInstance     = hInst;
    wc1.lpszClassName = "StartWin";
    wc1.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc1.hCursor       = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc1);

    WNDCLASS wc2 = {};
    wc2.lpfnWndProc   = MainProc;
    wc2.hInstance     = hInst;
    wc2.lpszClassName = "QueueGUI";
    wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc2.hCursor       = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc2);

    // Page 1 — splash
    HWND start = CreateWindowEx(
        0, "StartWin", "Queue Calculator - Group #10",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 420, 320,
        NULL, NULL, hInst, NULL);
    ShowWindow(start, nCmdShow);

    MSG msg = {};
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if(!openMain) return 0;

    // Page 2 — calculator
    HWND hwnd = CreateWindowEx(
        0, "QueueGUI", "Queue System (M/M/1 & M/M/c)",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 460, 400,
        NULL, NULL, hInst, NULL);
    ShowWindow(hwnd, nCmdShow);

    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}