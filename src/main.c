#include "player/player.h"
#include "raylib.h"

int main(void) {

  int windowWidth = 1280;
  int windowHeight = 720;

  InitWindow(windowWidth, windowHeight, "MyGame");

  Player player;

  player = InitPlayer((Vector2){10.0f, 10.0f}, 50.0f,
                      "assets/Characters/BasicCharakterSpritesheet.png");

  Vector2 camPos = (Vector2){0.0f, 0.0f};

  Camera2D camera = {0};
  camera.offset = (Vector2){0.0f, 0.0f};
  camera.rotation = 0.0f;
  camera.zoom = 8.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    float dt = GetFrameTime();

    camera.target = camPos;
    UpdatePlayer(&player, dt);
    if (player.position.y > 100.0f) {
      camPos.y = player.position.y - 100.0f;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    DrawPlayer(&player);
    EndMode2D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
