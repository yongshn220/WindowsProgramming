#include "PointConvex.h"

PointConvex::PointConvex()
{
	Reset();
}
PointConvex::~PointConvex()
{
}

void PointConvex::Reset()
{
	PointConvex::target = {30, 30};

	for (int i = 0; i < 15; i++)
	{
		int x = rand() % PointConvex::MAXWIDTH;
		int y = rand() % PointConvex::MAXHEIGHT;
		PointConvex::points.push_back({x, y});
	}
}

void PointConvex::getOutterHulls()
{

}

void PointConvex::CheckConvex()
{

}
