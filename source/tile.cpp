#include "tile.h"
#include "sprite.h"

/*Tile::Tile()
{
    TileSprite = Sprite("", 0, 0, 0);
    }*/
Tile::Tile() : TileSprite("", 0.0f, 0.0f, 0)
{
    TileX = 0;
    TileY = 0;
    CanKill = false;
}
