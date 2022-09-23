#pragma once
#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class DrawHelper
{
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pBrush;
    D2D1_ELLIPSE            ellipse;


public:

    void    CalculateLayout(int x, int y);
    HRESULT CreateGraphicsResources(int x, int y, int color);
    void    DiscardGraphicsResources();
    void    OnPaint(int x, int y, int color);
    void    Resize();
    HWND m_hwnd;

    DrawHelper(HWND hwnd) : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
    {
        m_hwnd = hwnd;
        D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
    }

    PCWSTR  ClassName() const { return L"Circle Window Class"; }
};

