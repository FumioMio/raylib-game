#include "background/background.h"
#include "land/land.h"
#include "player/player.h"
#include "raylib.h"
#include "ui/ui.h"
#include "util/loadCols.h"
#include <raymath.h>

int main(void) {

  Cols obstacle = {0};

  LoadCols("assets/mymap.json", &obstacle);

  int virtualWidth = 480;
  int virtualHeight = 320;
  int windowScale = 2;

  InitWindow(virtualWidth * windowScale, virtualHeight * windowScale, "MyGame");

  Image icon = LoadImage("icon.png");
  SetWindowIcon(icon);
  SetExitKey(KEY_NULL);

  RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);
  SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
  Rectangle targetSourceRec =
      (Rectangle){0.0f, 0.0f, (float)(target.texture.width),
                  (float)(-target.texture.height)};
  Rectangle targetDestRec =
      (Rectangle){0.0f, 0.0f, (float)(virtualWidth * windowScale),
                  (float)(virtualHeight * windowScale)};
  Vector2 targetOrigin = (Vector2){0.0f, 0.0f};

  HideCursor();

  Land farmable = InitLand("assets/mymap_farmable.csv",
                           "assets/Tilesets/Tilled_Dirt_Wide_v2.png",
                           "assets/Objects/Basic_Plants.png");

  Player player;

  player = InitPlayer((Vector2){140.0f, 180.0f}, 50.0f,
                      "assets/Characters/BasicCharakterSpritesheet.png",
                      "assets/Characters/CharAction.png");

  Background background;

  background = InitBackground("assets/mymap.png");

  Vector2 camPos = (Vector2){0.0f, 0.0f};

  Texture2D basicUitext =
      LoadTexture("assets/SproutLandUI/spritesheets/basicpack.png");
  Texture2D faceText =
      LoadTexture("assets/SproutLandUI/spritesheets/Dialouge/Emotes/emote.png");
  Font pixelFont = LoadFont("assets/SproutLandUI/fonts/pixelFont.ttf");

  Hud myHud = InitHud(basicUitext, faceText, pixelFont);

  Cursor cursor = InitCursor(basicUitext);
  SettingPanel setpanel = InitSetPanel(basicUitext, pixelFont);

  Camera2D camera = {0};
  camera.offset = (Vector2){0.0f, 0.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    Camera2D screenCam = {0};
    screenCam.zoom = (float)(windowScale);
    screenCam.offset = (Vector2){
        (float)((GetScreenWidth() - (float)(virtualWidth * windowScale)) *
                0.5f),
        (float)((GetScreenHeight() - (float)(virtualHeight * windowScale)) *
                0.5f)};

    float dt = GetFrameTime();

    camera.target = camPos;
    UpdatePlayer(&player, &farmable, &obstacle, dt);

    UpdateSetPanel(&setpanel, cursor);

    UpdateCursor(&cursor, screenCam);

    BeginTextureMode(target);

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    DrawBackground(background);

    DrawLand(&farmable);

    DrawPlayer(&player);

    EndMode2D();

    DrawHud(&myHud);

    DrawSetPanel(&setpanel);

    DrawCursor(&cursor);

    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(target.texture, targetSourceRec, targetDestRec, targetOrigin,
                   0.0f, WHITE);

    EndDrawing();
  }

  UnloadLand(farmable);
  UnloadPlayer(player);
  UnloadTexture(basicUitext);
  UnloadTexture(faceText);
  UnloadFont(pixelFont);
  CloseWindow();

  return 0;
}
