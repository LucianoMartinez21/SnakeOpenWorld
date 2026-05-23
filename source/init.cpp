#include "init.h"
#include "core.h"

Player SnakeDude;
Map MainMap;
RenderTexture2D FogOfWar;
std::vector <Tile> World;
std::vector <AppleTile> Fruits;
std::vector <Tile> Obstacles;
GAME_STATE GameFlow;
Tile Wall;

void InitCore()
{
    SnakeDude.SetPlayerPos(SCREENW/2, SCREENH/2);
    SnakeDude.PlayerTileX = (SCREENW/2)/MAP_TILE_SIZE;
    SnakeDude.PlayerTileY = (SCREENH/2)/MAP_TILE_SIZE;
    SnakeDude.SetCamTarget((float) SnakeDude.PlayerPosition.x + PLAYER_SIZE / 2,(float) SnakeDude.PlayerPosition.y + PLAYER_SIZE / 2);
    SnakeDude.InitCamOffset();
    SnakeDude.SetCamRotation(0);
    SnakeDude.SetCamZoom(2.0f);
    SnakeDude.PlayerSprite = Sprite("resource/SnakeTilesAlt.png", SCREENW/2, SCREENH/2, 10);
    //Fruits[i].TileSprite = Sprite("resource/FruitTiles.png", Fruits[i].TileX * MAP_TILE_SIZE, Fruits[i].TileY * MAP_TILE_SIZE, 10);

    //Declare Map Tiles
    MainMap.TileX = 96;
    MainMap.TileY = 64;
    MainMap.TileIds = (unsigned char *)RL_CALLOC(MainMap.TileX*MainMap.TileY, sizeof(unsigned char));
    MainMap.TileFog = (unsigned char *)RL_CALLOC(MainMap.TileX*MainMap.TileY, sizeof(unsigned char));

    for (unsigned int i = 0; i < MainMap.TileY*MainMap.TileX; i++) MainMap.TileIds[i] = GetRandomValue(0, 1);

    MetaTiles MetaMap;
    MetaMap.MTileX = MainMap.TileX/8;
    MetaMap.MTileY = MainMap.TileY/8;

    //Declare Fog of War Texture
    FogOfWar = LoadRenderTexture(MainMap.TileX, MainMap.TileY);
    SetTextureFilter(FogOfWar.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(FogOfWar.texture, TEXTURE_WRAP_CLAMP);

    //Declare a World Tile

    for(int i = 0; i <= 4; i++)
    {
        World.push_back(Tile());
        World[i].IsHarsh = false;
        World[i].TileSprite = Sprite("resource/WorldTile.png", (float)0, (float) 0, 10);
        World[i].SetRangeEffect(InitRanges(i));
        World[i].TileSprite.ChangeFrame(i);
        Obstacles.push_back(Tile());
        Obstacles[i].IsHarsh = true;
        Obstacles[i].TileSprite = Sprite("resource/ObstaclesTiles.png", 0, 0, 10);
        Obstacles[i].TileSprite.ChangeFrame(i);
    }

    Wall.IsHarsh = true;
    Wall.TileSprite = Sprite("resource/WorldTile.png", (float)0, (float) 0, 10);
    //Wall.SetRangeEffect(InitRanges(5));
    Wall.TileSprite.ChangeFrame(5);

    LoadAppleTilesLocations(Fruits, FruitLocations);

    World[2].SetRangeEffect(
        {
            (Vector2){0 * MAP_TILE_SIZE, 0 * MAP_TILE_SIZE},
            (Vector2){32 * MAP_TILE_SIZE, 0 * MAP_TILE_SIZE},
            (Vector2){32 * MAP_TILE_SIZE, 8 * MAP_TILE_SIZE},
            (Vector2){16 * MAP_TILE_SIZE, 8 * MAP_TILE_SIZE},
            (Vector2){16 * MAP_TILE_SIZE, 16 * MAP_TILE_SIZE},
            (Vector2){8 * MAP_TILE_SIZE, 16 * MAP_TILE_SIZE},
            (Vector2){8 * MAP_TILE_SIZE, 56 * MAP_TILE_SIZE},
            (Vector2){48 * MAP_TILE_SIZE, 56 * MAP_TILE_SIZE},
            (Vector2){48 * MAP_TILE_SIZE, 48 * MAP_TILE_SIZE},
            (Vector2){80 * MAP_TILE_SIZE, 48 * MAP_TILE_SIZE},
            (Vector2){80 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE},
            (Vector2){96 * MAP_TILE_SIZE, 32 * MAP_TILE_SIZE},
            (Vector2){96 * MAP_TILE_SIZE, 64 * MAP_TILE_SIZE},
            (Vector2){0 * MAP_TILE_SIZE, 64 * MAP_TILE_SIZE}
        }
    );
    World[0].IsHarsh = true;
    World[2].IsHarsh = true;
    World[3].IsHarsh = true;
}
