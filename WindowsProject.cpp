#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <Windowsx.h>
#include "Draw.h"

#include "PointConvex.h"
#include "QuickHull.h"
#include "Minkowski.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateButton(HWND hwnd);
void ShowLine();
void ConvexHullEX();
void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
void OnLButtonUp();
void OnMouseMove(int pixelX, int pixelY, DWORD flags);

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
        ConvexHullEX();
        EndPaint(hwnd, &ps);
        break;
    }

    case WM_LBUTTONDOWN:
        OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;

    case WM_LBUTTONUP:
        OnLButtonUp();
        return 0;

    case WM_MOUSEMOVE:
        OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;


    return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateButton(HWND hwnd)
{
    CreateWindowW(L"Button", L"Button", WS_VISIBLE | WS_CHILD, 0, 100, 50, 100, hwnd, (HMENU)1, NULL, NULL);
}

void ShowLine()
{
    draw->BeginDraw();
    draw->DrawPoint({ 100,100 }, "white");
    draw->DrawLine({ 200, 100 }, { 200, 200 }, "blue");
    draw->EndDraw();
}

void DrawLines(std::vector<point> points, std::string color)
{
    draw->DrawLine(points[0], points[1], color);
    for (int i = 1; i < points.size(); i++)
    {
        draw->DrawLine(points[i - 1], points[i], color);
    }
}

void ConvexHullEX()
{
    draw->BeginDraw();
    DrawLines(pc->hulls, "white");
    for (int i = 0; i < pc->points.size(); i++)
    {
        draw->DrawPoint(pc->points[i], "white");
    }

    for (int i = 0; i < pc->hulls.size(); i++)
    {
        draw->DrawPoint(pc->hulls[i], "blue");
    }

    if (pc->state)
    {
        draw->DrawPoint(pc->target, "green");
    }

    else
    {
        draw->DrawPoint(pc->target, "red");
    }
    draw->EndDraw();
}

void OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{

}
void OnLButtonUp()
{

}
void OnMouseMove(int pixelX, int pixelY, DWORD flags)
{

}