#ifndef CURSOR_H
#define CURSOR_H

#include "raylib.h"

typedef struct Cursor {
  Vector2 position;
  Texture2D texture;
  Rectangle frameRec;
} Cursor;

Cursor InitCursor(Texture2D texture);
void UpdateCursor(Cursor *c);
void DrawCursor(Cursor *c);

#endif // !CURSOR_H
