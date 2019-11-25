#pragma once

typedef int Radius;
typedef int Speed;
typedef int Width;
typedef int Height;

typedef short Health;

typedef struct point {
	int x;
	int y;
} Point;

enum DirectionX { LEFT, RIGHT, NONE_X };
enum DirectionY { UP, DOWN, NONE_Y };
