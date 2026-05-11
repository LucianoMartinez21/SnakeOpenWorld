#pragma once
#include "global.h"

class Tile{
    public:
        int TileX, TileY;
        bool CanKill;
        //Sprite
};

class AppleTile : public Tile
{
    public:
        unsigned short int Score;
};

typedef enum ObjectType{
    FLOATS,
    JACKET,
    SUNGLASSES
}ObjectType;
