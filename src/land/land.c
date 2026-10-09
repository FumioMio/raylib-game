#include "land.h"
#include "../util/util.h"
#include "raylib.h"
#include <assert.h>
#include <stdbool.h>

static const int autoTileMap[16] = {36, 25, 35, 24, 33, 22, 34, 23,
                                    3,  14, 2,  13, 0,  11, 1,  12};

Land InitLand(const char *filesource, const char *texturepath,
              const char *croptexturepath) {
  Land l;
  CsvLoaded csv;
  if (LoadCsv(&csv, filesource)) {

    for (int c = 0; c < MAP_HEIGHT; c++) {
      for (int r = 0; r < MAP_WIDTH; r++) {
        l.data[c][r].id = csv.data[c][r];
        l.data[c][r].isWatered = false;
        l.data[c][r].cropType = CROPLESS;
        l.data[c][r].daysGrown = 0;
        l.data[c][r].growthStage = 0;
      }
    }

    l.texture = LoadTexture(texturepath);
    l.cropTexture = LoadTexture(croptexturepath);
    return l;
  } else {
    return l;
  }
}

void DrawLand(Land *l) {

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if (l->data[y][x].id > 1) {
        int bitmask = 0;

        if (y > 0 && l->data[y - 1][x].id > 1)
          bitmask += 1;
        if (x > 0 && l->data[y][x - 1].id > 1)
          bitmask += 2;
        if (x < MAP_WIDTH - 1 && l->data[y][x + 1].id > 1)
          bitmask += 4;
        if (y < MAP_HEIGHT - 1 && l->data[y + 1][x].id > 1)
          bitmask += 8;

        int visualTileID = autoTileMap[bitmask];

        int tileCol = visualTileID % 11;
        int tileRow = visualTileID / 11;

        float srcX = (float)(tileCol * 16);
        float srcY = (float)(tileRow * 16);

        Rectangle frameRec = {(float){srcX}, (float){srcY}, 16, 16};
        Vector2 destPos = {(float){x * 16}, (float){y * 16}};

        Tile curTile = l->data[y][x];

        Color tileColor = (curTile.isWatered) ? BROWN : WHITE;

        DrawTextureRec(l->texture, frameRec, destPos, tileColor);

        if (curTile.cropType == WHEAT) {
          Rectangle cropRec = {(float)(16 * (l->data[y][x].growthStage + 1)), 0,
                               16.0f, 16.0f};
          Vector2 cropPos = {(float)(x * 16), (float)((y * 16) - 2)};
          DrawTextureRec(l->cropTexture, cropRec, cropPos, WHITE);
        }
      }
    }
  }
}

void UnloadLand(Land l) {
  UnloadTexture(l.texture);
  UnloadTexture(l.cropTexture);
}
