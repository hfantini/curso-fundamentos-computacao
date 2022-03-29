#include <iostream>

#ifndef SYSTEM_RECT
#define SYSTEM_RECT

typedef struct
{
	int x;
	int y;
	int w;
	int h;
} IRect;

typedef struct
{
	float x;
	float y;
	float w;
	float h;
} FRect;

typedef struct
{
	double x;
	double y;
	double w;
	double h;
} DRect;

#endif // !SYSTEM_RECT
