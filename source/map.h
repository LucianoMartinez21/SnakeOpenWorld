#pragma once
#include "raylib.h"

class Map{
    public:
        unsigned int TileX;
        unsigned int TileY;
        unsigned char *TileIds;
        unsigned char *TileFog;
};
