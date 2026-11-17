#ifndef GAME_SCREEN

#define GAME_SCREEN

#include <raylib.h>

typedef enum GameScreen { MAIN_MENU = 0, GAMEPLAY } GameScreen;

void UpdateMainMenu(GameScreen *currentScreen);
void DrawMainMenu();

void InitGameplay();
void UpdateGameplay(GameScreen *currentScreen);
void DrawGameplay();

#endif // !GAME_SCREEN
