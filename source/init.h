#pragma once
#include "player.h"
#include "tile.h"
#include "vector"
#include "tilelocation.h"
#include <raylib.h>

extern Player SnakeDude;
extern Map MainMap;
extern RenderTexture2D FogOfWar;
extern std::vector <Tile> World;
extern std::vector <AppleTile> Fruits;
extern std::vector <Tile> Obstacles;
extern GAME_STATE GameFlow;
extern Tile Wall;



void InitCore();

extern int SHeightLoc;
extern int AmplitudLoc;
extern int FrequencyLoc;
extern int SpeedLoc;
extern int AmplitudVertLoc;
extern int FrequencyVertLoc;
extern int SpeedVertLoc;
extern int ScrollDirLoc;
extern int ScrollSpeedLoc;
extern int EnablePaletteLoc;
extern int PaletteLoc;
extern int PaletteSpeedLoc;
extern int LocTime;
extern Shader ShaderBackground;
extern Texture2D MainMenu;
extern ObjectTile KeyObjects[3];
extern std::pmr::vector<int> KeyBuffer;
extern int KeyCounter;
void InitShader();

void Secrets();
