#include "ui.h"
#include <raylib.h>

Hud InitHud(Texture2D basicUiText, Texture2D faceText, Font font) {
  FaceUi faceUi;
  faceUi.texture = basicUiText;
  faceUi.position = (Vector2){0.0f, 0.0f};
  faceUi.frameRec = (Rectangle){144.0f, 96.0f, 48.0f, 48.0f};
  faceUi.faceText = faceText;
  faceUi.faceRec = (Rectangle){0.0f, 0.0f, 32.0f, 32.0f};

  Hud hud;
  hud.font = font;
  hud.faceUi = faceUi;

  return hud;
}

void DrawHud(Hud *hud) {
  DrawTextureRec(hud->faceUi.texture, hud->faceUi.frameRec,
                 hud->faceUi.position, WHITE);
  DrawTextureRec(hud->faceUi.faceText, hud->faceUi.faceRec,
                 hud->faceUi.position, WHITE);
}
