#pragma once
#include "global.h"
#include "player.h"
#include "sprite.h"
#include <cstdint>
#include <raylib.h>

class Tile{
    public:
        int TileX, TileY;
        bool CanKill;
        Sprite TileSprite;
        Tile();
        void SetRangeEffect(Rectangle Area);
        Rectangle GetRange();
        void Killzone(Player Dude);
    private:
        bool IsHarsh;
        Rectangle RangeOfEffect;
        unsigned short int Drainer;

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
