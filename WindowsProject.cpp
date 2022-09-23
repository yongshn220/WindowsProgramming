#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "PointConvex.h"
#include "DrawCircle.h"
#include "QuickHull.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowPointConvex(HWND);
void ShowQuickHull(HWND hwnd);
void DrawPoint(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush, point point);
void CreateButton(HWND hwnd);

PointConvex* pc;
QuickHull* qh;
DrawHelper* dc;

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

    pc = new PointConvex();
    dc = new DrawHelper(hwnd);
    qh = new QuickHull();

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
        ShowQuickHull(hwnd);
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

void ShowQuickHull(HWND hwnd)
{
    ID2D1Factory* pFactory = NULL;
    ID2D1HwndRenderTarget* pRenderTarget = NULL;
    ID2D1SolidColorBrush* pBrush = NULL;
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
    HRESULT hr = S_OK;
    RECT rc;
    GetClientRect(hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

    hr = pFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, size),
        &pRenderTarget);

    D2D1_COLOR_F c = D2D1::ColorF(D2D1::ColorF::Green);

    pRenderTarget->CreateSolidColorBrush(c, &pBrush);

    pRenderTarget->BeginDraw();

    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    for (int i = 0; i < qh->points.size(); i++)
    {
        c = D2D1::ColorF(D2D1::ColorF::White);
        pRenderTarget->CreateSolidColorBrush(c, &pBrush);
        DrawPoint(pRenderTarget, pBrush, qh->points[i]);
    }

    for (int i = 0; i < qh->hulls.size(); i++)
    {
        c = D2D1::ColorF(D2D1::ColorF::Green);
        pRenderTarget->CreateSolidColorBrush(c, &pBrush);
        DrawPoint(pRenderTarget, pBrush, qh->hulls[i]);
    }
    pRenderTarget->EndDraw();




void ShowPointConvex(HWND hwnd)
{
    ID2D1Factory* pFactory = NULL;
    ID2D1HwndRenderTarget* pRenderTarget = NULL;
    ID2D1SolidColorBrush* pBrush = NULL;
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
    HRESULT hr = S_OK;
    RECT rc;
    GetClientRect(hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

    hr = pFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, size),
        &pRenderTarget);

    D2D1_COLOR_F c = D2D1::ColorF(D2D1::ColorF::Green);

    pRenderTarget->CreateSolidColorBrush(c, &pBrush);

    pRenderTarget->BeginDraw();

    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    for (int i = 0; i < pc->points.size(); i++)
    {
        c = D2D1::ColorF(D2D1::ColorF::White);
        pRenderTarget->CreateSolidColorBrush(c, &pBrush);
        DrawPoint(pRenderTarget, pBrush, pc->points[i]);
    }

    for (int i = 0; i < pc->hulls.size(); i++)
    {
        c = D2D1::ColorF(D2D1::ColorF::Green);
        pRenderTarget->CreateSolidColorBrush(c, &pBrush);
        DrawPoint(pRenderTarget, pBrush, pc->hulls[i]);
    }

    if (pc->state)
    {
        c = D2D1::ColorF(D2D1::ColorF::Blue);
        pRenderTarget->CreateSolidColorBrush(c, &pBrush);
        DrawPoint(pRenderTarget, pBrush, pc->target);
    }

    else
    {
        c = D2D1::ColorF(D2D1::ColorF::Red);
        pRenderTarget->CreateSolidColorBrush(c, &pBrush);
        DrawPoint(pRenderTarget, pBrush, pc->target);
    }
    pRenderTarget->EndDraw();
}

void DrawPoint(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush, point p)
{
    int offsetA = 300;
    int offsetM = 1.2;

    point np = {offsetA + (p.x * offsetM), offsetA + (p.y * offsetM)};
    D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(np.x, np.y), 4, 4);
    pRenderTarget->FillEllipse(ellipse, pBrush);
}