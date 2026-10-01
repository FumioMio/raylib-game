#ifndef PLAYER
#define PLAYER

#include "../land/land.h"
#include <raylib.h>

enum PlayerAction {
  NONE = 0,
  SOILING = 1,
};

typedef struct Player {
  Texture2D texture;
  Vector2 position;
  float speed;
  Vector2 direction;
  Rectangle frameRec;
  int currentFrameX;
  int currentFrameY;
  float frameCounter;
  float frameSpeed;
  Vector2 size;
  bool flipX;
  int curAction;
  float timer;
} Player;

Player InitPlayer(Vector2 pos, float speed, const char *texturePath);
void UpdatePlayer(Player *p, Land *l, float dt);
void DrawPlayer(Player *p);
void UnloadPlayer(Player p);

#endif // !PLAYER
