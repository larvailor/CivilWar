#pragma once

typedef float Radius;
typedef float Speed;

typedef struct point {
	float X;
	float Y;
} Point;

typedef struct soldier {
	Point center;
	Radius radius;
} Soldier;

enum DirectionX { LEFT, RIGHT, NONE_X };
enum DirectionY { UP, DOWN, NONE_Y };

typedef struct bullet {
	Point center;
	Radius radius;
	DirectionX dirX;
	DirectionY dirY;
	Speed speed;
} Bullet;
