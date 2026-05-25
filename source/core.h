#pragma once
#include "raylib.h"
#include <list>
#include <vector>
#include "global.h"

class Polygon
{
    public:
        std::pmr::vector<Vector2> Points;
};

typedef enum GAME_STATE
{
    MAIN_MENU,
    PLAYING,
    CREDITS
}GSTATE;
