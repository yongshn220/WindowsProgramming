#pragma once
#include "CalculationHelper.h";

point CalculationHelper::lowestPoint = { 0,0 };

CalculationHelper::CalculationHelper()
{
	CalculationHelper::lowestPoint = { 0,0 };
}

std::vector<point> CalculationHelper::GetOutterHulls(std::vector<point> points)
{
	SortByAngle(points);

	std::stack<point> stack;

	stack.push(points[0]);
	stack.push(points[1]);


	for (int i = 2; i < points.size(); i++)
	{
		point next = points[i];
		point p = stack.top();
		stack.pop();

		while (!stack.empty() && !IsCCW(ToVector(stack.top(), p), ToVector(p, next)))
		{
			p = stack.top();
			stack.pop();
		}
		stack.push(p);
		stack.push(next);
	}
	std::vector<point> hulls;
	for (int i = 0; i < stack.size(); i++)
	{
		hulls.push_back(stack.top());
		stack.pop();
	}
	std::reverse(hulls.begin(), hulls.end());
	return hulls;
}

void CalculationHelper::SortByAngle(std::vector<point> points)
{
	CalculationHelper::lowestPoint = getLowestPoint(points);
	std::sort(points.begin(), points.end(), SortByAngleFunc);
}

bool CalculationHelper::SortByAngleFunc(point a, point b)
{
	if (isPointEqual(a, CalculationHelper::lowestPoint)) { return false; }
	if (isPointEqual(b, CalculationHelper::lowestPoint)) { return true; }

	if (IsCCW(ToVector(CalculationHelper::lowestPoint, a), ToVector(CalculationHelper::lowestPoint, b))) { return false; }
	return true;
}

// a -> r -> c
bool CalculationHelper::IsCCW(vector a, vector b)
{
	if (a.x * b.y - a.y * b.x > 0) return true;
	return false;
}

vector CalculationHelper::ToVector(point a, point b)
{
	return { b.x - a.x, b.y - a.y };
}

point CalculationHelper::getLowestPoint(std::vector<point> points)
{
	point minPoint = { 0, 100 };
	for (int i = 0; i < points.size(); i++)
	{
		if (points[i].y < minPoint.y)
		{
			minPoint = points[i];
		}
	}

	return minPoint;
}

bool CalculationHelper::isPointEqual(point a, point b)
{
	return (a.x == b.x && a.y == b.y);
}