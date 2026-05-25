#include "tile.h"
#include "core.h"
#include "global.h"
#include "player.h"
#include "sprite.h"
#include <cstdio>
#include <ctime>
#include <list>
#include <raylib.h>

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

bool RayCastPolygon(Vector2 Position, Polygon &Poly)
{
    int Polysize = Poly.Points.size();
    bool inside = false;
    for(int i = 0, j = Polysize - 1; i < Polysize; j = i++)
    {
        float Xi = Poly.Points[i].x, Yi = Poly.Points[i].y;
        float Xj = Poly.Points[j].x, Yj = Poly.Points[j].y;
        bool Intersects = ((Yi > Position.y) != (Yj > Position.y)) &&
            (Position.x < (Xj - Xi) * (Position.y - Yi) / (Yj -Yi) + Xi);
        if (Intersects)
            inside = !inside;
    }
    return inside;
}

bool Tile::IsInRange(Player &Dude)
{
    if(!IsHarsh)
    {
        IsPlayerInRange = false;
        return IsPlayerInRange;
    }

    if(!PolyRangeOfEffect.Points.empty())
    {
        if(RayCastPolygon(Dude.PlayerPosition, PolyRangeOfEffect))
        {
            IsPlayerInRange = true;
            Killzone(Dude);
        }
    }
    else if( Dude.PlayerPosition.x >= RangeOfEffect.x &&
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
        case 0: //desert
        Area = (Rectangle) {16 * MAP_TILE_SIZE, 24 * MAP_TILE_SIZE, (48-1) * MAP_TILE_SIZE, (48-1) * MAP_TILE_SIZE};
        break;
        case 3: //Snow
        Area = (Rectangle) {32 * MAP_TILE_SIZE, 1 * MAP_TILE_SIZE, (95-1) * MAP_TILE_SIZE, (16-1) * MAP_TILE_SIZE};
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

void DrawShallowWaters(int x, int y, Tile &ShallowWater)
{
    //16x8 -> 32x16
    if((y >= 8 && y < 16) && (x >= 16 && x < 32))
    {
        ShallowWater.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
    // 16x16 48x24
    else if((y >= 16 && y < 24) && (x >= 16 && x < 48))
    {
        ShallowWater.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
    //8x16 -> 16x56
    else if((y >= 16 && y < 56) && (x >= 8 && x < 16))
    {
        ShallowWater.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
    //16x48 -> 48x56
    else if((y >= 48 && y < 56) && (x >= 16 && x < 48))
    {
        ShallowWater.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
}


void DrawDesert(int x, int y, Tile &Sand)
{
    //16x24 -> 48x48
    if((y >= 24 && y < 48) && (x >= 16 && x < 48))
    {
        Sand.TileSprite.DrawSpritePro(
            (Vector2) { (float)x * MAP_TILE_SIZE, (float)y * MAP_TILE_SIZE },
            (Vector2) { MAP_TILE_SIZE, MAP_TILE_SIZE },
            (Vector2) { 0, 0 },
            0.0f
        );
    }
}

void Tile::SetRangeEffect(std::pmr::list<Vector2> Points)
{
    for(Vector2 Point : Points)
        PolyRangeOfEffect.Points.push_back(Point);
}

bool isVisible(Tile Object, Camera2D MainCam)
{
    Vector2 TopLeft = GetScreenToWorld2D({0, 0}, MainCam);
    Vector2 BottomRight = GetScreenToWorld2D({(float) SCREENW, (float) SCREENH}, MainCam);
    return (Object.TileX*MAP_TILE_SIZE) + MAP_TILE_SIZE > TopLeft.x &&
        (Object.TileX*MAP_TILE_SIZE) < BottomRight.x &&
        (Object.TileY*MAP_TILE_SIZE) + MAP_TILE_SIZE > TopLeft.y &&
        (Object.TileY*MAP_TILE_SIZE) < BottomRight.y;
}

bool isNear(Vector2 &Location, Camera2D MainCam)
{
    Vector2 TopLeft = GetScreenToWorld2D({0, 0}, MainCam);
    Vector2 BottomRight = GetScreenToWorld2D({(float) SCREENW, (float) SCREENH}, MainCam);
    return (Location.x*MAP_TILE_SIZE) + MAP_TILE_SIZE > TopLeft.x &&
        (Location.x*MAP_TILE_SIZE) < BottomRight.x &&
        (Location.y*MAP_TILE_SIZE) + MAP_TILE_SIZE > TopLeft.y &&
        (Location.y*MAP_TILE_SIZE) < BottomRight.y;
}

void LoadTilesLocations(std::vector<Tile> &TileObjects, bool IsHarsh, int frame, Vector2 Locations[], int ArraySize)
{
    for(int i = 0; i < ArraySize; i++)
    {
        TileObjects.push_back(Tile());
        TileObjects[i].IsHarsh = IsHarsh;
        TileObjects[i].TileX = Locations[i].x;
        TileObjects[i].TileY = Locations[i].y;
        TileObjects[i].TileSprite = Sprite("resource/ObstaclesTiles.png", TileObjects[i].TileX * MAP_TILE_SIZE, TileObjects[i].TileY * MAP_TILE_SIZE, 10);
        TileObjects[i].TileSprite.ChangeFrame(frame);
    }
}
void LoadAppleTilesLocations(std::vector<AppleTile> &TileObjects, Vector2 Locations[])
{
    for(int i = 0; i < 55; i++)
    {
        TileObjects.push_back(AppleTile());
        TileObjects[i].IsHarsh = false;
        TileObjects[i].TileX = Locations[i].x;
        TileObjects[i].TileY = Locations[i].y;
        TileObjects[i].hasBeingUsed = false;
        TileObjects[i].TileSprite = Sprite("resource/FruitTiles.png", TileObjects[i].TileX * MAP_TILE_SIZE, TileObjects[i].TileY * MAP_TILE_SIZE, 10);
        TileObjects[i].TileSprite.ChangeFrame(0);
        TileObjects[i].Score = 5;
    }
}
