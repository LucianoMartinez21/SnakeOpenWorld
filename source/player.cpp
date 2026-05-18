#include "player.h"
#include <raylib.h>

Player::Player() //: PlayerSprite("", 0, 0, 0)
{
}

void Player::SetCamTarget(short int x, short int y)
{
    PlayerCamera.target = (Vector2){ (float)x, (float)y };
}
void Player::InitCamOffset()
{
    //PlayerCamera.offset = (Vector2){ SCREENW/2.0f, SCREENH/2.0f };//Vector2{ player.x + player.width / 2, player.y + player.height / 2 };
    PlayerCamera.offset = (Vector2){ PlayerPosition.x - PLAYER_SIZE / 2, PlayerPosition.y - PLAYER_SIZE / 2 };
}
void Player::SetCamOffset(Vector2 Vec2)
{
    PlayerCamera.offset = Vec2;
}
void Player::SetCamRotation(float Degree)
{
    PlayerCamera.rotation = Degree;
}
void Player::SetCamZoom(float Augmentation)
{
    PlayerCamera.zoom = Augmentation;
}
void Player::FollowTarget()
{
    SetCamTarget(PlayerPosition.x + 20, PlayerPosition.y + 20);
}
void Player::SetPlayerPos(short int x, short int y)
{
    PlayerPosition = (Vector2){ (float)x, (float)y };
}

void Player::SetPlayerSpeed(float x, float y)
{
    PlayerSpeed = (Vector2){ x, y };
}

void Player::UpdateMovement()
{
    Vector2 PreviousPosition = Tail[0];
    Vector2 PreviousPositionAux;
    Tail[0] = PlayerPosition;
    PlayerPosition = {PlayerPosition.x + PlayerSpeed.x, PlayerPosition.y + PlayerSpeed.y};
    for(int index = 1; index < TailLen; index++)
    {
        PreviousPositionAux = Tail[index];
        Tail[index] = PreviousPosition;
        PreviousPosition = PreviousPositionAux;
    }
}

void Player::CheckMapLimits(Map &Mapa)
{
    if (PlayerPosition.x < 0) PlayerPosition.x = 0;
    else if ((PlayerPosition.x + PLAYER_SIZE) > Mapa.TileX*MAP_TILE_SIZE) PlayerPosition.x = (float)Mapa.TileX*MAP_TILE_SIZE - PLAYER_SIZE;
    if (PlayerPosition.y < 0) PlayerPosition.y = 0;
    else if ((PlayerPosition.y + PLAYER_SIZE) > Mapa.TileY*MAP_TILE_SIZE) PlayerPosition.y = (float)Mapa.TileY*MAP_TILE_SIZE - PLAYER_SIZE;
}

void Player::CheckCameraMapLimits()
{
    if (PlayerCamera.target.x < 0 + ((SCREENW/PlayerCamera.zoom)/2))    PlayerCamera.target.x = (float)(0 + (SCREENW/PlayerCamera.zoom) / 2);
    if (PlayerCamera.target.x > 3040 - ((SCREENW/PlayerCamera.zoom)/2)) PlayerCamera.target.x = (float)(3040 - (SCREENW/PlayerCamera.zoom) / 2);
    if (PlayerCamera.target.y < 0 + ((SCREENH/PlayerCamera.zoom)/2))    PlayerCamera.target.y = (float)(0 + (SCREENH/PlayerCamera.zoom) / 2);
    if (PlayerCamera.target.y > 2016 - ((SCREENH/PlayerCamera.zoom)/2)) PlayerCamera.target.y = (float)(2016 - (SCREENH/PlayerCamera.zoom) / 2);
}

void Player::Coalition() //Checks the Coalition of the player and itself
{
    for(int i = 0; i < TailLen; i++)
    {
        if(Tail[i].x == PlayerPosition.x and Tail[i].y == PlayerPosition.y)
            IsDead = true;
    }
}
//void InadequateEnviroment(); //Harsh conditions of the enviroment will start slowly killing the player
//void PositiveCoalition(AppleTile Fruit);

void Player::ControllerHandler()
{
    if (IsKeyDown(KEY_RIGHT))   {SetPlayerSpeed(4.5f, 0.0f);}
    if (IsKeyDown(KEY_LEFT))    {SetPlayerSpeed(-4.5f, 0.0f);}
    if (IsKeyDown(KEY_UP))      {SetPlayerSpeed(0.0f, -4.5f);}
    if (IsKeyDown(KEY_DOWN))    {SetPlayerSpeed(0.0f, 4.5f);}
}
