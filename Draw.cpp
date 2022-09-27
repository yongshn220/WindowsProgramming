#include "Draw.h"


void Draw::DrawPoint(point p, std::string str)
{
    Draw::Reset();
    Draw::pRenderTarget->BeginDraw();

    Draw::pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    D2D1_COLOR_F c = Draw::ConvertString(str);
    Draw::pRenderTarget->CreateSolidColorBrush(c, &(Draw::pBrush));
    Draw::Show(p);

    Draw::pRenderTarget->EndDraw();
}

void Draw::Reset()
{
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &(Draw::pFactory));
    HRESULT hr = S_OK;
    RECT rc;
    GetClientRect(hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

    hr = Draw::pFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(Draw::hwnd, size),
        &(Draw::pRenderTarget));

    D2D1_COLOR_F c = D2D1::ColorF(D2D1::ColorF::Green);

    Draw::pRenderTarget->CreateSolidColorBrush(c, &pBrush);
}


void Draw::Show(point p)
{
    D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(p.x, p.y), 4, 4);
    Draw::pRenderTarget->FillEllipse(ellipse, pBrush);
}

D2D1_COLOR_F Draw::ConvertString(std::string str)
{
    std::string black = "black";
    std::string blue = "blue";
    
    if (str.compare(black) == 0) return D2D1::ColorF(D2D1::ColorF::Black);
    if (str.compare(blue) == 0 ) return D2D1::ColorF(D2D1::ColorF::Blue);
    return D2D1::ColorF(D2D1::ColorF::White);
}
