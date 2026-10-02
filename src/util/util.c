#include "util.h"
#include "raylib.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool LoadCsv(CsvLoaded *csv, const char *filesource) {
  FILE *file = fopen(filesource, "r");

  if (file == NULL) {
    TraceLog(LOG_ERROR, "Gagal membuka file map csv");
    assert(false);
    return false;
  }

  char baris[1024];
  int c = 0;

  while (fgets(baris, sizeof(baris), file) && c < MAP_HEIGHT) {
    int r = 0;

    char *token = strtok(baris, ",\n\r");
    while (token != NULL && r < MAP_WIDTH) {
      csv->data[c][r] = atoi(token);
      r++;
      token = strtok(NULL, ",\n\r");
    }
    c++;
  }

  fclose(file);
  TraceLog(LOG_INFO, "peta berhasil di load!!");
  return true;
}
