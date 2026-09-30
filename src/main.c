#include "background/background.h"
#include "player/player.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

int lahankosong[MAP_WIDTH][MAP_HEIGHT];
int fences[MAP_WIDTH][MAP_HEIGHT];

void LoadMapCsv(const char *filesource);

int main(void) {

  int windowWidth = 960;
  int windowHeight = 640;

  InitWindow(windowWidth, windowHeight, "MyGame");

  LoadMapCsv("assets/mymap_farmable.csv");

  Texture2D dirtText = LoadTexture("assets/Tilesets/Tilled_Dirt.png");
  Rectangle dirtRec = {48.0f, 48.0f, 16.0f, 16.0f};

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
      int locX = player.position.x / 16;
      int locY = player.position.y / 16;

      TraceLog(LOG_INFO, "apcb %d, %d, %d", lahankosong[locX][locY], locX,
               locY);
      lahankosong[locX][locY] = 0;
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    DrawBackground(background);

    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        if (lahankosong[x][y] > 0) {
          Vector2 destPos = {(float){x * 16}, (float){y * 16}};

          DrawTextureRec(dirtText, dirtRec, destPos, WHITE);
        }
      }
    }

    DrawPlayer(&player);

    EndMode2D();
    EndDrawing();
  }

  UnloadTexture(dirtText);
  UnloadPlayer(player);
  CloseWindow();

  return 0;
}

void LoadMapCsv(const char *filesource) {
  FILE *file = fopen(filesource, "r");

  if (file == NULL) {
    TraceLog(LOG_ERROR, "Gagal membuka file map csv");
    return;
  }

  char baris[1024];
  int c = 0;

  while (fgets(baris, sizeof(baris), file) && c < MAP_HEIGHT) {
    int r = 0;

    char *token = strtok(baris, ",\n\r");
    while (token != NULL && c < MAP_WIDTH) {
      lahankosong[r][c] = atoi(token);
      r++;
      token = strtok(NULL, ",\n\r");
    }
    c++;
  }

  fclose(file);
  TraceLog(LOG_INFO, "peta berhasil di load!!");
}
