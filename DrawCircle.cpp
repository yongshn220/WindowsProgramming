#include "DrawCircle.h"

void DrawHelper::CalculateLayout(int x, int y)
{
    if (pRenderTarget != NULL)
    {
        D2D1_SIZE_F size = pRenderTarget->GetSize();
        //const float x = size.width / 2;
        //const float y = size.height / 2;
        //const float radius = min(x, y);
        ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), 10, 10);
    }
}

HRESULT DrawHelper::CreateGraphicsResources(int x, int y, int color)
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(DrawHelper::m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
        //D2D1_SIZE_U size = D2D1::SizeU(1,1);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(DrawHelper::m_hwnd, size),
            &pRenderTarget);

        if (SUCCEEDED(hr))
        {
            D2D1_COLOR_F c = D2D1::ColorF(D2D1::ColorF::Red);
            if (color == 1)
            {
                c = D2D1::ColorF(D2D1::ColorF::Blue);
            }
            if (color == 2)
            {
                c = D2D1::ColorF(D2D1::ColorF::Green);
            }
            
            hr = pRenderTarget->CreateSolidColorBrush(c, &pBrush);

            if (SUCCEEDED(hr))
            {
                CalculateLayout(x, y);
            }
        }
    }
    return hr;
}

void DrawHelper::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
}

void DrawHelper::OnPaint(int x, int y, int color)
{
    HRESULT hr = CreateGraphicsResources(x, y, color);
    if (SUCCEEDED(hr))
    {
        pRenderTarget->BeginDraw();

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
       
        pRenderTarget->FillEllipse(ellipse, pBrush);

        hr = pRenderTarget->EndDraw();
    }
}

void DrawHelper::Resize()
{
    if (pRenderTarget != NULL)
    {
        RECT rc;
        GetClientRect(DrawHelper::m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        CalculateLayout(5,5);
        InvalidateRect(DrawHelper::m_hwnd, NULL, FALSE);
    }
}