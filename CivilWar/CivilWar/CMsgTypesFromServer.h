#pragma once

constexpr auto BATTLEFIELD_MSG_TYPE = static_cast<char>(1);

constexpr auto SOLDIER_MSG_TYPE = static_cast<char>(2);
constexpr auto GREEN_SOLDIER = static_cast<char>(1);
constexpr auto BLUE_SOLDIER = static_cast<char>(2);

constexpr auto BULLETS_MSG_TYPE = static_cast<char>(3);
constexpr auto GREEN_BULLETS = static_cast<char>(1);
constexpr auto BLUE_BULLETS = static_cast<char>(2);

constexpr auto GAME_STATE_MSG_TYPE = static_cast<char>(4);
constexpr auto GREEN_WIN = static_cast<char>(1);
constexpr auto BLUE_WIN = static_cast<char>(2);
