#include "ui.h"
#include <raylib.h>

Cursor InitCursor(Texture2D texture) {

  Cursor cursor;

  cursor.frameRec = (Rectangle){336.0f, 128.0f, 16.0f, 16.0f};

  cursor.position = (Vector2){-100.0f, -100.0f};

  cursor.texture = texture;

  return cursor;
}

void UpdateCursor(Cursor *c, Camera2D cam) {
  c->position = GetScreenToWorld2D(GetMousePosition(), cam);
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) ||
      IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    c->frameRec.x = (float)(368.0f);
  } else {
    c->frameRec.x = (float)(336.0f);
  }
}

void DrawCursor(Cursor *c) {
  Rectangle destCursor = {(float)((int)(c->position.x)),
                          (float)((int)(c->position.y)), c->frameRec.width,
                          c->frameRec.height};

  DrawTexturePro(c->texture, c->frameRec, destCursor, (Vector2){0.0f, 0.0f},
                 0.0f, WHITE);
}
