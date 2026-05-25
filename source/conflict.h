#pragma once
#include "tile.h"
#include "player.h"

void CheckCoalition(ObjectTile &Item, Player &Dude);
void CheckCoalition(Tile &Object, Vector2 Position, Player &Dude);
void CheckCoalitionFruit(AppleTile &Object, Player &Dude);
