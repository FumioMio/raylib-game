#include "background/background.h"
#include "land/land.h"
#include "player/player.h"
#include "raylib.h"

int main(void) {

  int windowWidth = 960;
  int windowHeight = 640;

  InitWindow(windowWidth, windowHeight, "MyGame");

  Land farmable =
      InitLand("assets/mymap_farmable.csv", "assets/Tilesets/Tilled_Dirt.png");

  Player player;

  player = InitPlayer((Vector2){40.0f, 180.0f}, 50.0f,
                      "assets/Characters/BasicCharakterSpritesheet.png");

  Background background;

  background = InitBackground("assets/mymap.png");

  Vector2 camPos = (Vector2){0.0f, 0.0f};

  Camera2D camera = {0};
  camera.offset = (Vector2){0.0f, 0.0f};
  camera.rotation = 0.0f;
  camera.zoom = 2.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    float dt = GetFrameTime();

    camera.target = camPos;
    UpdatePlayer(&player, dt);

    if (IsKeyPressed(KEY_ENTER)) {
      int locX = (int){player.position.x / 16};
      int locY = (int){player.position.y / 16};

      if (farmable.data[locY][locX] == 1) {
        farmable.data[locY][locX] = 2;
      }
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    DrawBackground(background);

    DrawLand(&farmable);

    DrawPlayer(&player);

    EndMode2D();
    EndDrawing();
  }

  UnloadLand(farmable);
  UnloadPlayer(player);
  CloseWindow();

  return 0;
}
