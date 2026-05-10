#include "raylib.h"
#include "global.h"
#include <math.h>

class Player{
    private:
        Camera2D PlayerCamera;
        Vector2 PlayerSpeed;
    public:
        void SetCamTarget(short int x, short int y);
        void SetCamOffset();
        void SetCamRotation(float Degree);
        void SetCamZoom(float Augmentation);
        void FollowTarget();
        void SetPlayerPos(short int x, short int y);
        void SetPlayerSpeed(float x, float y);
        void UpdateMovement();
        //Vector2 GetPlayerPos();
        Camera2D GetCam();
        //Public Vars
        Vector2 PlayerPosition;
        int PlayerTileX, PlayerTileY;
};
