#ifndef LAND
#define LAND

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

enum CropType { CROPLESS = 0, WHEAT, TOMAT };

typedef struct Tile {
  int id;
  bool isWatered;
  int growthStage;
  int daysGrown;
  int cropType;
} Tile;

typedef struct Land {
  Tile data[MAP_HEIGHT][MAP_WIDTH];
  Texture2D texture;
  Texture2D cropTexture;
} Land;

Land InitLand(const char *filesource, const char *texturepath,
              const char *croptexturepath);
void DrawLand(Land *l);
void UnloadLand(Land l);

#endif
