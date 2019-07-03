#pragma once
#ifndef SPRITEANIM_H_
#define SPRITEANIM_H_

#define COCO_WALK_ANIM_PATTERN_MAX	(13)

void SpriteAnim_Init();
void SpriteAnim_Update();
void SpriteAnim_Draw(float dx, float dy);
void SpriteAnim_Uninit();

#endif // !SPRITEANIM_H_

