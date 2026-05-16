#include <cmath>
#include <cstdlib>
#include "tile.h"
#include "player.h"
#include "global.h"
#include "map.h"
#include "raylib.h"
#include "sprite.h"
#include <vector>
using namespace std;

int main(void)
{
    InitWindow(SCREENW, SCREENH, "Snake Game");
    //Declare Map Tiles
    Map MainMap;
    MainMap.TileX = 128;
    MainMap.TileY = 64;
    MainMap.TileIds = (unsigned char *)RL_CALLOC(MainMap.TileX*MainMap.TileY, sizeof(unsigned char));
    MainMap.TileFog = (unsigned char *)RL_CALLOC(MainMap.TileX*MainMap.TileY, sizeof(unsigned char));

    for (unsigned int i = 0; i < MainMap.TileY*MainMap.TileX; i++) MainMap.TileIds[i] = GetRandomValue(0, 1);

    //Initialization of Player and Camera settings
    Player SnakeDude;
    SnakeDude.SetPlayerPos((float) SCREENW/2, (float) SCREENH/2);
    SnakeDude.PlayerTileX = 0;
    SnakeDude.PlayerTileY = 0;
    SnakeDude.Life = 100;
    SnakeDude.SetCamTarget((float) SnakeDude.PlayerPosition.x + PLAYER_SIZE / 2,(float) SnakeDude.PlayerPosition.y + PLAYER_SIZE / 2);
    SnakeDude.InitCamOffset();
    SnakeDude.SetCamRotation(0);
    SnakeDude.SetCamZoom(2.0f);
    SnakeDude.SetPlayerPos((float) (MainMap.TileX*MAP_TILE_SIZE)/2, (float) (MainMap.TileY*MAP_TILE_SIZE)/2);

    //Declare Fog of War Texture
    RenderTexture2D FogOfWar = LoadRenderTexture(MainMap.TileX, MainMap.TileY);
    SetTextureFilter(FogOfWar.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(FogOfWar.texture, TEXTURE_WRAP_CLAMP);

    //Declare a World Tile
    vector <Tile> World;
    vector <AppleTile> Fruits;
    for(int i = 0; i <= 4; i++)
    {
        World.push_back(Tile());
        World[i].IsHarsh = false;
        World[i].TileSprite = Sprite("resource/WorldTile.png", (float)0, (float) 0, 10);
        World[i].SetRangeEffect(InitRanges(i));
        Fruits.push_back(AppleTile());
        Fruits[i].IsHarsh = false;
        Fruits[i].TileSprite = Sprite("resource/FruitTiles.png", 5, 5, 10);
        Fruits[i].Score = 5;
        //TODO: Add the range of effect to world tiles.
    }
    SetTargetFPS(60);
    World[0].IsHarsh = true;


    while(!WindowShouldClose())
    {
        //while (SnakeDude.IsDead == true) {}
        //Handles The Movement
        //TODO?: Make it a function?
        SnakeDude.ControllerHandler();
        SnakeDude.UpdateMovement();

        //Player's Limits in the map
        SnakeDude.CheckMapLimits(MainMap);

        //Camera's Limits in the map
        SnakeDude.CheckCameraMapLimits();

        //Check if the player is in the range
        //World[0].Killzone(SnakeDude);

        //Previous visited Tiles are set to parcial fog
        for (unsigned int i = 0; i < MainMap.TileX*MainMap.TileY; i++) if (MainMap.TileFog[i] == 1) MainMap.TileFog[i] = 2;
        //Stablish the Player's Tile coord. Relative to it's Vec2 Position.
        SnakeDude.PlayerTileX = (int)((SnakeDude.PlayerPosition.x + PLAYER_SIZE/2 + (float) MAP_TILE_SIZE/2)/MAP_TILE_SIZE);
        SnakeDude.PlayerTileY = (int)((MainMap.TileY) - (SnakeDude.PlayerPosition.y + (float)MAP_TILE_SIZE / 2) / MAP_TILE_SIZE);

        //Checks Visibility and update the fog
        // TODO: Make it a function.
        /*for (int y = (SnakeDude.PlayerTileY - PLAYER_TILE_VISIBILITY); y < (SnakeDude.PlayerTileY + PLAYER_TILE_VISIBILITY); y++)
            for (int x = (SnakeDude.PlayerTileX - PLAYER_TILE_VISIBILITY); x < (SnakeDude.PlayerTileX + PLAYER_TILE_VISIBILITY); x++)
                if((x >= 0) && (x < (int)MainMap.TileX) && (y >= 0) && (y < (int)MainMap.TileY))
                    MainMap.TileFog[y*MainMap.TileX + x] = 1;
                    */
        UpdateVision(SnakeDude.PlayerTileX, SnakeDude.PlayerTileY, MainMap);
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
            //DrawText("Move that pixel", 10, 10, 20, DARKGRAY);
            //Draws the background map
            /*for(unsigned int y = 0; y < MainMap.TileY; y++)
            {
                for(unsigned int x = 0; x < MainMap.TileX; x++)
                {
                    DrawRectangle(  x * MAP_TILE_SIZE,
                                    y * MAP_TILE_SIZE,
                                    MAP_TILE_SIZE,
                                    MAP_TILE_SIZE,
                                    (MainMap.TileIds[y * MainMap.TileX + x] == 0)? BLUE : Fade(BLUE, 0.9f));
                    DrawRectangleLines( x * MAP_TILE_SIZE,
                                        y * MAP_TILE_SIZE,
                                        MAP_TILE_SIZE,
                                        MAP_TILE_SIZE,
                                        Fade(DARKBLUE, 0.5f));
                }
                }*/

            //Draws relative to the Player's Camera
            BeginMode2D(SnakeDude.PlayerCamera);
                //Example square
                //DrawRectangleV((Vector2){40,50}, {50,50}, PURPLE);
                //Drawing the world
                for(unsigned int y = 0; y < MainMap.TileY; y++)
                {
                    for(unsigned int x = 0; x < MainMap.TileX; x++)
                    {

                        if(y <= 32 && x <= 32) //32x32 x: 0-32, y: 0-32
                        {
                            World[0].TileSprite.ChangeFrame(0);
                            World[0].TileSprite.DrawSpritePro((Vector2){ (float)x*MAP_TILE_SIZE, (float)y*MAP_TILE_SIZE },(Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE } , (Vector2){ (float)0, (float)0 }, 0.0f);
                        }
                        else if (y > 32 && y <= 64 && x <= 32) //32x32 x: 0-32, y: 32-64
                        {
                            World[1].TileSprite.ChangeFrame(1);
                            World[1].TileSprite.DrawSpritePro((Vector2){ (float)x*MAP_TILE_SIZE, (float)y*MAP_TILE_SIZE },(Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE } , (Vector2){ (float)0, (float)0 }, 0.0f);
                        }
                        else if (y <= 32 && x > 32 && x <= 64) //32x32 x: 32-64, y: 0-32
                        {
                            World[2].TileSprite.ChangeFrame(2);
                            World[2].TileSprite.DrawSpritePro((Vector2){ (float)x*MAP_TILE_SIZE, (float)y*MAP_TILE_SIZE },(Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE } , (Vector2){ (float)0, (float)0 }, 0.0f);
                        }
                        else if (y > 32 && x > 32 && x <= 64 && y <= 64) //32x32 x: 32-64, y: 32-64
                        {
                            World[3].TileSprite.ChangeFrame(3);
                            World[3].TileSprite.DrawSpritePro((Vector2){ (float)x*MAP_TILE_SIZE, (float)y*MAP_TILE_SIZE },(Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE } , (Vector2){ (float)0, (float)0 }, 0.0f);
                        }
                        else if (y <= 32 && x <= 96 && x > 64) //32x32 x: 64-96, y: 0-32
                        {
                            World[4].TileSprite.ChangeFrame(4);
                            World[4].TileSprite.DrawSpritePro((Vector2){ (float)x*MAP_TILE_SIZE, (float)y*MAP_TILE_SIZE },(Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE } , (Vector2){ (float)0, (float)0 }, 0.0f);
                        }
                    }
                }
                Fruits[1].TileSprite.DrawSpritePro((Vector2) {5*MAP_TILE_SIZE,5*MAP_TILE_SIZE}, (Vector2){ MAP_TILE_SIZE, MAP_TILE_SIZE }, (Vector2){ (float)0, (float)0 }, 0.0f);
                //Player's Texture
                DrawRectangleV((SnakeDude.PlayerPosition), (Vector2){PLAYER_SIZE, PLAYER_SIZE}, RED);
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
            DrawText(TextFormat("Current tile: [%i,%i]", SnakeDude.PlayerTileX, SnakeDude.PlayerTileY), 10, 10, 20, RAYWHITE);
            DrawText(TextFormat("Current position: [%f,%f]", SnakeDude.PlayerPosition.x, SnakeDude.PlayerPosition.y), 10, 30, 20, RAYWHITE);
            DrawText(TextFormat("Is Player in WorldTile 0: [%b]", World[0].IsInRange(SnakeDude)), 10, 50, 20, RAYWHITE);
            DrawText(TextFormat("Is Player in WorldTile 1: [%b]", World[1].IsInRange(SnakeDude)), 10, 70, 20, RAYWHITE);
            DrawText(TextFormat("Is Player in WorldTile 2: [%b]", World[2].IsInRange(SnakeDude)), 10, 90, 20, RAYWHITE);
            DrawText(TextFormat("Is Player in WorldTile 3: [%b]", World[3].IsInRange(SnakeDude)), 10, 110, 20, RAYWHITE);
            DrawText(TextFormat("Is Player in WorldTile 4: [%b]", World[4].IsInRange(SnakeDude)), 10, 130, 20, RAYWHITE);
            DrawText(TextFormat("Current Life: [%i]", SnakeDude.Life), 10, 150, 20, RED);
        EndDrawing();
    }

    RL_FREE(MainMap.TileIds);
    RL_FREE(MainMap.TileFog);

    UnloadRenderTexture(FogOfWar);

    CloseWindow();
    return 0;
}
