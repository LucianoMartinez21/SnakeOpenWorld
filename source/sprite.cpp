#include "sprite.h"
#include <raylib.h>

Sprite::Sprite(const char *Filename, float PositionX, float PositionY, uint8_t TotalSpriteFrames)
{
    SpriteTexture = LoadTexture(Filename);
    SpritePosition = (Vector2){ PositionX, PositionY };
    FrameCounter = 0;
    LengthFrame = TotalSpriteFrames;
    FrameRectangle = (Rectangle)
        {
            0.0f,
            0.0f,
            (float)SpriteTexture.width/LengthFrame,
            (float)SpriteTexture.height
        };
}

void Sprite::DrawSpritePro(Vector2 Resize, Vector2 Origin, float Rotation)
{
    DrawTexturePro(SpriteTexture,
        FrameRectangle,
        (Rectangle){ SpritePosition.x, SpritePosition.y, Resize.x, Resize.y },
        Origin,
        Rotation,
        WHITE);
}
void Sprite::DrawSpritePro(Vector2 Location, Vector2 Resize, Vector2 Origin, float Rotation)
{
    DrawTexturePro(SpriteTexture,
        FrameRectangle,
        (Rectangle){ Location.x, Location.y, Resize.x, Resize.y },
        Origin,
        Rotation,
        WHITE);
}
void Sprite::AddInitialSpeed(Vector2 SpeedVector)
{
    SpriteSpeed = SpeedVector;
}

void Sprite::ChangeFrame(int Frame)
{
    FrameCounter = Frame;
    FrameRectangle.x = (float) FrameCounter * SpriteTexture.width / LengthFrame;
}
