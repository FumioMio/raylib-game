#ifndef GAME_SCREEN

#define GAME_SCREEN

#include <raylib.h>

typedef enum GameScreen { MAIN_MENU = 0, GAMEPLAY } GameScreen;

int UpdateMainMenu();
void DrawMainMenu(Font pixelFont);

#endif // !GAME_SCREEN
