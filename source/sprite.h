#pragma once
#include "core.h"
#include <cstdint>
#include <raylib.h>
#include <string>

class Sprite
{
    public:
        Texture2D SpriteTexture;
        Vector2 SpritePosition, SpriteSpeed;
        //uint8_t LocalFrameCounter;
        uint8_t FrameCounter;
        uint8_t LengthFrame;
        Rectangle FrameRectangle;
        Sprite(const char *Filename,
            float PositionX, float PositionY, uint8_t TotalSpriteFrames);
        void DrawSpritePro(Vector2 Resize,
            Vector2 Origin, float Rotation);
        void AddInitialSpeed(Vector2 SpeedVector);

};
