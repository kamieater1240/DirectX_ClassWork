#pragma once
#ifndef SPRITEANIM_H_
#define SPRITEANIM_H_

#define COCO_WALK_ANIM_PATTERN_MAX	(13)

void SpriteAnim_Init();
void SpriteAnim_Update();
void SpriteAnim_Draw(float dx, float dy);
void SpriteAnim_Draw(const char* fileName, float dx, float dy, int sprite_width, int sprite_height);
void SpriteAnim_Uninit();

#endif // !SPRITEANIM_H_

