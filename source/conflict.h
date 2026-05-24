#pragma once
#include "tile.h"
#include "player.h"

void CheckCoalition(ObjectTile &Item, Player &Dude);
void CheckCoalition(Tile &Object, Vector2 Position, Player &Dude);
void CheckCoalitionFruit(AppleTile &Object, Player &Dude);
/*void Coalition(); //Coalition of the player and a wall or itself
void InadequateEnviroment(); //Harsh conditions of the enviroment will start slowly killing the player
void PositiveCoalition(AppleTile Fruit);
*/
