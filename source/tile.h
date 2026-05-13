#pragma once
#include "global.h"
#include "sprite.h"
#include <cstdint>

class Tile{
    public:
        int TileX, TileY;
        bool CanKill;
        Sprite TileSprite;
        Tile();
};

class AppleTile : public Tile
{
    public:
        unsigned short int Score;
};

class ObjectTile : public Tile
{
    public:
    uint8_t Object;
};

typedef enum ObjectType{
    FLOATS = 1,
    JACKET = 2,
    SUNGLASSES = 3
}ObjectType;
