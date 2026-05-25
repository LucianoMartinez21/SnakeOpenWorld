#include "init.h"
#include "core.h"
#include "global.h"
#include "tile.h"
#include <cstring>
#include <raylib.h>
#include <vector>

Player SnakeDude;
Map MainMap;
RenderTexture2D FogOfWar;
std::vector <Tile> World;
std::vector <AppleTile> Fruits;
std::vector <Tile> Obstacles;
ObjectTile KeyObjects[3];
GAME_STATE GameFlow;
Tile Wall;

void InitCore()
{
    SnakeDude.SetPlayerPos(SCREENW/2, SCREENH/2);
    SnakeDude.PlayerTileX = (SCREENW/2)/MAP_TILE_SIZE;
    SnakeDude.PlayerTileY = (SCREENH/2)/MAP_TILE_SIZE;
    SnakeDude.SetCamTarget((float) SnakeDude.PlayerPosition.x + (float)PLAYER_SIZE / 2,(float) SnakeDude.PlayerPosition.y + (float)PLAYER_SIZE / 2);
    SnakeDude.InitCamOffset();
    SnakeDude.SetCamRotation(0);
    SnakeDude.SetCamZoom(2.0f);
    SnakeDude.PlayerSprite = Sprite("resource/SnakeTilesAlt.png", (float)SCREENW/2, (float)SCREENH/2, 10);
    SnakeDude.IsDead = false;
    SnakeDude.Score = 0;
    SnakeDude.Life = 100;
    SnakeDude.TailLen = 0;
    memset(SnakeDude.Tail, 0, sizeof SnakeDude.Tail);
    SnakeDude.CleanInventory();

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
    World.clear();
    Obstacles.clear();
    for(int i = 0; i <= 4; i++)
    {
        World.push_back(Tile());
        World[i].IsHarsh = false;
        World[i].TileSprite = Sprite("resource/WorldTile.png", (float)0, (float) 0, 10);
        World[i].SetRangeEffect(InitRanges(i));
        World[i].TileSprite.ChangeFrame(i);
        Obstacles.push_back(Tile());
        Obstacles[i].IsHarsh = true;
        Obstacles[i].TileSprite = Sprite("resource/ObstaclesTiles.png", 0.0f, 0.0f, 10);
        Obstacles[i].TileSprite.ChangeFrame(i);
        if(i < 3)
        {
            KeyObjects[i].Object = i + 1;
            KeyObjects[i].IsHarsh = false;
            KeyObjects[i].TileSprite = Sprite("resource/KeyObjects.png", 0.0f, 0.0f, 10);
            KeyObjects[i].TileSprite.ChangeFrame(i);
            KeyObjects[i].hasBeingUsed = false;
            switch (i) {
                case 0:
                    KeyObjects[i].TileX = 40;
                    KeyObjects[i].TileY = 7;
                    break;
                case 1:
                    KeyObjects[i].TileX = 27;
                    KeyObjects[i].TileY = 37;
                    break;
                case 2:
                    KeyObjects[i].TileX = 87;
                    KeyObjects[i].TileY = 23;
                    break;

            }
        }
    }

    Wall.IsHarsh = true;
    Wall.TileSprite = Sprite("resource/WorldTile.png", 0.0f, 0.0f, 10);
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

int SHeightLoc;
int AmplitudLoc;
int FrequencyLoc;
int SpeedLoc;
int AmplitudVertLoc;
int FrequencyVertLoc;
int SpeedVertLoc;
int ScrollDirLoc;
int ScrollSpeedLoc;
int EnablePaletteLoc;
int PaletteLoc;
int PaletteSpeedLoc;
Shader ShaderBackground;
Texture2D MainMenu;
int LocTime;
std::pmr::vector<int> KeyBuffer;
int KeyCounter = 0;

void InitShader()
{
    MainMenu = LoadTexture("resource/MainMenu.png");
    ShaderBackground = LoadShader(0, "shaders/eb.fs");
    LocTime =           GetShaderLocation(ShaderBackground, "TIME");
    SHeightLoc =        GetShaderLocation(ShaderBackground, "screen_height");
    AmplitudLoc =       GetShaderLocation(ShaderBackground, "amplitude");
    FrequencyLoc =      GetShaderLocation(ShaderBackground, "frequency");
    SpeedLoc =          GetShaderLocation(ShaderBackground, "speed");
    AmplitudVertLoc =   GetShaderLocation(ShaderBackground, "amplitude_vertical");
    FrequencyVertLoc =  GetShaderLocation(ShaderBackground, "frequency_vertical");
    SpeedVertLoc =      GetShaderLocation(ShaderBackground, "speed_vertical");
    ScrollDirLoc =      GetShaderLocation(ShaderBackground, "scroll_direction");
    ScrollSpeedLoc =    GetShaderLocation(ShaderBackground, "scrolling_speed");
    EnablePaletteLoc =  GetShaderLocation(ShaderBackground, "enable_palette_cycling");
    PaletteLoc =        GetShaderLocation(ShaderBackground, "palette");
    PaletteSpeedLoc =   GetShaderLocation(ShaderBackground, "palette_speed");

    float Screen                = SCREENH;
    float Amplitud              = 0.08f;
    float Frequency             = 10.0f;
    float Speed                 = 2.0f;
    float AmplitudVertical      = 0.0f;
    float FrequencyVertical     = 0.0f;
    float SpeedVertical         = 0.0f;
    float ScrollDirection[2]    = {0.0f,0.0f};
    float ScrollSpeed           = 0.08f;
    int EnablePalette           = 0; // 1 means true, 0 means false
    float PaletteSpeed          = 0.1f;

    SetShaderValue(ShaderBackground, SHeightLoc, &Screen, SHADER_UNIFORM_FLOAT);
    SetShaderValue(ShaderBackground, AmplitudLoc, &Amplitud, SHADER_UNIFORM_FLOAT);
    SetShaderValue(ShaderBackground, FrequencyLoc, &Frequency, SHADER_UNIFORM_FLOAT);
    SetShaderValue(ShaderBackground, SpeedLoc, &Speed, SHADER_UNIFORM_FLOAT);
    SetShaderValue(ShaderBackground, AmplitudVertLoc, &AmplitudVertical, SHADER_UNIFORM_FLOAT);
    SetShaderValue(ShaderBackground, FrequencyVertLoc, &FrequencyVertical, SHADER_UNIFORM_FLOAT);
    SetShaderValue(ShaderBackground, SpeedVertLoc, &SpeedVertical, SHADER_UNIFORM_FLOAT);
    SetShaderValue(ShaderBackground, ScrollDirLoc, &ScrollDirection, SHADER_UNIFORM_VEC2);
    SetShaderValue(ShaderBackground, ScrollSpeedLoc, &ScrollSpeed, SHADER_UNIFORM_FLOAT);
    SetShaderValue(ShaderBackground, EnablePaletteLoc, &EnablePalette, SHADER_UNIFORM_INT);
    SetShaderValue(ShaderBackground, PaletteSpeedLoc, &PaletteSpeed, SHADER_UNIFORM_FLOAT);

    SetShaderValueTexture(ShaderBackground, PaletteLoc, MainMenu);
}
bool RevealSecret[3] = {false};
void Secrets()
{
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
        RevealSecret[0] = false;
        RevealSecret[1] = false;
        RevealSecret[2] = false;
        KeyBuffer.clear();
        return;
    }
    KeyCounter = GetKeyPressed();
    if(KeyCounter != KEY_NULL)
    {
        if(GetKeyName(KeyCounter) == GetKeyName(KEY_M) ||
            GetKeyName(KeyCounter) == GetKeyName(KEY_U)||
            GetKeyName(KeyCounter) == GetKeyName(KEY_S)||
            GetKeyName(KeyCounter) == GetKeyName(KEY_I)||
            GetKeyName(KeyCounter) == GetKeyName(KEY_C)||
            GetKeyName(KeyCounter) == GetKeyName(KEY_Z)||
            GetKeyName(KeyCounter) == GetKeyName(KEY_A)||
            GetKeyName(KeyCounter) == GetKeyName(KEY_R)
            )
            KeyBuffer.push_back(KeyCounter);
        if(
            KeyBuffer[0] == KEY_M &&
            KeyBuffer[1] == KEY_U &&
            KeyBuffer[2] == KEY_S &&
            KeyBuffer[3] == KEY_I &&
            KeyBuffer[4] == KEY_C
            )
            {
                RevealSecret[0] = true;
                RevealSecret[1] = false;
                RevealSecret[2] = false;
                KeyBuffer.clear();
            }
        if(
            KeyBuffer[0] == KEY_S &&
            KeyBuffer[1] == KEY_I &&
            KeyBuffer[2] == KEY_C &&
            KeyBuffer[3] == KEY_M &&
            KeyBuffer[4] == KEY_U
            )
            {
                RevealSecret[0] = false;
                RevealSecret[1] = true;
                RevealSecret[2] = false;
                KeyBuffer.clear();
            }
        if(
            KeyBuffer[0] == KEY_Z &&
            KeyBuffer[1] == KEY_A &&
            KeyBuffer[2] == KEY_R &&
            KeyBuffer[3] == KEY_A
            )
            {
                RevealSecret[0] = false;
                RevealSecret[1] = false;
                RevealSecret[2] = true;
                KeyBuffer.clear();
            }
    }
    if(RevealSecret[0])
    {
        DrawText(
        "Music heard on the Making:\nBlack Soul Sickness by KarciusMirage by Camel\nKind of Blue by Miles Davis\nIntrospection by Luiz Bonfá\nWet Land by Hiroshi Yoshimura\nConcierto (Album) by Jim Hall\nSi on avait besoin d'une cinquième saison by Harmonium\nDepois do Fim by Bacamarte\nThe Inner Mounting Flame by The Mahavishnu Orchestra\nBitches Brew By Miles Davis\nSvitanie Blue Effect By (Modrý Efekt)\nSpectrum By Billy Cobham\nRebel by EsDeeKid\nClône by Tiemko\nThe Soothsayer by Wayne Shorter\nTemplars - In Sacred Blood by John Zorn\nFrom Silence to Somewhere by Wobbler\nWhen Dream And Day Unite by Dream Theater\nAwake by Dream Theater\nTanquemante by Inundaremos\n"
        , SCREENW/2 - 30, 0, 20, RAYWHITE);
    }
    if(RevealSecret[1])
    {
        DrawText(
        "Music heard on the Making:\nFilin by Melissa Aldana\nDistancia by Congelador\nEspero podamos ver un ovni juntxs by Rubio\nAmigos, vecinos, parientes by el mejor de los camilos\nCírculo de fuego by Légamo\nTropiezos y certezas, ceci\nPrimer Vuelo by ceci\nplease be nice by Camping in Alaska\nBATHE by Camping in Alaska\nOperation Doomsday by MF DOOM\nTake Me To Your Leader by King Geedorah aka MF DOOM\nVaudeville Villain by Viktor Vaughn aka MF DOOM\nVenomous Villain (VV:2) by Viktor Vaughn aka MF DOOM\nMM..FOOD by MF DOOM\nBorn Like This by MF DOOM"
        , SCREENW/2 - 30, 0, 20, RAYWHITE);
    }
    if(RevealSecret[2])
    {
        DrawText(
        "Grande Zara-Tustra por volver con un comic"
        , SCREENW/2 - 150, 0, 20, RAYWHITE);
    }
}
