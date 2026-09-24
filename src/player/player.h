#ifndef PLAYER
#define PLAYER

#include <raylib.h>

typedef struct Player {
  Texture2D texture;
  Vector2 position;
  float speed;
  Rectangle frameRec;
  int currentFrameX;
  int currentFrameY;
  float frameCounter;
  float frameSpeed;
  Vector2 size;
  bool flipX;
} Player;

Player InitPlayer(Vector2 pos, float speed, const char *texturePath);
void UpdatePlayer(Player *p, float dt);
void DrawPlayer(Player *p);
void UnloadPlayer(Player p);

#endif // !PLAYER
