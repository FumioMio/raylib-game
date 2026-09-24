#include "player/player.h"
#include "raylib.h"

int main(void) {

  int windowWidth = 960;
  int windowHeight = 640;

  InitWindow(windowWidth, windowHeight, "MyGame");

  Player player;

  player = InitPlayer((Vector2){40.0f, 180.0f}, 50.0f,
                      "assets/Characters/BasicCharakterSpritesheet.png");

  Texture mymap = LoadTexture("assets/mymap.png");
  Rectangle mapSource = {0.0f, 0.0f, mymap.width, mymap.height};
  Rectangle mapDst = {0.0f, 0.0f, 480.0f, 320.0f};

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
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);
    DrawTexturePro(mymap, mapSource, mapDst, (Vector2){0.0f, 0.0f}, 0.0f,
                   WHITE);

    DrawPlayer(&player);
    EndMode2D();
    EndDrawing();
  }

  UnloadPlayer(player);
  UnloadTexture(mymap);
  CloseWindow();

  return 0;
}
