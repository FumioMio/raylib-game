#include "player.h"

void PlayerMovement(Player *p, Cols *obstacle, float dt) {
  p->previousPos = p->position;

  Vector2 moveDir = (Vector2){0.0f, 0.0f};

  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    moveDir.x = 1;
    p->direction = (Vector2){1.0f, 0.0f};
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    moveDir.x = -1;
    p->direction = (Vector2){-1.0f, 0.0f};
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    moveDir.y = 1;
    p->direction = (Vector2){0.0f, 1.0f};
  }
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    moveDir.y = -1;
    p->direction = (Vector2){0.0f, -1.0f};
  }

  if (Vector2Length(moveDir) > 0.0f) {
    moveDir = Vector2Normalize(moveDir);
  }
  Vector2 vel = Vector2Scale(moveDir, p->speed * dt);

  p->position.x += vel.x;
  p->colShape.x = p->position.x - 5;

  for (int i = 0; i < obstacle->actualSize; i++) {
    Rectangle obs = obstacle->recs[i];
    if (CheckCollisionRecs(p->colShape, obs)) {
      p->position.x = p->previousPos.x;
      break;
    }
  }

  p->position.y += vel.y;
  p->colShape.y = p->position.y;

  for (int i = 0; i < obstacle->actualSize; i++) {
    Rectangle obs = obstacle->recs[i];
    if (CheckCollisionRecs(p->colShape, obs)) {
      p->position.y = p->previousPos.y;
      break;
    }
  }
}
