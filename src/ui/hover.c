#include "ui.h"
#include <raylib.h>
#include <stdbool.h>

Hover InitHover(Texture2D texture) {
  Hover hover;
  hover.texture = texture;
  hover.position = (Vector2){0.0f, 0.0f};
  hover.size = (Vector2){32.0f, 32.0f};

  hover.frameRec = (Rectangle){144.0f, 144.0f, 32.0f, 32.0f};

  hover.npatchInf.source = hover.frameRec;
  hover.npatchInf.layout = NPATCH_NINE_PATCH;
  hover.npatchInf.top = 16;
  hover.npatchInf.bottom = 16;
  hover.npatchInf.right = 16;
  hover.npatchInf.left = 16;

  hover.visibility = false;

  return hover;
}

void UpdateHover(Hover *h) {}

void DrawHover(Hover *h) {
  if (!h->visibility)
    return;
  Rectangle destRec =
      (Rectangle){h->position.x, h->position.y, h->size.x, h->size.y};

  Vector2 origin = {destRec.width / 2.0f, destRec.height / 2.0f};

  DrawTextureNPatch(h->texture, h->npatchInf, destRec, origin, 0.0f, WHITE);
}
