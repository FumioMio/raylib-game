#ifndef UI_H
#define UI_H

#include <raylib.h>

// Cursor
typedef struct Cursor {
  Vector2 position;
  Texture2D texture;
  Rectangle frameRec;
} Cursor;

Cursor InitCursor(Texture2D texture);
void UpdateCursor(Cursor *c, Camera2D cam);
void DrawCursor(Cursor *c);

// hover
typedef struct Hover {
  Vector2 position;
  Texture2D texture;
  Rectangle frameRec;
  NPatchInfo npatchInf;
  Vector2 size;
  bool visibility;
} Hover;

Hover InitHover(Texture2D texture);
void UpdateHover(Hover *h);
void DrawHover(Hover *h);

// buttons
typedef struct Button {
  Vector2 position;
  Vector2 size;
  Texture2D texture;
  Rectangle frameRec;
  NPatchInfo npatchInf;
  Font font;
  const char *text;
  bool isClicked;
  bool isHover;
} Button;

Button InitButton(Vector2 pos, Texture2D texture, Font font);
void UpdateButton(Button *btn, Cursor c);
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
  Hover hover;
} SettingPanel;

SettingPanel InitSetPanel(Texture2D texture, Font font);
void UpdateSetPanel(SettingPanel *sp, Cursor c);
void DrawSetPanel(SettingPanel *sp);

typedef struct FaceUi {
  Rectangle frameRec;
  Texture2D texture;
  Vector2 position;
  Rectangle faceRec;
  Texture2D faceText;
} FaceUi;

typedef struct Hud {
  FaceUi faceUi;
  Font font;
} Hud;

Hud InitHud(Texture2D basicUiText, Texture2D faceText, Font font);
void DrawHud(Hud *hud);

#endif // !UI_H
