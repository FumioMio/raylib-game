#include "player.h"
#include "raylib.h"
#include "raymath.h"

Player InitPlayer(Vector2 pos, float speed, const char *texturePath) {
  Player player;
  player.position = pos;
  player.speed = speed;
  player.texture = LoadTexture(texturePath);
  player.frameRec =
      (Rectangle){0.0f, 0.0f, (float){player.texture.width / 4.0f},
                  (float){player.texture.height / 4.0f}};
  player.currentFrame = 0;
  player.frameCounter = 0;
  player.frameSpeed = 0.4f;
  player.size = (Vector2){32.0f, 32.0f};
  return player;
}

void AnimatePlayer(Player *p, float dt, Vector2 dir) {
  p->frameCounter += dt;
  if (p->frameCounter >= (60.0f / p->frameSpeed)) {
    p->frameCounter = 0.0f;
    p->currentFrame++;
    if (p->currentFrame > 1) {
      p->currentFrame = 0;
    }

    p->frameRec.x = p->currentFrame * (p->texture.width / 4.0f);
  }
}

void UpdatePlayer(Player *p, float dt) {
  Vector2 dir = (Vector2){0.0f, 0.0f};

  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    dir.x = 1;
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    dir.y = 1;
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    dir.x = -1;
  }
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    dir.y = -1;
  }

  AnimatePlayer(p, dt, dir);
  if (Vector2Length(dir) > 0.0f) {
    dir = Vector2Normalize(dir);
  }
  Vector2 vel = Vector2Scale(dir, p->speed * dt);
  p->position = Vector2Add(p->position, vel);
}

void DrawPlayer(Player p) {
  Rectangle destRec = {p.position.x, p.position.y, p.size.x, p.size.y};

  Vector2 origin = {p.size.x / 2.0f, p.size.y / 2.0f};

  DrawTexturePro(p.texture, p.frameRec, destRec, origin, 0, WHITE);
}
