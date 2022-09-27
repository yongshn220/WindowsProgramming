#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Draw.h"

#include "PointConvex.h"
#include "QuickHull.h"
#include "Minkowski.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateButton(HWND hwnd);
void ShowGJK(HWND hwnd);

PointConvex* pc;
QuickHull* qh;
Minkowski* mk;
Draw* draw;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    draw = new Draw(hwnd);
    pc = new PointConvex();
    qh = new QuickHull();
    mk = new Minkowski();

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        switch(wParam)
        {
        case 1:
            pc->Reset();
            qh->Reset();
            mk->Reset();
        }
    case WM_CREATE:
        CreateButton(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        
        // ShowPointConvex(hwnd);
        // ShowQuickHull(hwnd);
        // ShowMinkowskiDiff(hwnd);
        // ShowMinkowskiSum(hwnd);
        ShowGJK(hwnd);

        EndPaint(hwnd, &ps);
        break;
    }
    return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateButton(HWND hwnd)
{
    CreateWindowW(L"Button", L"Button", WS_VISIBLE | WS_CHILD, 0, 100, 50, 100, hwnd, (HMENU)1, NULL, NULL);
}

void ShowGJK(HWND hwnd)
{
    draw->DrawPoint({ 100,100 }, "blue");
}
