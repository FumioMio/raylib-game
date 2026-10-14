#include "background/background.h"
#include "land/land.h"
#include "player/player.h"
#include "raylib.h"
#include "ui/cursor.h"
#include "util/loadCols.h"
#include <raymath.h>

int main(void) {

  Cols obstacle = {0};

  LoadCols("assets/mymap.json", &obstacle);

  int windowWidth = 960;
  int windowHeight = 640;

  InitWindow(windowWidth, windowHeight, "MyGame");

  Image icon = LoadImage("icon.png");
  SetWindowIcon(icon);

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
  Cursor cursor = InitCursor(basicUitext);

  Camera2D camera = {0};
  camera.offset = (Vector2){0.0f, 0.0f};
  camera.rotation = 0.0f;
  camera.zoom = 2.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    float dt = GetFrameTime();

    camera.target = camPos;
    UpdatePlayer(&player, &farmable, &obstacle, dt);
    UpdateCursor(&cursor);

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    DrawBackground(background);

    DrawLand(&farmable);

    DrawPlayer(&player);

    EndMode2D();

    DrawCursor(&cursor);

    EndDrawing();
  }

  UnloadLand(farmable);
  UnloadPlayer(player);
  UnloadTexture(basicUitext);
  CloseWindow();

  return 0;
}
