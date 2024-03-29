#pragma once

#include "CTypes.h"

typedef struct battlefield {
	Width width;
	Height height;
} BattlefieldStruct; 

typedef struct soldier {
	Point center;
	Radius radius;
	Health health;
} SoldierStruct;

typedef struct bullet {
	Point center;
	Radius radius;
} BulletStruct;

constexpr auto BATTLEFIELD_STRUCT_SIZE = static_cast<int>(sizeof(BattlefieldStruct));
constexpr auto SOLDIER_STRUCT_SIZE = static_cast<int>(sizeof(SoldierStruct));
constexpr auto BULLET_STRUCT_SIZE = static_cast<int>(sizeof(BulletStruct));
