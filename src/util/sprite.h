#ifndef SPRITE_H
#define SPRITE_H

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

typedef struct Sprite {
  int id;
  Rectangle frameRec;
  Texture2D texture;
  int animId;
} Sprite;

Sprite InitSprite(Rectangle frameRec, Texture2D defaultTexture,
                  int defaultAnimID);
Anim InitAnim(Texture2D texture, int startFrame, int endFrame, float speed);
void PlayAnim(Anim *anim, Sprite *sprite, float dt);

#endif // !SPRITE_H
