#include "ui.h"
#include <math.h>
#include <raylib.h>
#include <stdbool.h>

SettingPanel InitSetPanel(Texture2D texture, Font font) {
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
  btn1 = InitButton(setpanel.position, texture, font);
  btn1.text = "return";
  btn1.size.x = 112.0f;
  btn1.position.y += 60;

  Button btn2;
  btn2 = InitButton(setpanel.position, texture, font);
  btn2.text = "quit";
  btn2.size.x = 112.0f;
  btn2.position.y += 100;

  setpanel.buttons[0] = btn1;
  setpanel.buttons[1] = btn2;

  Hover hover;

  hover = InitHover(texture);

  setpanel.hover = hover;

  return setpanel;
}

void UpdateSetPanel(SettingPanel *sp, Cursor c) {
  if (IsKeyPressed(KEY_ESCAPE)) {
    sp->visibility = !sp->visibility;
  }

  if (!sp->visibility)
    return;

  for (int i = 0; i < 2; i++) {
    UpdateButton(&sp->buttons[i], c);
  }

  if (sp->buttons[0].isClicked && sp->visibility != false) {
    sp->visibility = false;
  }
  if (sp->buttons[1].isClicked) {
    CloseWindow();
  }
  if (sp->buttons[1].isHover) {
    sp->hover.visibility = true;
    sp->hover.position = sp->buttons[1].position;
    sp->hover.size.x = sp->buttons[1].size.x;
    sp->hover.size.y = sp->buttons[1].size.y;
  } else {
    sp->hover.visibility = false;
  }
}

void DrawSetPanel(SettingPanel *sp) {
  if (!sp->visibility)
    return;

  Rectangle destRec = {sp->position.x, sp->position.y, sp->size.x, sp->size.y};

  Vector2 origin = {sp->size.x / 2.0f, sp->size.y / 2.0f};

  DrawTextureNPatch(sp->texture, sp->ninePatchInf, destRec, origin, 0.0f,
                    WHITE);
  for (int i = 0; i < 2; i++) {
    DrawButton(&sp->buttons[i]);
  }

  DrawHover(&sp->hover);
}
