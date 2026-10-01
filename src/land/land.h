#ifndef LAND

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

typedef struct Land {
  int data[MAP_HEIGHT][MAP_WIDTH];
  Texture2D texture;
  Rectangle frameRec;
} Land;

Land InitLand(const char *filesource, const char *texturepath);
void DrawLand(Land *l);
void UnloadLand(Land l);

#endif
