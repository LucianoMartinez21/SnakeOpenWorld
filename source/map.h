#pragma once
#include "raylib.h"
#include "global.h"
#include <cstdlib>

class Map{
    public:
        unsigned int TileX;
        unsigned int TileY;
        unsigned char *TileIds;
        unsigned char *TileFog;
};

class MetaTiles
{
    public:
        unsigned int MTileX;
        unsigned int MTileY;
};
void UpdateVision(int TileX, int TileY, Map &Mapa);
int YInvertedFix(int TileY, int HeightSize);
