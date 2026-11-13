#ifndef ANIMATION
#define ANIMATION

#include <raylib.h>

typedef struct Anim {
  int id;
  Texture2D texture;
  int startFrame;
  int endFrame;
  int curFrame;
  float timeStamp;
  float speed;
} Anim;

Anim InitAnim(Texture2D texture, int startFrame, int endFrame, float speed);
void PlayAnim(Anim *anim, Texture2D *curTexture, Rectangle *frameRec, float dt);

#endif // !ANIMATION
