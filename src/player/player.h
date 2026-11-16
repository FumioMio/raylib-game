#ifndef PLAYER
#define PLAYER

#include "../land/land.h"
#include "../util/loadCols.h"
#include "../util/sprite.h"
#include "raymath.h"
#include <raylib.h>

enum PlayerAction { NONE = -1, SOILING, WATERING, PLANTING, GROWING };
enum PlayerAnim { IDLE_DOWN = 0, IDLE_UP, IDLE_SIDE };

typedef struct Player {
  Texture2D basicTexture;
  Texture2D actionTexture;
  Vector2 position;
  Vector2 previousPos;
  float speed;
  Vector2 direction;
  Sprite sprite;
  Rectangle colShape;
  int currentFrameX;
  int currentFrameY;
  Anim anim[10];
  float frameCounter;
  float frameSpeed;
  Vector2 size;
  bool flipX;
  int curAction;
  float timer;
} Player;

Player InitPlayer(Vector2 pos, float speed, const char *basicTexturePath,
                  const char *actionTexturePath);
void UpdatePlayer(Player *p, Land *l, Cols *obstacle, float dt);
void DrawPlayer(Player *p);
void UnloadPlayer(Player p);

void AnimatePlayer(Player *p, float dt);
void PlayerAction(Player *p, Land *l, float dt);
void PlayerMovement(Player *p, Cols *obstacle, float dt);
#endif // !PLAYER
