#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

typedef struct CsvLoaded {
  int data[20][30];
} CsvLoaded;

bool LoadCsv(CsvLoaded *csv, const char *filesource);

#endif
