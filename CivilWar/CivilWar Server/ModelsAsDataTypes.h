#pragma once

#include "Types.h"

struct battlefield {
	Width width;
	Height height;
};

struct soldier {
	Point center;
	Radius radius;
	Health health;
};

struct bullet {
	Point center;
	Radius radius;
	DirectionX dirX;
	DirectionY dirY;
	Speed speed;
};

constexpr auto BATTLEFIELD_STRUCT_SIZE = static_cast<int>(sizeof(struct battlefield));
constexpr auto SOLDIER_STRUCT_SIZE     = static_cast<int>(sizeof(struct soldier));
constexpr auto BULLET_STRUCT_SIZE      = static_cast<int>(sizeof(struct bullet));
