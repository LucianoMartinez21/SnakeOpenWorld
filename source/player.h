#pragma once
#include "raylib.h"
#include "global.h"
#include <cstdint>
#include <math.h>
#include <vector>
#include "map.h"
#include "sprite.h"


enum DirectionFacing{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player{
    public:
        Player();
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
        void CheckCoalition(); //Coalition of the player and a wall or itself
        void ControllerHandler();
        void DrawPlayer();

        //Inventory

        //Public Vars
        Vector2 PlayerPosition;
        int PlayerTileX, PlayerTileY;
        Camera2D PlayerCamera;
        Vector2 PlayerSpeed;
        DirectionFacing DirFacing;
        bool IsDead = false;
        bool IsMoving = false;
        int TailLen = 0;
        Vector2 Tail[100];
        Sprite PlayerSprite;
        short Life = 100;
        short Score = 0;
    private:
        std::vector<uint8_t> Inventory;
        void OffsetTail(Vector2 &TailPosition);
        void OffsetTail(Vector2 &TailPosition, Vector2 NewestPosition);
};
 /*
  * Explication of Life
  * In a normal Enviroment, or an enviroment that the player have protection, the life will no drain
  * but in case of entering a harsh new enviroment, it will start draining.
  * E.G entering the shallow waters will not drain the life, but entering in deep waters without any
  * floaters will kill the player.
  */

//bool isVisible(Tile Object, Camera2D MainCam);
