#pragma once

constexpr auto SERVER_IP = "127.0.0.1";
constexpr auto SERVER_PORT = 8080;

constexpr auto BATTLEFIELD_WIDTH = 1000.0f;
constexpr auto BATTLEFIELD_HEIGHT = 600.0f;

constexpr auto GREEN_SOLDIER_START_X = BATTLEFIELD_WIDTH * 0.15f;
constexpr auto GREEN_SOLDIER_START_Y = BATTLEFIELD_HEIGHT * 0.5f;
constexpr auto GREEN_SOLDIER_RADIUS  = BATTLEFIELD_HEIGHT * 0.05f;
constexpr auto GREEN_SOLDIER_HEALTH  = 1;
constexpr auto GREEN_SOLDIER_SPEED   = 10;

constexpr auto BLUE_SOLDIER_START_X = BATTLEFIELD_WIDTH - (BATTLEFIELD_WIDTH * 0.15f);
constexpr auto BLUE_SOLDIER_START_Y = BATTLEFIELD_HEIGHT * 0.5f;
constexpr auto BLUE_SOLDIER_RADIUS  = BATTLEFIELD_HEIGHT * 0.05f;
constexpr auto BLUE_SOLDIER_HEALTH  = 1;
constexpr auto BLUE_SOLDIER_SPEED   = 10;

constexpr auto BULLET_RADIUS = BATTLEFIELD_HEIGHT * 0.005f;
constexpr auto BULLET_SPEED  = 5;
