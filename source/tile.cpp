#include "tile.h"
#include "player.h"
#include "sprite.h"
#include <raylib.h>

/*Tile::Tile()
{
    TileSprite = Sprite("", 0, 0, 0);
    }*/
Tile::Tile() : TileSprite("", 0.0f, 0.0f, 0)
{
    TileX = 0;
    TileY = 0;
    CanKill = false;
    IsHarsh = false;
    Drainer = 1;
}

void Tile::SetRangeEffect(Rectangle Area)
{
    RangeOfEffect = Area;
}
Rectangle Tile::GetRange()
{
    return RangeOfEffect;
}
void Tile::Killzone(Player Dude)
{
    if(IsHarsh)
    {
        if( Dude.PlayerPosition.x >= RangeOfEffect.x &&
            Dude.PlayerPosition.x <= RangeOfEffect.width &&
            Dude.PlayerPosition.y >= RangeOfEffect.y &&
            Dude.PlayerPosition.y <= RangeOfEffect.height);
        {
            Dude.Life -= Drainer;
            if(Dude.Life <= 0)
                Dude.IsDead = true;
        }
    }
}
