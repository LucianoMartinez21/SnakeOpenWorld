#include "core.h"
#include "init.h"
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
    InitCore();
    InitShader();
    SetTargetFPS(60);
    double lastMoveTime = 0.0;
    float seconds = 0.0;
    bool UpDown = false; //false up, true down
    while(!WindowShouldClose())
    {
        seconds = GetTime();
        SetShaderValue(ShaderBackground, LocTime, &seconds, SHADER_UNIFORM_FLOAT);
        switch (GameFlow) {
            case MAIN_MENU:
                BeginDrawing();
                ClearBackground(BLACK);
                    BeginShaderMode(ShaderBackground);
                        DrawTexture(MainMenu, 0, 0, WHITE);
                        DrawTexture(MainMenu, MainMenu.width, 0, Fade(WHITE, 0));
                    EndShaderMode();
                    DrawText("SnakeDude Adventure", (SCREENW/2)-(19*20), SCREENH/2, 20, RAYWHITE);
                    if(IsKeyPressed(KEY_DOWN) or IsKeyPressed(KEY_UP)) UpDown = !UpDown;
                    if(UpDown == false)
                    {
                        DrawText(">Play", (SCREENW/2)-(19*20), (SCREENH/2)+50, 20, RAYWHITE);
                        DrawText("Credits", (SCREENW/2)-(19*20), (SCREENH/2)+75, 20, RAYWHITE);
                        if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
                        {
                            GameFlow = PLAYING;
                            InitCore();
                        }
                    }
                    else
                    {
                        DrawText("Play", (SCREENW/2)-(19*20), (SCREENH/2)+50, 20, RAYWHITE);
                        DrawText(">Credits", (SCREENW/2)-(19*20), (SCREENH/2)+75, 20, RAYWHITE);
                        if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
                            GameFlow = CREDITS;
                    }
                EndDrawing();
                break;
            case CREDITS:
                BeginDrawing();
                ClearBackground(BLACK);
                Secrets();
                    BeginShaderMode(ShaderBackground);
                        DrawTexture(MainMenu, 0, 0, WHITE);
                        DrawTexture(MainMenu, MainMenu.width, 0, Fade(WHITE, 0));
                    EndShaderMode();
                    DrawText("SnakeDude Adventure", (SCREENW/2)-(19*20), SCREENH/2, 20, RAYWHITE);
                    DrawText("Created by Luciano Martínez", (SCREENW/2)-(19*20), (SCREENH/2)+50, 20, RAYWHITE);
                    DrawText("Designed by Luciano Martínez", (SCREENW/2)-(19*20), (SCREENH/2)+70, 20, RAYWHITE);
                    DrawText("Programmed by Luciano Martínez", (SCREENW/2)-(19*20), (SCREENH/2)+90, 20, RAYWHITE);
                    DrawText("Made in Raylib", (SCREENW/2)-(19*20), (SCREENH/2)+110, 20, RAYWHITE);
                    DrawText(">Back", (SCREENW/2)-(19*20), (SCREENH/2)+130, 20, RAYWHITE);
                    if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
                        GameFlow = MAIN_MENU;
                EndDrawing();
                break;
            case PLAYING:
                //Handles The Movement and Camera following
                const float MOVE_DELAY = 0.15f;
                double now = GetTime();
                if (now - lastMoveTime >= MOVE_DELAY) {
                    lastMoveTime = now;
                    SnakeDude.UpdateMovement();
                }
                SnakeDude.ControllerHandler();
                SnakeDude.FollowTarget();
                //Player's Limits in the map
                SnakeDude.CheckMapLimits(MainMap);
                //Camera's Limits in the map
                SnakeDude.CheckCameraMapLimits();
                //Check if player has colide with itself.
                SnakeDude.CheckCoalition();
                SnakeDude.CheckKeyItem();
                //Previous visited Tiles are set to parcial fog
                for (unsigned int i = 0; i < MainMap.TileX*MainMap.TileY; i++) if (MainMap.TileFog[i] == 1) MainMap.TileFog[i] = 2;
                //Stablish the Player's Tile coord. Relative to it's Vec2 Position.
                int fogTileX = (int)((SnakeDude.PlayerPosition.x + MAP_TILE_SIZE / 2.0f) / MAP_TILE_SIZE);
                int fogTileY = (int)((SnakeDude.PlayerPosition.y + MAP_TILE_SIZE / 2.0f) / MAP_TILE_SIZE);
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
                    //ClearBackground(RAYWHITE);
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
                                DrawLimitWalls(x, y, Wall);
                            }
                        }
                        cout << World[0].IsHarsh << endl;
                        World[0].IsInRange(SnakeDude);
                        World[2].IsInRange(SnakeDude);
                        World[3].IsInRange(SnakeDude);
                        SnakeDude.CheckCoalition();
                        //Draw Fruits
                        for (int i = 0; i < Fruits.size(); i++)
                        {
                            if(Fruits[i].hasBeingUsed)
                                continue;
                            CheckCoalitionFruit(Fruits[i], SnakeDude);
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
                        for(int i = 0 ; i < 3; i++)
                        {
                            if(KeyObjects[i].hasBeingUsed)
                                continue;
                            CheckCoalition(KeyObjects[i], SnakeDude);
                            if(isVisible(KeyObjects[i], SnakeDude.PlayerCamera))
                            {
                                KeyObjects[i].TileSprite.DrawSpritePro(
                                    (Vector2){(float)KeyObjects[i].TileX * MAP_TILE_SIZE,
                                            (float)KeyObjects[i].TileY * MAP_TILE_SIZE},
                                    (Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE },
                                    (Vector2){ (float)0, (float)0 }, 0.0f
                                );
                            }
                        }
                        for(int i = 0; i < 401; i++)
                        {
                            //j = ((i + 1) % 90);
                            //cout << "test value: " << j << "\niteration: " << i << endl;
                            if(isNear(CoralLocations[i], SnakeDude.PlayerCamera))
                            {
                                Obstacles[0].TileSprite.DrawSpritePro(
                                    (Vector2){CoralLocations[i].x * MAP_TILE_SIZE,
                                            CoralLocations[i].y * MAP_TILE_SIZE},
                                    (Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE },
                                    (Vector2){ (float)0, (float)0 }, 0.0f
                                );
                            }
                            CheckCoalition(Obstacles[0], CoralLocations[i], SnakeDude);

                            if(isNear(TreeLocations[((i + 1) % 90)], SnakeDude.PlayerCamera))
                            {
                                Obstacles[1].TileSprite.DrawSpritePro(
                                    (Vector2){TreeLocations[((i + 1) % 90)].x * MAP_TILE_SIZE,
                                            TreeLocations[((i + 1) % 90)].y * MAP_TILE_SIZE},
                                    (Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE },
                                    (Vector2){ (float)0, (float)0 }, 0.0f
                                );
                            }
                            CheckCoalition(Obstacles[1], TreeLocations[((i + 1) % 90)], SnakeDude);

                            if(isNear(StoneLocations[((i + 1) % 120)], SnakeDude.PlayerCamera))
                            {
                                Obstacles[2].TileSprite.DrawSpritePro(
                                    (Vector2){StoneLocations[((i + 1) % 120)].x * MAP_TILE_SIZE,
                                            StoneLocations[((i + 1) % 120)].y * MAP_TILE_SIZE},
                                    (Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE },
                                    (Vector2){ (float)0, (float)0 }, 0.0f
                                );
                            }
                            CheckCoalition(Obstacles[2], StoneLocations[((i + 1) % 120)], SnakeDude);

                            if(isNear(RockyLocations[((i + 1) % 158)], SnakeDude.PlayerCamera))
                            {
                                Obstacles[3].TileSprite.DrawSpritePro(
                                    (Vector2){RockyLocations[((i + 1) % 158)].x * MAP_TILE_SIZE,
                                            RockyLocations[((i + 1) % 158)].y * MAP_TILE_SIZE},
                                    (Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE },
                                    (Vector2){ (float)0, (float)0 }, 0.0f
                                );
                            }
                            CheckCoalition(Obstacles[3], RockyLocations[((i + 1) % 158)], SnakeDude);

                            if(isNear(QuicksandLocations[((i + 1) % 70)], SnakeDude.PlayerCamera))
                            {
                                Obstacles[4].TileSprite.DrawSpritePro(
                                    (Vector2){QuicksandLocations[((i + 1) % 70)].x * MAP_TILE_SIZE,
                                            QuicksandLocations[((i + 1) % 70)].y * MAP_TILE_SIZE},
                                    (Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE },
                                    (Vector2){ (float)0, (float)0 }, 0.0f
                                );
                            }
                            CheckCoalition(Obstacles[4], QuicksandLocations[((i + 1) % 70)], SnakeDude);
                        }

                        //Player's Texture
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
                        GameFlow = MAIN_MENU;
                    }
                    DrawText(TextFormat("Current Score: [%i]", SnakeDude.Score), 10, 10, 20, RAYWHITE);
                    DrawText(TextFormat("Current Life: [%i]", SnakeDude.Life), 10, 30, 20, RED);
                EndDrawing();
                break;
        }
    }

    RL_FREE(MainMap.TileIds);
    RL_FREE(MainMap.TileFog);

    UnloadRenderTexture(FogOfWar);

    CloseWindow();
    return 0;
}
