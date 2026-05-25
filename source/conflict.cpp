#include "conflict.h"
#include "init.h"
#include "tile.h"
#include <raylib.h>

void CheckCoalition(ObjectTile &Item, Player &Dude)
{
    if(Item.hasBeingUsed)
        return ;
    int YPlayer = YInvertedFix(Dude.PlayerTileY, 64);
    if(Item.TileX == Dude.PlayerTileX && Item.TileY == YPlayer)
    {
        SnakeDude.AddInventory(Item.Object);
        Item.hasBeingUsed = true;
    }

}
void CheckCoalition(Tile &Object, Vector2 Position, Player &Dude)
{

    int YPlayer = YInvertedFix(Dude.PlayerTileY, 64);
    if(Position.x == Dude.PlayerTileX && Position.y == YPlayer)
    {
        if(Object.IsHarsh)
            Dude.IsDead = true;
    }

}
void CheckCoalitionFruit(AppleTile &Object, Player &Dude)
{
    if(Object.hasBeingUsed)
        return ;
    int YPlayer = YInvertedFix(Dude.PlayerTileY, 64);
    if(Object.TileX == Dude.PlayerTileX && Object.TileY == YPlayer)
    {
        Dude.Score += Object.Score;
        Object.hasBeingUsed = true;
        Dude.TailLen += 1;
        if(Dude.Life <= 100)
            Dude.Life += Object.Score * 2;
        if(Dude.Life > 100)
            Dude.Life = 100;
    }
}
