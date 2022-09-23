#pragma once
#include "Preset.h"
#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>
#include <cmath>

class CalculationHelper
{
public:
	static point lowestPoint;

	CalculationHelper();

	static std::vector<point> GetOutterHulls(std::vector<point> points);

	static std::vector<point> SortByAngle(std::vector<point> points);
	static bool SortByAngleFunc(point a, point b);

	// a -> r -> c
	static int IsCCW(vector a, vector b);

	static vector ToVector(point a, point b);

	static point getLowestPoint(std::vector<point> points);

	static bool isPointEqual(point a, point b);
};