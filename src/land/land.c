#include "land.h"
#include "raylib.h"

static const int autoTileMap[16] = {36, 25, 35, 24, 33, 22, 34, 23,
                                    3,  14, 2,  13, 0,  11, 1,  12};

void loadCsv(const char *filesource, Land *l) {
  FILE *file = fopen(filesource, "r");

  if (file == NULL) {
    TraceLog(LOG_ERROR, "Gagal membuka file map csv");
    return;
  }

  char baris[1024];
  int c = 0;

  while (fgets(baris, sizeof(baris), file) && c < MAP_HEIGHT) {
    int r = 0;

    char *token = strtok(baris, ",\n\r");
    while (token != NULL && r < MAP_WIDTH) {
      l->data[c][r] = atoi(token);
      r++;
      token = strtok(NULL, ",\n\r");
    }
    c++;
  }

  fclose(file);
  TraceLog(LOG_INFO, "peta berhasil di load!!");
}

Land InitLand(const char *filesource, const char *texturepath,
              const char *croptexturepath) {
  Land l;
  loadCsv(filesource, &l);
  l.texture = LoadTexture(texturepath);
  l.cropTexture = LoadTexture(croptexturepath);
  return l;
}

void DrawLand(Land *l) {

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if (l->data[y][x] > 1) {
        int bitmask = 0;

        if (y > 0 && l->data[y - 1][x] > 1)
          bitmask += 1;
        if (x > 0 && l->data[y][x - 1] > 1)
          bitmask += 2;
        if (x < MAP_WIDTH - 1 && l->data[y][x + 1] > 1)
          bitmask += 4;
        if (y < MAP_HEIGHT - 1 && l->data[y + 1][x] > 1)
          bitmask += 8;

        int visualTileID = autoTileMap[bitmask];

        int tileCol = visualTileID % 11;
        int tileRow = visualTileID / 11;

        float srcX = (float)(tileCol * 16);
        float srcY = (float)(tileRow * 16);

        Rectangle frameRec = {(float){srcX}, (float){srcY}, 16, 16};
        Vector2 destPos = {(float){x * 16}, (float){y * 16}};

        DrawTextureRec(l->texture, frameRec, destPos, WHITE);
      }
    }
  }
}

void UnloadLand(Land l) {
  UnloadTexture(l.texture);
  UnloadTexture(l.cropTexture);
}
