#include "Preset.h"
#include <vector>
#include <cstdlib>

class PointConvex : Preset
{
	
public:

	std::vector<point> points;
	std::vector<point> hulls;
	point target;

	PointConvex();
	~PointConvex();

	void Reset();

	void getOutterHulls();

	void CheckConvex();
};