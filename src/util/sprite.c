#include "sprite.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

Sprite InitSprite(Rectangle frameRec, Texture2D defaultTexture,
                  int defaultAnimID) {
  static int next_sprite_id;

  Sprite sprite;

  sprite.id = next_sprite_id++;
  sprite.texture = defaultTexture;
  sprite.frameRec = frameRec;
  sprite.animId = defaultAnimID;
  sprite.flipX = false;
  sprite.flipY = false;

  return sprite;
}

Anim InitAnim(Texture2D texture, int startFrame, int endFrame, float speed) {

  static int next_anim_id = 1;

  Anim anim;

  anim.id = next_anim_id++;
  anim.texture = texture;
  anim.startFrame = startFrame;
  anim.endFrame = endFrame;
  anim.speed = speed;
  anim.curFrame = startFrame;
  anim.timeStamp = 0.0f;

  return anim;
}

void PlayAnim(Anim *anim, Sprite *sprite, float dt) {
  // TraceLog(LOG_INFO,
  //          "Anim TExture Width : %d , Anim TExture Height : %d \n "
  //          "curTexture Width : %d , curTexture Height : %d",
  //          anim->texture.width, anim->texture.height, sprite->texture.width,
  //          sprite->texture.height);
  const int sliceX = (int)((float)((float)(anim->texture.width) /
                                   fabsf(sprite->frameRec.width)));
  const int sliceY = (int)((float)((float)(anim->texture.height) /
                                   fabsf(sprite->frameRec.height)));
  // TraceLog(LOG_INFO, "Slice X : %d Slice Y : %d", sliceX, sliceY);
  // TraceLog(LOG_INFO, "Sprite animId : %d , anim id : %d", sprite->animId,
  //          anim->id);
  if (sprite->animId != anim->id) {
    // TraceLog(LOG_INFO, "CurTexture is not AnimTexture, %d %d",
    //          sprite->texture.id, anim->texture.id);
    sprite->texture = anim->texture;
    sprite->animId = anim->id;
    // TraceLog(LOG_INFO, "CurTexture : %d", sprite->texture.id);
    anim->curFrame = anim->startFrame;
    anim->timeStamp = 0.0f;
    sprite->frameRec.x = (float)((int)(anim->startFrame % sliceX));
    sprite->frameRec.y = (float)((int)(anim->startFrame / sliceY));
    // TraceLog(LOG_INFO,
    //          "Current Frame : %d , Timestamp : %f , Rec_X : %f , Rec_Y : %f",
    //          anim->curFrame, anim->timeStamp, sprite->frameRec.x,
    //          sprite->frameRec.y);
  }
  // TraceLog(LOG_INFO, "cur tex is same as the anim!");

  anim->timeStamp += dt;

  const float frameSpeed = (60.0f / anim->speed) * 0.1f;

  // TraceLog(LOG_INFO, "frame_speed : %f , timestamp : %f", frameSpeed,
  //          anim->timeStamp);

  if (anim->timeStamp >= frameSpeed) {
    anim->timeStamp = 0.0f;
    anim->curFrame++;
    // TraceLog(LOG_INFO, "Timestamp : %f , Current Frame : %d",
    // anim->timeStamp,
    //          anim->curFrame);
    if (anim->curFrame > anim->endFrame) {
      anim->curFrame = anim->startFrame;
      // TraceLog(LOG_INFO, "Current Frame : %d", anim->curFrame);
    }
  }

  // TraceLog(LOG_INFO, "Proceed the frameRec_Transition! Cur frame : %d",
  //          anim->curFrame);

  int frameX = (int)((float)(anim->curFrame % sliceX));
  int frameY = (int)((float)(anim->curFrame) / (float)(sliceX));

  // TraceLog(LOG_INFO, "frame_X : %d , frame_Y : %d", frameX, frameY);

  sprite->frameRec.x = (float)(frameX)*fabsf(sprite->frameRec.width);
  sprite->frameRec.y = (float)(frameY)*fabsf(sprite->frameRec.height);

  // TraceLog(LOG_INFO, "frameRec_X : %f , frameRec_Y : %f", sprite->frameRec.x,
  //          sprite->frameRec.y);
}
