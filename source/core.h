#pragma once
#include "raylib.h"
#include <list>
#include <vector>
#include "global.h"
//#include "tile.h"
//#include "raygui.h"

class Polygon
{
    public:
        std::pmr::vector<Vector2> Points;
};
