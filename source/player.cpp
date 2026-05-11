#include "player.h"
#include <raylib.h>

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
    PlayerPosition = {PlayerPosition.x + PlayerSpeed.x, PlayerPosition.y + PlayerSpeed.y};
    FollowTarget();
}

/*Vector2 Player::GetPlayerPos()
{
    return PlayerPosition;
}*/
Vector2 Player::GetSpeed()
{
    return PlayerSpeed;
}


int Player::GetDirFace()
{
    return DirFacing;
}
