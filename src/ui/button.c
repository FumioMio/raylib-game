#include "ui.h"
#include <raylib.h>
#include <stdbool.h>

Button InitButton(Vector2 pos, Texture2D texture, Font font) {
  Button btn;
  btn.position = pos;
  btn.texture = texture;
  btn.frameRec = (Rectangle){0.0f, 48.0f, 48.0f, 48.0f};

  btn.npatchInf.source = btn.frameRec;
  btn.npatchInf.top = 16;
  btn.npatchInf.bottom = 16;
  btn.npatchInf.right = 16;
  btn.npatchInf.left = 16;
  btn.npatchInf.layout = NPATCH_NINE_PATCH;

  btn.font = font;
  btn.text = "test";
  btn.size = (Vector2){96.0f, 48.0f};
  btn.isHover = false;

  return btn;
}

void UpdateButton(Button *btn, Cursor c) {

  Vector2 mousePos = c.position;

  btn->isClicked = false;
  btn->isHover = false;

  if (mousePos.x >= (btn->position.x + (btn->size.x / -2.0f)) &&
      mousePos.x <= (btn->position.x + (btn->size.x / 2.0f)) &&
      mousePos.y >= (btn->position.y + (btn->size.y / -2.0f)) &&
      mousePos.y <= (btn->position.y + (btn->size.y / 2.0f))) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      btn->frameRec.x = 96.0f;
    } else {
      btn->frameRec.x = 48.0f;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      btn->isClicked = true;
    }

    btn->isHover = true;

  } else {
    btn->frameRec.x = 0.0f;
  }

  btn->npatchInf.source = btn->frameRec;
}

void DrawButton(Button *btn) {
  Rectangle destRec =
      (Rectangle){btn->position.x, btn->position.y, btn->size.x, btn->size.y};

  Vector2 origin =
      (Vector2){(float)(btn->size.x / 2.0f), (float)(btn->size.y / 2.0f)};

  Vector2 textSize = MeasureTextEx(btn->font, btn->text, 16.0f, 1.0f);

  Vector2 textOrigin = (Vector2){textSize.x / 2.0f, textSize.y / 2.0f};

  DrawTextureNPatch(btn->texture, btn->npatchInf, destRec, origin, 0.0f, WHITE);
  DrawTextPro(btn->font, btn->text, btn->position, textOrigin, 0.0f, 16.0f,
              1.0f, WHITE);
}
