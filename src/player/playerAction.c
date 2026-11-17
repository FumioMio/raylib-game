#include "player.h"
#include <raylib.h>
#include <stdbool.h>

void PlayerAction(Player *p, Land *l, float dt) {
  bool actionKey[4] = {IsKeyPressed(KEY_ENTER), IsKeyPressed(KEY_P),
                       IsKeyPressed(KEY_L), IsKeyPressed(KEY_K)};

  for (int i = 0; i < sizeof(actionKey); i++) {
    if (actionKey[i]) {
      int targetX = (int){(p->position.x / 16) + p->direction.x};
      int targetY = (int){(p->position.y / 16) + p->direction.y};

      Tile curTile = l->data[targetY][targetX];

      switch (i) {
      case SOILING:
        curTile.id = (curTile.id == 0) ? 2 : curTile.id;
        break;

      case WATERING:
        curTile.isWatered = (curTile.id > 1) ? true : false;
        break;

      case PLANTING:
        curTile.cropType = (curTile.id > 1 && curTile.cropType == CROPLESS)
                               ? WHEAT
                               : curTile.cropType;
        break;

      case GROWING:
        curTile.growthStage = (curTile.cropType != CROPLESS)
                                  ? curTile.growthStage + 1
                                  : curTile.growthStage;
        break;
      }
      p->curAction = i;

      l->data[targetY][targetX] = curTile;
    }
  }
}
