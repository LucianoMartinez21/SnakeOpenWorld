#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "player.h"
#include "global.h"
#include "map.h"
#include "raylib.h"
using namespace std;

int main(void)
{
    InitWindow(SCREENW, SCREENH, "Snake Game");

    Map MainMap;
    MainMap.TileX = 128;
    MainMap.TileY = 64;
    MainMap.TileIds = (unsigned char *)RL_CALLOC(MainMap.TileX*MainMap.TileY, sizeof(unsigned char));
    MainMap.TileFog = (unsigned char *)RL_CALLOC(MainMap.TileX*MainMap.TileY, sizeof(unsigned char));

    for (unsigned int i = 0; i < MainMap.TileY*MainMap.TileX; i++) MainMap.TileIds[i] = GetRandomValue(0, 1);

    Player SnakeDude;
    SnakeDude.SetPlayerPos((float) SCREENW/2, (float) SCREENH/2);
    SnakeDude.PlayerTileX = 0;
    SnakeDude.PlayerTileY = 0;
    SnakeDude.SetCamTarget((float) SnakeDude.PlayerPosition.x + PLAYER_SIZE / 2,(float) SnakeDude.PlayerPosition.y + PLAYER_SIZE / 2);
    //SnakeDude.SetCamTarget(((float) SCREENW/2) + 20.0f, ((float) SCREENH/2) + 20.0f);
    SnakeDude.InitCamOffset();
    SnakeDude.SetCamRotation(0);
    SnakeDude.SetCamZoom(1.0f);
    SnakeDude.SetPlayerPos((float) (MainMap.TileX*MAP_TILE_SIZE)/2, (float) (MainMap.TileY*MAP_TILE_SIZE)/2);
    RenderTexture2D FogOfWar = LoadRenderTexture(MainMap.TileX, MainMap.TileY);
    SetTextureFilter(FogOfWar.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(FogOfWar.texture, TEXTURE_WRAP_CLAMP);

    SetTargetFPS(60);


    while(!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))   {SnakeDude.SetPlayerSpeed(5.0f, 0.0f);}//{AddedValueX = 2; AddedValueY = 0;}//SquarePos.x += 2.0f;
        if (IsKeyDown(KEY_LEFT))    {SnakeDude.SetPlayerSpeed(-5.0f, 0.0f);}//{AddedValueX = -2; AddedValueY = 0;}//SquarePos.x -= 2.0f;
        if (IsKeyDown(KEY_UP))      {SnakeDude.SetPlayerSpeed(0.0f, -5.0f);}//{AddedValueY = -2; AddedValueX = 0;}//SquarePos.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN))    {SnakeDude.SetPlayerSpeed(0.0f, 5.0f);}//{AddedValueY = 2; AddedValueX = 0;}//SquarePos.y += 2.0f;
        //if (IsKeyDown(KEY_RIGHT))   {SnakeDude.PlayerPosition.x += 2;}//{AddedValueX = 2; AddedValueY = 0;}//SquarePos.x += 2.0f;
        //if (IsKeyDown(KEY_LEFT))    {SnakeDude.PlayerPosition.x -= 2;}//{AddedValueX = -2; AddedValueY = 0;}//SquarePos.x -= 2.0f;
        //if (IsKeyDown(KEY_UP))      {SnakeDude.PlayerPosition.y -= 2;}//{AddedValueY = -2; AddedValueX = 0;}//SquarePos.y -= 2.0f;
        //if (IsKeyDown(KEY_DOWN))    {SnakeDude.PlayerPosition.y += 2;}
        SnakeDude.UpdateMovement();
        //FollowTarget();


        if (SnakeDude.PlayerPosition.x < 0) SnakeDude.PlayerPosition.x = 0;
        else if ((SnakeDude.PlayerPosition.x + PLAYER_SIZE) > MainMap.TileX*MAP_TILE_SIZE) SnakeDude.PlayerPosition.x = (float)MainMap.TileX*MAP_TILE_SIZE - PLAYER_SIZE;
        if (SnakeDude.PlayerPosition.y < 0) SnakeDude.PlayerPosition.y = 0;
        else if ((SnakeDude.PlayerPosition.y + PLAYER_SIZE) > MainMap.TileY*MAP_TILE_SIZE) SnakeDude.PlayerPosition.y = (float)MainMap.TileY*MAP_TILE_SIZE - PLAYER_SIZE;

        if (SnakeDude.PlayerCamera.target.x < 0 + (SCREENW/2)) SnakeDude.PlayerCamera.target.x = (float)(0 + SCREENW / 2);
        if (SnakeDude.PlayerCamera.target.x > 4046 - (SCREENW/2)) SnakeDude.PlayerCamera.target.x = (float)(4046 - SCREENW / 2);
        if (SnakeDude.PlayerCamera.target.y < 0 + (SCREENH/2)) SnakeDude.PlayerCamera.target.y = (float)(0 + SCREENH / 2);
        if (SnakeDude.PlayerCamera.target.y > 1997 - (SCREENH/2)) SnakeDude.PlayerCamera.target.y = (float)(1997 - SCREENH / 2);

        for (unsigned int i = 0; i < MainMap.TileX*MainMap.TileY; i++) if (MainMap.TileFog[i] == 1) MainMap.TileFog[i] = 2;

        SnakeDude.PlayerTileX = (int)((SnakeDude.PlayerPosition.x + PLAYER_SIZE/2 + (float) MAP_TILE_SIZE/2)/MAP_TILE_SIZE);
        //SnakeDude.PlayerTileY = (int)((SnakeDude.PlayerPosition.y + (float) MAP_TILE_SIZE/2)/MAP_TILE_SIZE);
        SnakeDude.PlayerTileY = (int)((MainMap.TileY) - (SnakeDude.PlayerPosition.y + (float)MAP_TILE_SIZE / 2) / MAP_TILE_SIZE);

        for (int y = (SnakeDude.PlayerTileY - PLAYER_TILE_VISIBILITY); y < (SnakeDude.PlayerTileY + PLAYER_TILE_VISIBILITY); y++)
            for (int x = (SnakeDude.PlayerTileX - PLAYER_TILE_VISIBILITY); x < (SnakeDude.PlayerTileX + PLAYER_TILE_VISIBILITY); x++)
                if((x >= 0) && (x < (int)MainMap.TileX) && (y >= 0) && (y < (int)MainMap.TileY))
                    MainMap.TileFog[y*MainMap.TileX + x] = 1;

        BeginTextureMode(FogOfWar);
            ClearBackground(BLANK);
            for (unsigned int y = 0; y < MainMap.TileY; y++)
                for (unsigned int x = 0; x < MainMap.TileX; x++)
                    if(MainMap.TileFog[y * MainMap.TileX + x] == 0) DrawRectangle(x, y, 1, 1, BLACK);
                    else if (MainMap.TileFog[y * MainMap.TileX + x] == 2) DrawRectangle(x, y, 1, 1, Fade(BLACK, 0.8f));
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Move that pixel", 10, 10, 20, DARKGRAY);

            for(unsigned int y = 0; y < MainMap.TileY; y++)
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
            }

            BeginMode2D(SnakeDude.PlayerCamera);
                DrawRectangleV((Vector2){40,50}, {50,50}, PURPLE);
                DrawRectangleV((SnakeDude.PlayerPosition), (Vector2){PLAYER_SIZE, PLAYER_SIZE}, RED);
                DrawTexturePro( FogOfWar.texture,
                                (Rectangle){ 0, 0, (float)FogOfWar.texture.width, (float)FogOfWar.texture.height },
                                (Rectangle){ 0, 0, (float)MainMap.TileX*MAP_TILE_SIZE, (float)MainMap.TileY*MAP_TILE_SIZE },
                                (Vector2) { 0, 0 }, 0.0f, WHITE);
            EndMode2D();

            DrawText(TextFormat("Current tile: [%i,%i]", SnakeDude.PlayerTileX, SnakeDude.PlayerTileY), 10, 10, 20, RAYWHITE);
            DrawText(TextFormat("Current position: [%f,%f]", SnakeDude.PlayerPosition.x, SnakeDude.PlayerPosition.y), 10, 30, 20, RAYWHITE);
        EndDrawing();
    }

    RL_FREE(MainMap.TileIds);
    RL_FREE(MainMap.TileFog);

    UnloadRenderTexture(FogOfWar);

    CloseWindow();
    return 0;
}
