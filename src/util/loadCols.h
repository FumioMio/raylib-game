#ifndef LOADCOLS
#define LOADCOLS

#include "raylib.h"

#define MAX_RECTANGLES 500

typedef struct Cols {
  Rectangle recs[MAX_RECTANGLES];
  int actualSize;
} Cols;

void LoadCols(const char *filepath, Cols *cols);

#endif
