#include "conflict.h"
#include "tile.h"
#include <iostream>

void CheckCoalition(Tile &Object, Player &Dude)
{
    AppleTile* Aux = dynamic_cast<AppleTile*>(&Object);
    if(Aux->hasBeingUsed)
        return ;
    int YPlayer = YInvertedFix(Dude.PlayerTileY, 64);
    if(Object.TileX == Dude.PlayerTileX && Object.TileY == YPlayer)
    {
        std::cout << "hola2";
        if(Object.IsHarsh)
            Dude.IsDead = true;
        else
        {
            Dude.Score += Aux->Score;
            Aux->hasBeingUsed = true;
            Dude.TailLen += 1;
        }
    }

}
