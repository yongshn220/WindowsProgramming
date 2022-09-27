#pragma once

#include <windows.h>
#include "Preset.h"
#include <d2d1.h>
#include <string>
#pragma comment(lib, "d2d1")

class Draw
{

public:
	HWND hwnd;
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;


	Draw(HWND h) : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
	{
		hwnd = h;
	}

	void Reset();

	void DrawPoint(point p, std::string str);

	void Show(point p);

	D2D1_COLOR_F ConvertString(std::string str);
};