#pragma once
#include "core.h"
#include "sprite.h"
#include <cstdint>

class Animation{
    public:
        uint8_t FramesCounter;
        uint8_t FramesSpeed;
        Animation();
        void PlayLoop(Sprite &TargetSprite); /* Loops indefinetly */
        void PlayOnce(Sprite &TargetSprite);
        void StopAt(Sprite &TargetSprite, int Frame); /* Stop at x Frame */
        //void ResetSpriteFC()
};
