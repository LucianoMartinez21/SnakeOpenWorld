#pragma once
//#include "player.h"
#include "raylib.h"
#include "global.h"

class Map{
    public:
        unsigned int TileX;
        unsigned int TileY;
        unsigned char *TileIds;
        unsigned char *TileFog;
};
void UpdateVision(int TileX, int TileY, Map &Mapa);
