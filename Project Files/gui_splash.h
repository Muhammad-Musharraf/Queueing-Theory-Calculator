#pragma once
#include <windows.h>

extern const char* const kSplashClassName;
extern bool openMain;   // set to true when the user clicks "Open Calculator"

LRESULT CALLBACK StartProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
