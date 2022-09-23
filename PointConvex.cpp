#include "PointConvex.h"

PointConvex::PointConvex() : Preset()
{
	Reset();
}

PointConvex::~PointConvex()
{
}

void PointConvex::Reset()
{
	PointConvex::points = {};
	PointConvex::hulls = {};
	PointConvex::state = false;

	srand(time(NULL));
	point t = { (rand() % PointConvex::MAXWIDTH) / 1.33, (rand() % PointConvex::MAXWIDTH) / 1.33 };
	PointConvex::target = t;
	for (int i = 0; i < 15; i++)
	{
		int x = (rand() % PointConvex::MAXWIDTH) / 1.33;
		int y = (rand() % PointConvex::MAXHEIGHT) / 1.33;
		point p = { x, y };
		PointConvex::points.push_back(p);
	}
	IsPointInsideConvex();
}

void PointConvex::CalculateOutterHulls()
{
	PointConvex::hulls = CalculationHelper::GetOutterHulls(PointConvex::points);
}

bool PointConvex::IsPointInsideConvex()
{
	PointConvex::CalculateOutterHulls();
	

	point lowestHull = CalculationHelper::getLowestPoint(PointConvex::hulls);

	if (PointConvex::target.y < lowestHull.y) return false;

	int lastIndexUnderTarget = GetLastIndexUnderTarget(lowestHull);

	// if the target stays behind of the first and last vector of the outter hullls
	if (lastIndexUnderTarget == 0 || lastIndexUnderTarget == PointConvex::hulls.size() - 1)
	{
		return false;
	}

	vector pToNp = CalculationHelper::ToVector(PointConvex::hulls[lastIndexUnderTarget], PointConvex::hulls[lastIndexUnderTarget + 1]); // vector (point to the next point)
	vector pToT = CalculationHelper::ToVector(PointConvex::hulls[lastIndexUnderTarget], PointConvex::target); // vector (point to target)

	bool result = (CalculationHelper::IsCCW(pToNp, pToT) != -1);

	PointConvex::state = result;
	return result;
}

point PointConvex::GetLeftMostPoint(std::vector<point> hulls)
{
	point lmp = { 101, 0 };
	for (int i = 0; i < PointConvex::hulls.size(); i++)
	{
		point p = PointConvex::hulls[i];
		if (p.x < lmp.x)
		{
			lmp = p;
		}
	}
	return lmp;
}

int PointConvex::GetLastIndexUnderTarget(point lowestPoint)
{
	vector t = CalculationHelper::ToVector(lowestPoint, PointConvex::target);
	vector v;
	int index = 0;


	for (int i = 1; i < PointConvex::hulls.size(); i++)
	{
		v = CalculationHelper::ToVector(PointConvex::hulls[0], PointConvex::hulls[i]);

		if (CalculationHelper::IsCCW(v, t) != -1)
		{
			index = i;
		}
		else { break; }
	}
	return index;
}
