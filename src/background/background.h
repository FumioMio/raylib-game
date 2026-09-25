#ifndef BACKGROUND

#define BACKGROUND
#include "raylib.h"

typedef struct Background {
  Texture2D texture;
  Rectangle rec;
} Background;

Background InitBackground(const char *source);
void DrawBackground(Background b);
void UnloadBackground(Background b);
#endif // !BACKGROUND
