#include "map.h"
void UpdateVision(int TileX, int TileY, Map &Mapa)
{
    for (int y = (TileY - PLAYER_TILE_VISIBILITY); y < (TileY + PLAYER_TILE_VISIBILITY); y++)
        for (int x = (TileX - PLAYER_TILE_VISIBILITY); x < (TileX + PLAYER_TILE_VISIBILITY); x++)
            if((x >= 0) && (x < (int)Mapa.TileX) && (y >= 0) && (y < (int)Mapa.TileY))
                Mapa.TileFog[y*Mapa.TileX + x] = 1;
}

int YInvertedFix(int TileY, int HeightSize)
{
    return abs(TileY + 1 - HeightSize);
}
