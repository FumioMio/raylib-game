#include "ui.h"
#include <raylib.h>
#include <stdbool.h>

SettingPanel InitSetPanel(Texture2D texture) {
  SettingPanel setpanel;

  setpanel.texture = texture;
  setpanel.frameRec = (Rectangle){0.0f, 96.0f, 48.0f, 48.0f};

  // nine patch
  setpanel.ninePatchInf.source = setpanel.frameRec;
  setpanel.ninePatchInf.layout = NPATCH_NINE_PATCH;
  setpanel.ninePatchInf.top = 16;
  setpanel.ninePatchInf.bottom = 16;
  setpanel.ninePatchInf.right = 16;
  setpanel.ninePatchInf.left = 16;

  setpanel.position = (Vector2){240.0f, 160.0f};
  setpanel.size = (Vector2){240.0f, 300.0f};

  setpanel.visibility = false;

  Button btn1;
  btn1 = InitButton(setpanel.position, texture);

  setpanel.buttons[0] = btn1;

  return setpanel;
}

void UpdateSetPanel(SettingPanel *sp, Camera2D cam) {
  if (IsKeyPressed(KEY_ESCAPE)) {
    sp->visibility = !sp->visibility;
  }

  if (!sp->visibility)
    return;

  sp->position = GetScreenToWorld2D(
      (Vector2){(GetScreenWidth() / 2.0f), (GetScreenHeight() / 2.0f)}, cam);

  UpdateButtonCam(&sp->buttons[0], cam);
}

void DrawSetPanel(SettingPanel *sp) {
  if (!sp->visibility)
    return;
  Rectangle destRec = {sp->position.x, sp->position.y, sp->size.x, sp->size.y};

  Vector2 origin = {sp->size.x / 2.0f, sp->size.y / 2.0f};

  DrawTextureNPatch(sp->texture, sp->ninePatchInf, destRec, origin, 0.0f,
                    WHITE);
  DrawButton(&sp->buttons[0]);
}
