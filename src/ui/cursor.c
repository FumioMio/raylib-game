#include "cursor.h"
#include <raylib.h>

Cursor InitCursor(Texture2D texture) {

  Cursor cursor;

  cursor.frameRec = (Rectangle){336.0f, 128.0f, 16.0f, 16.0f};

  cursor.position = (Vector2){-100.0f, -100.0f};

  cursor.texture = texture;

  return cursor;
}

void UpdateCursor(Cursor *c) {
  c->position = GetMousePosition();
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) ||
      IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    c->frameRec.x = (float)(368.0f);
  } else {
    c->frameRec.x = (float)(336.0f);
  }
}

void DrawCursor(Cursor *c) {
  Rectangle destCursor = {c->position.x, c->position.y,
                          c->frameRec.width * 2.0f, c->frameRec.height * 2.0f};

  DrawTexturePro(c->texture, c->frameRec, destCursor, (Vector2){0.0f, 0.0f},
                 0.0f, WHITE);
}
