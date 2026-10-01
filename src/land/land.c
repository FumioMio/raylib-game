#include "land.h"
#include "raylib.h"

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

Land InitLand(const char *filesource, const char *texturepath) {
  Land l;
  loadCsv(filesource, &l);
  l.texture = LoadTexture(texturepath);
  l.frameRec = (Rectangle){48.0f, 48.0f, 16.0f, 16.0f};
  return l;
}

void DrawLand(Land *l) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if (l->data[y][x] > 1) {
        Vector2 destPos = {(float){x * 16}, (float){y * 16}};

        DrawTextureRec(l->texture, l->frameRec, destPos, WHITE);
      }
    }
  }
}

void UnloadLand(Land l) { UnloadTexture(l.texture); }
