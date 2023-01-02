#pragma once

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTER_X 640
#define CENTER_Y 360

#define GRAVITY 0.98
#define PI 3.141592

#define LERP(s,e,t) s + (e - s) * t // 0 이면 s, 1 이면 e

#define _poolCountX 25
#define _poolCountY 25


enum Dir
{
	DIR_UP,
	DIR_LEFT,
	DIR_DOWN,
	DIR_RIGHT,

	DIR_COUNT = 4
};
