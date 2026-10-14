#ifndef UI_H
#define UI_H

#include "raylib.h"

// Cursor
typedef struct Cursor {
  Vector2 position;
  Texture2D texture;
  Rectangle frameRec;
} Cursor;

Cursor InitCursor(Texture2D texture);
void UpdateCursor(Cursor *c);
void DrawCursor(Cursor *c);

// buttons
typedef struct Button {
  Vector2 position;
  Texture2D texture;
  Rectangle frameRec;
} Button;

Button InitButton(Vector2 pos, Texture2D texture);
void UpdateButton(Button *btn);
void UpdateButtonCam(Button *btn, Camera2D cam);
void DrawButton(Button *btn);

// Setting panel
typedef struct SettingPanel {
  Vector2 position;
  Vector2 size;
  Texture2D texture;
  Rectangle frameRec;
  NPatchInfo ninePatchInf;
  bool visibility;
  Button buttons[5];
} SettingPanel;

SettingPanel InitSetPanel(Texture2D texture);
void UpdateSetPanel(SettingPanel *sp, Camera2D cam);
void DrawSetPanel(SettingPanel *sp);

#endif // !UI_H
