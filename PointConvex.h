#include "Preset.h"
#include "CalculationHelper.h"
#include <vector>
#include <cstdlib>

class PointConvex : Preset
{

public:

	std::vector<point> points;
	std::vector<point> hulls;
	point target;
	bool state;

	PointConvex();
	~PointConvex();

	void Reset();

	void CalculateOutterHulls();

	bool IsPointInsideConvex();

	point GetLeftMostPoint(std::vector<point> hulls);

	int GetLastIndexUnderTarget(point leftMostPoint);

};