#include "gameplay.h"
#include <raylib.h>

void InitGameplay(GameObj *gameObj, GameUi *gameUi, Cursor *cursor,
                  Texture2D basicUiTexture, Font basicPixelText) {
  gameObj->obstacle = (Cols){0};

  LoadCols("assets/mymap.json", &gameObj->obstacle);

  gameUi->cursor = cursor;

  gameObj->farmable = InitLand("assets/mymap_farmable.csv",
                               "assets/Tilesets/Tilled_Dirt_Wide_v2.png",
                               "assets/Objects/Basic_Plants.png");

  gameObj->player =
      InitPlayer((Vector2){140.0f, 180.0f}, 50.0f,
                 "assets/Characters/BasicCharakterSpritesheet.png",
                 "assets/Characters/CharAction.png");

  gameObj->background = InitBackground("assets/mymap.png");

  gameUi->hud =
      InitHud(basicUiTexture,
              "assets/SproutLandUI/spritesheets/Dialouge/Emotes/emote.png",
              basicPixelText);

  gameUi->setpanel = InitSetPanel(basicUiTexture, basicPixelText);

  gameObj->camera = (Camera2D){0};
  gameObj->camera.offset = (Vector2){0.0f, 0.0f};
  gameObj->camera.rotation = 0.0f;
  gameObj->camera.zoom = 1.0f;
}

void UpdateGameplay(GameScreen *currentScreen, GameObj *gameObj, GameUi *gameUi,
                    Camera2D screencam) {
  float dt = GetFrameTime();

  UpdatePlayer(&gameObj->player, &gameObj->farmable, &gameObj->obstacle, dt);

  UpdateSetPanel(&gameUi->setpanel, *gameUi->cursor, currentScreen);
}

void DrawGameplay(GameObj *gameObj, GameUi *gameUi) {

  BeginMode2D(gameObj->camera);

  DrawBackground(gameObj->background);

  DrawLand(&gameObj->farmable);

  DrawPlayer(&gameObj->player);

  EndMode2D();

  DrawHud(&gameUi->hud);

  DrawSetPanel(&gameUi->setpanel);
}

void UnloadGameplay(GameObj *gameObj, GameUi *gameUi) {
  UnloadPlayer(gameObj->player);
  UnloadBackground(gameObj->background);
  UnloadLand(gameObj->farmable);
}
