#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>

Player InitPlayer(Vector2 pos, float speed, const char *texturePath) {
  Player player;
  player.position = pos;
  player.speed = speed;
  player.direction = (Vector2){0.0f, 1.0f};
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
  player.curAction = NONE;
  player.timer = 0.0f;
  return player;
}

void AnimatePlayer(Player *p, float dt, Vector2 moveDir) {
  p->frameCounter += dt;
  int animX = 0;

  if (moveDir.y < 0.0f) {
    animX = 2;
    p->currentFrameY = 1;
    p->flipX = false;
  } else if (moveDir.y > 0.0f) {
    animX = 2;
    p->currentFrameY = 0;
    p->flipX = false;
  } else if (moveDir.x != 0.0f) {
    if (moveDir.x > 0) {
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

void UpdatePlayer(Player *p, Land *l, float dt) {

  // Action
  if (p->curAction == NONE && IsKeyPressed(KEY_ENTER)) {
    p->curAction = SOILING;
    int targetX = (int){(p->position.x / 16) + p->direction.x};
    int targetY = (int){(p->position.y / 16) + p->direction.y};

    if (l->data[targetY][targetX].id == 1) {
      l->data[targetY][targetX].id = 2;
    }
  }
  if (p->curAction == NONE && IsKeyPressed(KEY_P)) {
    p->curAction = WATERING;
    int targetX = (int){(p->position.x / 16) + p->direction.x};
    int targetY = (int){(p->position.y / 16) + p->direction.y};

    if (l->data[targetY][targetX].id > 1) {
      l->data[targetY][targetX].isWatered = true;
    }
  }
  if (p->curAction == NONE && IsKeyPressed(KEY_L)) {
    p->curAction = PLANTING;
    int targetX = (int){(p->position.x / 16) + p->direction.x};
    int targetY = (int){(p->position.y / 16) + p->direction.y};

    if (l->data[targetY][targetX].id > 1 &&
        l->data[targetY][targetX].cropType == CROPLESS) {
      l->data[targetY][targetX].cropType = WHEAT;
    }
  }
  if (p->curAction == NONE && IsKeyPressed(KEY_K)) {
    p->curAction = PLANTING;
    int targetX = (int){(p->position.x / 16) + p->direction.x};
    int targetY = (int){(p->position.y / 16) + p->direction.y};

    if (l->data[targetY][targetX].id > 1 &&
        l->data[targetY][targetX].cropType != CROPLESS) {
      l->data[targetY][targetX].growthStage++;
    }
  }

  if (p->curAction != NONE) {
    p->timer += dt;
  }
  if (p->timer >= 1.0f) {
    p->timer = 0.0f;
    p->curAction = NONE;
  }

  // Movement
  Vector2 moveDir = (Vector2){0.0f, 0.0f};

  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    moveDir.x = 1;
    p->direction = (Vector2){1.0f, 0.0f};
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    moveDir.y = 1;
    p->direction = (Vector2){0.0f, 1.0f};
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    moveDir.x = -1;
    p->direction = (Vector2){-1.0f, 0.0f};
  }
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    moveDir.y = -1;
    p->direction = (Vector2){0.0f, -1.0f};
  }

  AnimatePlayer(p, dt, moveDir);

  if (p->flipX) {
    if (p->frameRec.width > 0) {
      p->frameRec.width *= -1;
    }
  } else {
    if (p->frameRec.width < 0) {
      p->frameRec.width *= -1;
    }
  }

  if (Vector2Length(moveDir) > 0.0f) {
    moveDir = Vector2Normalize(moveDir);
  }
  Vector2 vel = Vector2Scale(moveDir, p->speed * dt);
  if (p->curAction == NONE) {
    p->position = Vector2Add(p->position, vel);
  }
}

void DrawPlayer(Player *p) {

  Rectangle destRec = {p->position.x, p->position.y, p->size.x, p->size.y};

  Vector2 origin = {p->size.x / 2.0f, p->size.y / 2.0f};

  DrawTexturePro(p->texture, p->frameRec, destRec, origin, 0, WHITE);
}

void UnloadPlayer(Player p) { UnloadTexture(p.texture); }
