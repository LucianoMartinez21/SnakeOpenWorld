#include <cmath>
#include <cstdlib>
#include "tile.h"
#include "player.h"
#include "global.h"
#include "map.h"
#include "raylib.h"
#include "sprite.h"
#include "grid.h"
#include <iostream>
#include <vector>
#include "conflict.h"
#include "tilelocation.h"
using namespace std;

int main(void)
{
    InitWindow(SCREENW, SCREENH, "Snake Game");

    //Initialization of Player and Camera settings
    Player SnakeDude;
    SnakeDude.SetPlayerPos(SCREENW/2, SCREENH/2);
    SnakeDude.PlayerTileX = (SCREENW/2)/MAP_TILE_SIZE;
    SnakeDude.PlayerTileY = (SCREENH/2)/MAP_TILE_SIZE;
    SnakeDude.SetCamTarget((float) SnakeDude.PlayerPosition.x + PLAYER_SIZE / 2,(float) SnakeDude.PlayerPosition.y + PLAYER_SIZE / 2);
    SnakeDude.InitCamOffset();
    SnakeDude.SetCamRotation(0);
    SnakeDude.SetCamZoom(2.0f);
    SnakeDude.PlayerSprite = Sprite("resource/SnakeTilesAlt.png", SCREENW/2, SCREENH/2, 10);
    //Fruits[i].TileSprite = Sprite("resource/FruitTiles.png", Fruits[i].TileX * MAP_TILE_SIZE, Fruits[i].TileY * MAP_TILE_SIZE, 10);

    //Declare Map Tiles
    Map MainMap;
    MainMap.TileX = 96;
    MainMap.TileY = 64;
    MainMap.TileIds = (unsigned char *)RL_CALLOC(MainMap.TileX*MainMap.TileY, sizeof(unsigned char));
    MainMap.TileFog = (unsigned char *)RL_CALLOC(MainMap.TileX*MainMap.TileY, sizeof(unsigned char));

    for (unsigned int i = 0; i < MainMap.TileY*MainMap.TileX; i++) MainMap.TileIds[i] = GetRandomValue(0, 1);

    MetaTiles MetaMap;
    MetaMap.MTileX = MainMap.TileX/8;
    MetaMap.MTileY = MainMap.TileY/8;

    //Declare Fog of War Texture
    RenderTexture2D FogOfWar = LoadRenderTexture(MainMap.TileX, MainMap.TileY);
    SetTextureFilter(FogOfWar.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(FogOfWar.texture, TEXTURE_WRAP_CLAMP);

    //Declare a World Tile
    vector <Tile> World;
    vector <AppleTile> Fruits;
    vector <Tile> Corals;
    //Grid WorldGrid;
    for(int i = 0; i <= 4; i++)
    {
        World.push_back(Tile());
        World[i].IsHarsh = false;
        World[i].TileSprite = Sprite("resource/WorldTile.png", (float)0, (float) 0, 10);
        //World[i].SetRangeEffect(InitRanges(i));
        World[i].TileSprite.ChangeFrame(i);
        /*Fruits.push_back(AppleTile());
        Fruits[i].IsHarsh = false;
        Fruits[i].TileX = 1 + i;
        Fruits[i].TileY = 1 + i;
        Fruits[i].hasBeingUsed = false;
        Fruits[i].TileSprite = Sprite("resource/FruitTiles.png", Fruits[i].TileX * MAP_TILE_SIZE, Fruits[i].TileY * MAP_TILE_SIZE, 10);
        Fruits[i].Score = 5;*/
        //TODO: Add the range of effect to world tiles.
    }
    LoadTilesLocations(Corals, true, 0, CoralLocations);
    World[2].SetRangeEffect(
        {
            (Vector2){0 * MAP_TILE_SIZE, 0 * MAP_TILE_SIZE},
            (Vector2){32 * MAP_TILE_SIZE, 0 * MAP_TILE_SIZE},
            (Vector2){32 * MAP_TILE_SIZE, 8 * MAP_TILE_SIZE},
            (Vector2){16 * MAP_TILE_SIZE, 8 * MAP_TILE_SIZE},
            (Vector2){16 * MAP_TILE_SIZE, 16 * MAP_TILE_SIZE},
            (Vector2){8 * MAP_TILE_SIZE, 16 * MAP_TILE_SIZE},
            (Vector2){8 * MAP_TILE_SIZE, 56 * MAP_TILE_SIZE},
            (Vector2){48 * MAP_TILE_SIZE, 56 * MAP_TILE_SIZE},
            (Vector2){48 * MAP_TILE_SIZE, 48 * MAP_TILE_SIZE},
            (Vector2){80 * MAP_TILE_SIZE, 48 * MAP_TILE_SIZE},
            (Vector2){80 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE},
            (Vector2){96 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE},
            (Vector2){96 * MAP_TILE_SIZE, 64 * MAP_TILE_SIZE},
            (Vector2){0 * MAP_TILE_SIZE, 64 * MAP_TILE_SIZE}
        }
    );
    SetTargetFPS(60);
    World[2].IsHarsh = true;

    while(!WindowShouldClose())
    {
        //Handles The Movement and Camera following
        SnakeDude.ControllerHandler();
        SnakeDude.UpdateMovement();
        SnakeDude.FollowTarget();

        //Player's Limits in the map
        SnakeDude.CheckMapLimits(MainMap);

        //Camera's Limits in the map
        SnakeDude.CheckCameraMapLimits();

        //Previous visited Tiles are set to parcial fog
        for (unsigned int i = 0; i < MainMap.TileX*MainMap.TileY; i++) if (MainMap.TileFog[i] == 1) MainMap.TileFog[i] = 2;
        //Stablish the Player's Tile coord. Relative to it's Vec2 Position.
        int fogTileX = (int)((SnakeDude.PlayerPosition.x + MAP_TILE_SIZE / 2.0f) / MAP_TILE_SIZE);
        int fogTileY = (int)((SnakeDude.PlayerPosition.y + MAP_TILE_SIZE / 2.0f) / MAP_TILE_SIZE);

        int MetaPlayerTileX, MetaPlayerTileY;
        MetaPlayerTileX = SnakeDude.PlayerTileX/8;
        MetaPlayerTileY = SnakeDude.PlayerTileY/8;

        //Checks Visibility and update the fog
        // TODO: Make it a function.
        UpdateVision(fogTileX, 63-fogTileY, MainMap);

        //Screen Draws
        BeginTextureMode(FogOfWar);
            ClearBackground(BLANK);
            for (unsigned int y = 0; y < MainMap.TileY; y++)
                for (unsigned int x = 0; x < MainMap.TileX; x++)
                    if(MainMap.TileFog[y * MainMap.TileX + x] == 0) DrawRectangle(x, y, 1, 1, BLACK);
                    else if (MainMap.TileFog[y * MainMap.TileX + x] == 2) DrawRectangle(x, y, 1, 1, Fade(BLACK, 0.8f));
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            //Draws relative to the Player's Camera
            BeginMode2D(SnakeDude.PlayerCamera);
                //Drawing the world
                for(unsigned int y = 0; y < MainMap.TileY; y++)
                {
                    for(unsigned int x = 0; x < MainMap.TileX; x++)
                    {
                        DrawDesert(x, y, World[0]);
                        DrawDeepOcean(x, y, World[2]);
                        DrawSnowField(x, y, World[3]);
                        DrawField(x, y, World[4]);
                        DrawShallowWaters(x, y, World[1]);
                    }
                }
                //Draw Fruits
                for (int i = 0; i < Fruits.size(); i++)
                {
                    CheckCoalition(Fruits[i], SnakeDude);
                    SnakeDude.CheckCoalition();
                    if(Fruits[i].hasBeingUsed)
                        continue;
                    if(isVisible(Fruits[i], SnakeDude.PlayerCamera))
                    {
                        Fruits[i].TileSprite.DrawSpritePro(
                            (Vector2){Fruits[i].TileSprite.SpritePosition.x,
                                    Fruits[i].TileSprite.SpritePosition.y},
                            (Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE },
                            (Vector2){ (float)0, (float)0 }, 0.0f
                        );
                    }
                }

                //Player's Texture
                //DrawRectangleV((SnakeDude.PlayerPosition), (Vector2){PLAYER_SIZE, PLAYER_SIZE}, RED);
                SnakeDude.DrawPlayer();
                //Fog of War Texture
                DrawTexturePro( FogOfWar.texture,
                                (Rectangle){ 0, 0, (float)FogOfWar.texture.width, (float)FogOfWar.texture.height },
                                (Rectangle){ 0, 0, (float)MainMap.TileX*MAP_TILE_SIZE, (float)MainMap.TileY*MAP_TILE_SIZE },
                                (Vector2) { 0, 0 }, 0.0f, WHITE);
            EndMode2D();
            if(SnakeDude.IsDead == true)
            {
                DrawText("Game Over", SCREENW/2, SCREENH/2, 20, RED);
            }
            DrawText(TextFormat("Current tile: [%i,%i]", SnakeDude.PlayerTileX, YInvertedFix(SnakeDude.PlayerTileY, MainMap.TileY)), 10, 10, 20, RAYWHITE);
            DrawText(TextFormat("Current position: [%f,%f]", SnakeDude.PlayerPosition.x, SnakeDude.PlayerPosition.y), 10, 30, 20, RAYWHITE);
            DrawText(TextFormat("Current metatile: [%i,%i]", MetaPlayerTileX, YInvertedFix(MetaPlayerTileY, MetaMap.MTileY)), 10, 50, 20, RAYWHITE);
            DrawText(TextFormat("Current Score: [%i]", SnakeDude.Score), 10, 70, 20, RAYWHITE);
            //DrawText(TextFormat("Is Player in WorldTile 0: [%b]", World[0].IsInRange(SnakeDude)), 10, 50, 20, RAYWHITE);
            //DrawText(TextFormat("Is Player in WorldTile 1: [%b]", World[1].IsInRange(SnakeDude)), 10, 70, 20, RAYWHITE);
            //DrawText(TextFormat("Is Player in WorldTile 2: [%b]", World[2].IsInRange(SnakeDude)), 10, 90, 20, RAYWHITE);
            //DrawText(TextFormat("Is Player in WorldTile 3: [%b]", World[3].IsInRange(SnakeDude)), 10, 110, 20, RAYWHITE);
            //DrawText(TextFormat("Is Player in WorldTile 4: [%b]", World[4].IsInRange(SnakeDude)), 10, 130, 20, RAYWHITE);
            DrawText(TextFormat("Current Life: [%i]", SnakeDude.Life), 10, 150, 20, RED);
        EndDrawing();
    }

    RL_FREE(MainMap.TileIds);
    RL_FREE(MainMap.TileFog);

    UnloadRenderTexture(FogOfWar);

    CloseWindow();
    return 0;
}
