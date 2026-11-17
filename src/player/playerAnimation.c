#include "player.h"

void AnimatePlayer(Player *p, float dt) {
  enum PlayerAnim curAnim = IDLE_DOWN;

  if (p->curAction == WATERING) {

    curAnim = WATER_DOWN;

  } else if (p->curAction == SOILING) {

    curAnim = SOIL_DOWN;

  } else {

    curAnim =
        (p->position.x != p->previousPos.x || p->position.y != p->previousPos.y)
            ? MOVE_DOWN
            : IDLE_DOWN;
  }

  curAnim += (p->direction.y < 0.0f) ? 1 : (p->direction.x != 0.0f) ? 2 : 0;

  p->sprite.flipX = (p->direction.x > 0.0f || p->position.x > p->previousPos.x)
                        ? true
                        : false;

  PlayAnim(&p->anim[curAnim], &p->sprite, dt);
}
