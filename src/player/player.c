#include "player.h"
#include <raylib.h>
#include <stdbool.h>

Player InitPlayer(Vector2 pos, float speed, const char *basicTexturePath,
                  const char *actionTexturePath) {

  // Player initialization
  Player player;

  // Player Pos, Speed, Direction, Size
  player.position = pos;
  player.previousPos = pos;
  player.speed = speed;
  player.direction = (Vector2){0.0f, 1.0f};
  player.size = (Vector2){48.0f, 48.0f};

  // Texture Load
  player.basicTexture = LoadTexture(basicTexturePath);
  player.actionTexture = LoadTexture(actionTexturePath);
  player.texture = player.basicTexture;

  // Rectangle frame
  player.frameRec = (Rectangle){0.0f, 0.0f, player.size.x, player.size.y};
  player.colShape = (Rectangle){pos.x - 5.0f, pos.y, 10.0f, 8.0f};

  // Animation init
  player.currentFrameX = 0;
  player.currentFrameY = 0;
  player.frameCounter = 0;
  player.frameSpeed = (float)(4.0f);
  player.flipX = false;
  player.curAction = NONE;
  player.timer = 0.0f;

  return player;
}

void UpdatePlayer(Player *p, Land *l, Cols *obstacle, float dt) {

  if (p->curAction == NONE) {

    PlayerAction(p, l, dt);

    PlayerMovement(p, obstacle, dt);
  }

  if (p->curAction != NONE) {
    p->timer += dt;
  }
  if (p->timer >= 0.5f) {
    p->timer = 0.0f;
    p->curAction = NONE;
  }

  AnimatePlayer(p, dt);
}

void DrawPlayer(Player *p) {

  Rectangle destRec = {p->position.x, p->position.y, p->size.x, p->size.y};

  Vector2 origin = {p->size.x / 2.0f, p->size.y / 2.0f};

  DrawTexturePro(p->texture, p->frameRec, destRec, origin, 0, WHITE);
}

void UnloadPlayer(Player p) {
  UnloadTexture(p.basicTexture);
  UnloadTexture(p.actionTexture);
  UnloadTexture(p.texture);
}
