#include "player.h"

void AnimatePlayer(Player *p, float dt) {
  p->frameCounter += dt;
  int animX = 0;

  if (p->direction.y > 0.0f) {
    p->currentFrameY = 0;
  } else if (p->direction.y < 0.0f) {
    p->currentFrameY = 1;
  } else if (p->direction.x != 0.0f) {
    p->currentFrameY = 2;
    p->flipX = (p->direction.x > 0.0f) ? true : false;
  }

  // Action Anim
  if (p->curAction == NONE) {
    p->texture = p->basicTexture;
    // Movement anim
    if (p->previousPos.y != p->position.y ||
        p->previousPos.x != p->position.x) {
      animX = 2;
    }
  } else {
    if (p->texture.width != p->actionTexture.width) {
      p->currentFrameX = 0;
      p->frameCounter = 0.0f;
    }
    animX = 0;
    p->texture = p->actionTexture;
    if (p->curAction == WATERING) {
      if (p->currentFrameY < 8) {
        p->currentFrameY += 8;
      }
    }
  }

  // Anim process
  if (p->frameCounter >= (1.0f / p->frameSpeed)) {
    p->frameCounter = 0.0f;
    p->currentFrameX++;
    if (p->currentFrameX > (animX + 1) || p->currentFrameX < animX) {
      p->currentFrameX = animX;
    }
  }
  p->frameRec.x = p->currentFrameX * p->size.x;
  p->frameRec.y = p->currentFrameY * p->size.y;

  if (p->flipX) {
    if (p->frameRec.width > 0) {
      p->frameRec.width *= -1;
    }
  } else {
    if (p->frameRec.width < 0) {
      p->frameRec.width *= -1;
    }
  }
}
