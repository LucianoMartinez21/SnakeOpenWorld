/*//#include "grid.h"
#include "global.h"
//#include "tile.h"
#include <cmath>
#include <raylib.h>
void Grid::Clear()
{
    GridMap.clear();
}

Vector2 Grid::CellKey(Vector2 Position)
{
    Vector2 Key = (Vector2){
        floorf(Position.x/CellSize),
        floorf(Position.y/CellSize)};
    return Key;
}
void Grid::AddToGrid(Tile &Object)
{
    GridMap[CellKey((Vector2){(float)Object.TileSprite.SpritePosition.x, (float)Object.TileSprite.SpritePosition.y})] = Object;
    /Vector2 Key = CellKey((Vector2){(float)Object.TileX*MAP_TILE_SIZE, (float)Object.TileX*MAP_TILE_SIZE});
    if(!(GridMap.find(Key) != GridMap.end()))
        GridMap.insert({Key, Tile()});
        GridMap.at(Key) = Object;*
}
Tile* Grid::GetNearby(Player& Dude)
{
    const float CellX = floorf(Dude.PlayerPosition.x / CellSize);
    const float CellY = floorf(Dude.PlayerPosition.y / CellSize);
    static Tile Objects[255];
    int Index = 0;
    for (int DistanceX = -1; DistanceX <= 1; DistanceX++)
    {
        for(int DistanceY = -1; DistanceY <= 1; DistanceY++)
        {
            Vector2 Key = (Vector2){CellX + DistanceX, CellY + DistanceY};
            if(GridMap.find(Key) != GridMap.end())
            {
                Objects[Index] = GridMap.at(Key);
                Index++;
            }
        }
    }
    return Objects;
}
*/
