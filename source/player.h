#pragma once
#include "raylib.h"
#include "global.h"
#include <math.h>
#include "map.h"


enum DirectionFacing{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player{
    public:
        //Public Functions
        // Camera related
        void SetCamTarget(short int x, short int y);
        void SetCamOffset(Vector2 Vec2);
        void InitCamOffset();
        void SetCamRotation(float Degree);
        void SetCamZoom(float Augmentation);
        void FollowTarget();
        void CheckCameraMapLimits();

        //Position and movement related
        void SetPlayerPos(short int x, short int y);
        void SetPlayerSpeed(float x, float y);
        void UpdateMovement();
        void CheckMapLimits(Map &Mapa);

        //Public Vars
        Vector2 PlayerPosition;
        int PlayerTileX, PlayerTileY;
        Camera2D PlayerCamera;
        Vector2 PlayerSpeed;
        DirectionFacing DirFacing;
};
