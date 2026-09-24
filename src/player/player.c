#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>

Player InitPlayer(Vector2 pos, float speed, const char *texturePath) {
  Player player;
  player.position = pos;
  player.speed = speed;
  player.texture = LoadTexture(texturePath);
  player.frameRec =
      (Rectangle){0.0f, 0.0f, (float){player.texture.width / 4.0f},
                  (float){player.texture.height / 4.0f}};
  player.currentFrameX = 0;
  player.currentFrameY = 0;
  player.frameCounter = 0;
  player.frameSpeed = 4.0f;
  player.size = (Vector2){48.0f, 48.0f};
  player.flipX = false;
  return player;
}

void AnimatePlayer(Player *p, float dt, Vector2 dir) {
  p->frameCounter += dt;
  int animX = 0;

  if (dir.y < 0.0f) {
    animX = 2;
    p->currentFrameY = 1;
    p->flipX = false;
  } else if (dir.y > 0.0f) {
    animX = 2;
    p->currentFrameY = 0;
    p->flipX = false;
  } else if (dir.x != 0.0f) {
    if (dir.x > 0) {
      p->flipX = true;
    } else {
      p->flipX = false;
    }

    animX = 2;
    p->currentFrameY = 2;
  }

  if (p->frameCounter >= (1.0f / p->frameSpeed)) {
    p->frameCounter = 0.0f;
    if (p->currentFrameX > (animX + 1) || p->currentFrameX < animX) {
      p->currentFrameX = animX;
    }
    p->currentFrameX++;
    if (p->currentFrameX > (animX + 1)) {
      p->currentFrameX = animX;
    }

    p->frameRec.x = p->currentFrameX * (p->texture.width / 4.0f);
    p->frameRec.y = p->currentFrameY * (p->texture.height / 4.0f);
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

  if (p->flipX) {
    if (p->frameRec.width > 0) {
      p->frameRec.width *= -1;
    }
  } else {
    if (p->frameRec.width < 0) {
      p->frameRec.width *= -1;
    }
  }

  if (Vector2Length(dir) > 0.0f) {
    dir = Vector2Normalize(dir);
  }
  Vector2 vel = Vector2Scale(dir, p->speed * dt);
  p->position = Vector2Add(p->position, vel);
}

void DrawPlayer(Player *p) {

  Rectangle destRec = {p->position.x, p->position.y, p->size.x, p->size.y};

  Vector2 origin = {p->size.x / 2.0f, p->size.y / 2.0f};

  DrawTexturePro(p->texture, p->frameRec, destRec, origin, 0, WHITE);
}

void UnloadPlayer(Player p) { UnloadTexture(p.texture); }
