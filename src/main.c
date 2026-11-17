#include "gameScreen/gameScreen.h"
#include "gameScreen/gameplay.h"
#include "ui/ui.h"
#include <raylib.h>
#include <raymath.h>

int main(void) {

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

  Texture2D basicUitext =
      LoadTexture("assets/SproutLandUI/spritesheets/basicpack.png");
  Texture2D faceText =
      LoadTexture("assets/SproutLandUI/spritesheets/Dialouge/Emotes/emote.png");
  Font pixelFont = LoadFont("assets/SproutLandUI/fonts/pixelFont.ttf");

  Cursor cursor = InitCursor(basicUitext);

  GameObj gameObj;
  GameUi gameUi;

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
