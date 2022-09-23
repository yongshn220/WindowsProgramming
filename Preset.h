#pragma once

class Preset
{

public:
	int MAXWIDTH;
	int MAXHEIGHT;

	Preset()
	{
		MAXWIDTH = 300;
		MAXHEIGHT = 300;
	}
};

struct point
{
	float x;
	float y;
};

struct vector
{
	float x;
	float y;
};
