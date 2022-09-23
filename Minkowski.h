#pragma once
#include "Preset.h"
#include "CalculationHelper.h"

class Minkowski : Preset
{

public:
	std::vector<point> pointsA;
	std::vector<point> hullsA;
	std::vector<point> pointsB;
	std::vector<point> hullsB;

	std::vector<point> sumPoints;
	std::vector<point> diffPoints;

	bool ishit;

	Minkowski()
	{
		Reset();
	}
	~Minkowski()
	{
	}

	void Reset();

	void Calculate();
};