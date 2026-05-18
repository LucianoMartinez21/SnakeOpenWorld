#include "tile.h"
#include "global.h"
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
bool Tile::IsInRange(Player &Dude)
{
    if( Dude.PlayerPosition.x >= RangeOfEffect.x &&
        Dude.PlayerPosition.x <= RangeOfEffect.width &&
        Dude.PlayerPosition.y >= RangeOfEffect.y &&
        Dude.PlayerPosition.y <= RangeOfEffect.height)
        {
            IsPlayerInRange = true;
            Killzone(Dude);
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
    if (!Dude.IsDead)
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

void DrawLimitWalls(int x, int y, Tile &Wall)
{
    if(y == 0 || y == 64)
    {
        Wall.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
    if(x == 0 || x == 96)
    {
        Wall.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
}
void DrawDeepOcean(int x, int y, Tile &DeepWater)
{
    // 1x1 -> 32x8
    if( y >= 1 && y < 8)
    {
        if(x >= 1 && x < 32)
        {
            DeepWater.TileSprite.DrawSpritePro(
                (Vector2) { (float)x* MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
                (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
                (Vector2) { 0, 0 },
                0.0f
            );
        }
    }

    //1x8 -> 16x16
    else if(y >= 8 && y < 16)
    {
        if(x >= 1 && x < 16)
        {
            DeepWater.TileSprite.DrawSpritePro(
                (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
                (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
                (Vector2) { 0, 0 },
                0.0f
            );
        }
    }
    //1x16 -> 8x56
    else if( y >= 16 && y < 56)
    {
        if(x >= 1 && x < 8)
        {
            DeepWater.TileSprite.DrawSpritePro(
                (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
                (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
                (Vector2) { 0, 0 },
                0.0f
            );
        }
    }

    //1x56 -> 48x63
    else if((y >= 56 && y < 63) && (x >= 1 && x < 48))
    {
        DeepWater.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
    //48x48 -> 95x63
    if(y >= 48 && y < 63)
    {
        if(x >= 48 && x < 95)
        {
            DeepWater.TileSprite.DrawSpritePro(
                (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
                (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
                (Vector2) { 0, 0 },
                0.0f
            );
        }
    }
    // 80x32 -> 95x48
    if(y >= 32 && y < 48)
    {
        if(x >= 80 && x < 95)
        {
            DeepWater.TileSprite.DrawSpritePro(
                (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
                (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
                (Vector2) { 0, 0 },
                0.0f
            );
        }
    }
}
void DrawField(int x, int y, Tile &Grass)
{
    // 48x16 -> 80x47
    if((y >= 16 && y < 48) && (x >= 48 && x < 80))
    {
        Grass.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
    // 80x16 -> 95x32
    else if((y >= 16 && y < 32) && (x >= 80 && x < 95))
    {
        Grass.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
}


void DrawSnowField(int x, int y, Tile &Snow)
{
    //32x1 -> 95x16
    if((y >= 1 && y < 16) && (x >= 32 && x < 95))
    {
        Snow.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
}
