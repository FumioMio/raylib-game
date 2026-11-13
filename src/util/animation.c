#include "animation.h"
#include <raylib.h>

Anim InitAnim(Texture2D texture, int startFrame, int endFrame, float speed) {

  static int next_id = 1;

  Anim anim;

  anim.id = next_id++;
  anim.texture = texture;
  anim.startFrame = startFrame;
  anim.endFrame = endFrame;
  anim.speed = speed;
  anim.curFrame = startFrame;
  anim.timeStamp = 0.0f;

  return anim;
}

void PlayAnim(Anim *anim, Texture2D *curTexture, Rectangle *frameRec,
              float dt) {
  TraceLog(LOG_INFO,
           "Anim TExture Width : %d , Anim TExture Height : %d \n "
           "curTexture Width : %d , curTexture Height : %d",
           anim->texture.width, anim->texture.height, curTexture->width,
           curTexture->height);
  const int sliceX =
      (int)((float)((float)(anim->texture.width) / frameRec->width));
  const int sliceY =
      (int)((float)((float)(anim->texture.height) / frameRec->height));
  TraceLog(LOG_INFO, "Slice X : %d Slice Y : %d", sliceX, sliceY);
  if (curTexture->id != anim->texture.id) {
    TraceLog(LOG_INFO, "CurTexture is not AnimTexture, %d %d", curTexture->id,
             anim->texture.id);
    curTexture = &anim->texture;
    TraceLog(LOG_INFO, "CurTexture : %d", curTexture->id);
    anim->curFrame = anim->startFrame;
    anim->timeStamp = 0.0f;
    frameRec->x = (float)((int)(anim->startFrame % sliceX));
    frameRec->y = (float)((int)(anim->startFrame / sliceY));
    TraceLog(LOG_INFO,
             "Current Frame : %d , Timestamp : %f , Rec_X : %f , Rec_Y : %f",
             anim->curFrame, anim->timeStamp, frameRec->x, frameRec->y);
  }
  TraceLog(LOG_INFO, "cur tex is same as the anim!");

  anim->timeStamp += dt;

  const float frameSpeed = (60.0f / anim->speed) * 0.1f;

  TraceLog(LOG_INFO, "frame_speed : %f , timestamp : %f", frameSpeed,
           anim->timeStamp);

  if (anim->timeStamp >= frameSpeed) {
    anim->timeStamp = 0.0f;
    anim->curFrame++;
    TraceLog(LOG_INFO, "Timestamp : %f , Current Frame : %d", anim->timeStamp,
             anim->curFrame);
    if (anim->curFrame > anim->endFrame) {
      anim->curFrame = anim->startFrame;
      TraceLog(LOG_INFO, "Current Frame : %d", anim->curFrame);
    }
  }

  TraceLog(LOG_INFO, "Proceed the frameRec_Transition! Cur frame : %d",
           anim->curFrame);

  int frameX = (float)((int)(anim->curFrame % sliceX));
  int frameY = (float)((int)(anim->curFrame / sliceY));

  frameRec->x = frameX * frameRec->width;
  frameRec->y = frameY * frameRec->height;

  TraceLog(LOG_INFO, "frameRec_X : %f , frameRec_Y : %f", frameRec->x,
           frameRec->y);
}
