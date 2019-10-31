#pragma once

typedef float Radius;
typedef float Speed;
typedef float Width;
typedef float Height;

typedef struct point {
	float x;
	float y;
} Point;

typedef struct soldier {
	Point center;
	Radius radius;
};

enum DirectionX { LEFT, RIGHT, NONE_X };
enum DirectionY { UP, DOWN, NONE_Y };

typedef struct bullet {
	Point center;
	Radius radius;
	DirectionX dirX;
	DirectionY dirY;
	Speed speed;
};

typedef struct battlefield {
	Width width;
	Height height;
};
