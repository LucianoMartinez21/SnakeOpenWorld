#include "animation.h"

Animation::Animation()
{
    FramesCounter = 0;
    FramesSpeed = 24;
}

void Animation::PlayLoop(Sprite &TargetSprite)
{
    TargetSprite.FrameCounter = FramesCounter;
    if (TargetSprite.FrameCounter >= (60/FramesSpeed))
    {
        TargetSprite.FrameCounter++;
        if (TargetSprite.FrameCounter > TargetSprite.LengthFrame - 1)
            TargetSprite.FrameCounter = 0;
        TargetSprite.FrameRectangle.x = (float)TargetSprite.FrameCounter * TargetSprite.SpriteTexture.width/TargetSprite.LengthFrame;
    }
}
void Animation::PlayOnce(Sprite &TargetSprite)
{
    TargetSprite.FrameCounter = FramesCounter;
    if (TargetSprite.FrameCounter >= (60/FramesSpeed))
    {
        if(TargetSprite.FrameCounter < TargetSprite.LengthFrame - 1)
        {
            TargetSprite.FrameCounter++;
            TargetSprite.FrameRectangle.x = (float)TargetSprite.FrameCounter * (float)TargetSprite.SpriteTexture.width/TargetSprite.LengthFrame;
        }
    }
}
void Animation::StopAt(Sprite &TargetSprite, int Frame)
{
    TargetSprite.FrameCounter = FramesCounter;
    if (TargetSprite.FrameCounter >= (60/FramesSpeed))
    {
        if (TargetSprite.FrameCounter < Frame)
        {
            TargetSprite.FrameCounter++;
            TargetSprite.FrameRectangle.x = (float)TargetSprite.FrameCounter * TargetSprite.SpriteTexture.width/TargetSprite.LengthFrame;
        }
    }
}
