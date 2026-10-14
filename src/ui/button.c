#include "ui.h"
#include <raylib.h>

Button InitButton(Vector2 pos, Texture2D texture) {
  Button btn;
  btn.position = pos;
  btn.texture = texture;
  btn.frameRec = (Rectangle){0.0f, 48.0f, 48.0f, 48.0f};

  return btn;
}

void UpdateButtonCam(Button *btn, Camera2D cam) {

  Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), cam);

  if (mousePos.x >= btn->position.x &&
      mousePos.x <= (btn->position.x + btn->frameRec.width) &&
      mousePos.y >= btn->position.y &&
      mousePos.y <= (btn->position.y + btn->frameRec.height)) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      btn->frameRec.x = 96.0f;
    } else {
      btn->frameRec.x = 48.0f;
    }
  } else {
    btn->frameRec.x = 0.0f;
  }
}

void DrawButton(Button *btn) {
  DrawTextureRec(btn->texture, btn->frameRec, btn->position, WHITE);
}
