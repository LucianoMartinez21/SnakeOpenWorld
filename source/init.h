#pragma once
#include "player.h"
#include "tile.h"
#include "vector"
#include "tilelocation.h"

extern Player SnakeDude;
extern Map MainMap;
extern RenderTexture2D FogOfWar;
extern std::vector <Tile> World;
extern std::vector <AppleTile> Fruits;
extern std::vector <Tile> Obstacles;
extern GAME_STATE GameFlow;
extern Tile Wall;

void InitCore();
