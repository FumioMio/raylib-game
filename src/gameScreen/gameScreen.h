#ifndef GAME_SCREEN

#define GAME_SCREEN

#include <raylib.h>

typedef enum GameScreen { MAIN_MENU = 0, GAMEPLAY } GameScreen;

void UpdateMainMenu(GameScreen *currentScreen);
void DrawMainMenu();

#endif // !GAME_SCREEN
