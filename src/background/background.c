#include "background.h"
#include "raylib.h"

Background InitBackground(const char *source) {
  Background b;
  b.texture = LoadTexture(source);
  b.rec = (Rectangle){0.0f, 0.0f, b.texture.width, b.texture.height};
  return b;
}

void DrawBackground(Background b) {
  Rectangle backDst = {0.0f, 0.0f, b.texture.width, b.texture.height};

  DrawTexturePro(b.texture, b.rec, backDst, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
}

void UnloadBackground(Background b) { UnloadTexture(b.texture); }
