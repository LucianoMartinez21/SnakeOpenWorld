#pragma once
#include "core.h"
#include "global.h"
#include "player.h"
#include "sprite.h"
#include <cstdint>
#include <raylib.h>
#include <vector>
#include "map.h"

class Tile{
    public:
        int TileX, TileY;
        //bool CanKill;
        bool IsHarsh;
        bool hasBeingUsed = false;
        Sprite TileSprite;
        Tile();
        void SetRangeEffect(Rectangle Area);
        void SetRangeEffect(std::pmr::list<Vector2> Points);
        Rectangle GetRange();
        void Killzone(Player &Dude);
        bool IsInRange(Player &Dude);
        virtual ~Tile() {}
    private:
        bool IsPlayerInRange;
        Rectangle RangeOfEffect;
        unsigned short int Drainer;
        Polygon PolyRangeOfEffect;

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

class GroupTile
{
    public:
        bool IsNearPlayer = false;
        Vector2 Center;
        std::pmr::vector<Tile> Collection;
        bool DistanceFromPlayer(Player Dude);
};

typedef enum ObjectType{
    FLOATS = 1,
    SCARF = 2,
    SUNGLASSES = 3
}ObjectType;

Rectangle InitRanges(int i);
void DrawLimitWalls(int x, int y, Tile &Wall);
void DrawDeepOcean(int x, int y, Tile &DeepWater);
void DrawField(int x, int y, Tile &Grass);
void DrawSnowField(int x, int y, Tile &Snow);
void DrawShallowWaters(int x, int y, Tile &ShallowWater);
void DrawDesert(int x, int y, Tile &Sand);
bool RayCastPolygon(Vector2 Position, Polygon &Poly);
bool isVisible(Tile Object, Camera2D MainCam);
bool isNear(Vector2 &Location, Camera2D MainCam);

void LoadTilesLocations(std::vector<Tile> &TileObjects, bool IsHarsh, int frame, Vector2 Locations[], int ArraySize);
void LoadAppleTilesLocations(std::vector<AppleTile> &TileObjects, Vector2 Locations[]);
