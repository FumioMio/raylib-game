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

  // Rectangle frame
  Rectangle frameRec = (Rectangle){0.0f, 0.0f, player.size.x, player.size.y};

  player.anim[IDLE_DOWN] = InitAnim(player.basicTexture, 0, 1, 16);
  player.anim[IDLE_UP] = InitAnim(player.basicTexture, 4, 5, 16);
  player.anim[IDLE_SIDE] = InitAnim(player.basicTexture, 8, 9, 16);

  player.anim[MOVE_DOWN] = InitAnim(player.basicTexture, 2, 3, 16);
  player.anim[MOVE_UP] = InitAnim(player.basicTexture, 6, 7, 16);
  player.anim[MOVE_SIDE] = InitAnim(player.basicTexture, 10, 11, 16);

  player.anim[WATER_DOWN] = InitAnim(player.actionTexture, 16, 17, 24);
  player.anim[WATER_UP] = InitAnim(player.actionTexture, 18, 19, 24);
  player.anim[WATER_SIDE] = InitAnim(player.actionTexture, 20, 21, 24);

  player.anim[SOIL_DOWN] = InitAnim(player.actionTexture, 0, 1, 24);
  player.anim[SOIL_UP] = InitAnim(player.actionTexture, 2, 3, 24);
  player.anim[SOIL_SIDE] = InitAnim(player.actionTexture, 4, 5, 24);

  player.sprite =
      InitSprite(frameRec, player.basicTexture, player.anim[IDLE_DOWN].id);

  player.colShape = (Rectangle){pos.x - 5.0f, pos.y, 10.0f, 8.0f};

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

  if (p->sprite.flipX && p->sprite.frameRec.width > 0) {
    p->sprite.frameRec.width *= -1;
  } else if (!p->sprite.flipX && p->sprite.frameRec.width < 0) {
    p->sprite.frameRec.width *= -1;
  }

  if (p->sprite.flipY && p->sprite.frameRec.height > 0) {
    p->sprite.frameRec.height *= -1;
  } else if (!p->sprite.flipY && p->sprite.frameRec.height < 0) {
    p->sprite.frameRec.height *= -1;
  }

  DrawTexturePro(p->sprite.texture, p->sprite.frameRec, destRec, origin, 0,
                 WHITE);
}

void UnloadPlayer(Player p) {
  UnloadTexture(p.basicTexture);
  UnloadTexture(p.actionTexture);
  UnloadTexture(p.sprite.texture);
}
