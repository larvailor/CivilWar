#pragma once

typedef float Radius;
typedef float Speed;
typedef float Width;
typedef float Height;

typedef short Health;

typedef struct point {
	float x;
	float y;
} Point;

enum class DirectionX { LEFT, RIGHT, NONE_X };
enum class DirectionY { UP, DOWN, NONE_Y };
