#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "../background/background.h"
#include "../land/land.h"
#include "../player/player.h"
#include "../ui/ui.h"
#include "../util/loadCols.h"
#include "gameScreen.h"
#include <raylib.h>
#include <raymath.h>

typedef struct GameUi {
  Cursor *cursor;
  SettingPanel setpanel;
  Hud hud;
} GameUi;

typedef struct GameObj {
  Player player;
  Land farmable;
  Cols obstacle;
  Background background;
  Camera2D camera;
} GameObj;

void InitGameplay(GameObj *gameObj, GameUi *gameUi, Cursor *cursor,
                  Texture2D basicUiTexture, Font basicPixelText);
void UpdateGameplay(GameScreen *currentScreen, GameObj *gameObj, GameUi *gameUi,
                    Camera2D screencam);
void DrawGameplay(GameObj *gameObj, GameUi *gameUi);
void UnloadGameplay(GameObj *gameObj, GameUi *gameUi);

#endif // !GAMEPLAY_H
