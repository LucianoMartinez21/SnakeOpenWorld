#include "tile.h"
#include "player.h"
#include "sprite.h"
#include <ctime>
#include <raylib.h>

/*Tile::Tile()
{
    TileSprite = Sprite("", 0, 0, 0);
    }*/
Tile::Tile() : TileSprite("", 0.0f, 0.0f, 0)
{
    TileX = 0;
    TileY = 0;
    IsHarsh = false;
    Drainer = 1;
}

void Tile::SetRangeEffect(Rectangle Area)
{
    RangeOfEffect = Area;
}
Rectangle Tile::GetRange()
{
    return RangeOfEffect;
}
bool Tile::IsInRange(Player Dude)
{
    if( Dude.PlayerPosition.x >= RangeOfEffect.x &&
        Dude.PlayerPosition.x <= RangeOfEffect.width &&
        Dude.PlayerPosition.y >= RangeOfEffect.y &&
        Dude.PlayerPosition.y <= RangeOfEffect.height)
        {
            IsPlayerInRange = true;
        }
    else {
        IsPlayerInRange = false;
    }
    return IsPlayerInRange;
}
void Tile::Killzone(Player &Dude)
{

    if(!IsHarsh)
        return ;
    if(!IsPlayerInRange)
        return ;
    Dude.Life -= Drainer;
    if(Dude.Life <= 0)
        Dude.IsDead = true;
}

Rectangle InitRanges(int i)
{
    Rectangle Area;
    switch (i) {
        case 0:
        Area = (Rectangle) {0 * MAP_TILE_SIZE, 0 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE};
        break;
        case 1:
        Area = (Rectangle) {0 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE, 64 * MAP_TILE_SIZE};
        break;
        case 2:
        Area = (Rectangle) {32 * MAP_TILE_SIZE, 0 * MAP_TILE_SIZE, 64 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE};
        break;
        case 3:
        Area = (Rectangle) {32 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE, 64 * MAP_TILE_SIZE, 64 * MAP_TILE_SIZE};
        break;
        case 4:
        Area = (Rectangle) {64 * MAP_TILE_SIZE, 0 * MAP_TILE_SIZE, 96 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE};
        break;
        case 5:
        //Area = (Rectangle) {64 * MAP_TILE_SIZE, 0 * MAP_TILE_SIZE, 96 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE};
        break;
        case 6:
        //Area = (Rectangle) {0 * MAP_TILE_SIZE, 0 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE};
        break;

    }
    return Area;
}
