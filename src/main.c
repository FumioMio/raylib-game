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
  Font pixelFont = LoadFont("assets/SproutLandUI/fonts/pixelFont.ttf");

  Cursor cursor = InitCursor(basicUitext);

  GameScreen currentScreen = MAIN_MENU;

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

    UpdateCursor(&cursor, screenCam);

    switch (currentScreen) {
    case MAIN_MENU: {
      int menuOption = UpdateMainMenu();
      if (menuOption == 1) {
        InitGameplay(&gameObj, &gameUi, &cursor, basicUitext, pixelFont);
        currentScreen = GAMEPLAY;
      } else if (menuOption == 2) {
        CloseWindow();
      }
    } break;
    case GAMEPLAY: {
      UpdateGameplay(&currentScreen, &gameObj, &gameUi, screenCam);
      if (currentScreen == MAIN_MENU) {
        UnloadGameplay(&gameObj, &gameUi);
      }
    } break;
    }

    BeginTextureMode(target);

    ClearBackground(RAYWHITE);

    switch (currentScreen) {
    case MAIN_MENU: {
      DrawMainMenu(pixelFont);
    } break;
    case GAMEPLAY: {
      DrawGameplay(&gameObj, &gameUi);
    } break;
    }

    DrawCursor(&cursor);

    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(target.texture, targetSourceRec, targetDestRec, targetOrigin,
                   0.0f, WHITE);

    EndDrawing();
  }

  UnloadTexture(basicUitext);
  UnloadFont(pixelFont);
  CloseWindow();

  return 0;
}
