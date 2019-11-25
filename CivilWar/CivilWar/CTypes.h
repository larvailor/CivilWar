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

enum class DirectionX { LEFT, RIGHT, NONE_X };
enum class DirectionY { UP, DOWN, NONE_Y };
