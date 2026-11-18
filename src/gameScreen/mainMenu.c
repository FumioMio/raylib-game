#include "gameScreen.h"
#include <raylib.h>

int UpdateMainMenu() {
  if (IsKeyPressed(KEY_ENTER)) {
    return 1;
  } else if (IsKeyPressed(KEY_ESCAPE)) {
    return 2;
  }
  return 0;
}

void DrawMainMenu(Font pixelFont) {
  DrawTextEx(pixelFont, "Press ENTER to Play! \n Press ESC to Close!",
             (Vector2){0.0, 0.0}, 12.0f, 1.0, BLUE);
}
