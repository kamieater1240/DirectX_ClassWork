#include "sprite.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "texture.h"
#include "SpriteAnim.h"

int FrameCount = 0;

void SpriteAnim_Init() {

	Texture_SetLoadFile("Asset/Texture/runningman100_flip.png", 700, 400);
	Texture_Load();
}

void SpriteAnim_Update() {
	FrameCount++;
}

void SpriteAnim_Draw(float dx, float dy) {
	//cut_x = pattern % 5 * 140		140x200
	//cut_y = pattern / 5 * 200

	int patternX = 4 - (FrameCount / 5 % 5);
	int patternY = 4 - (FrameCount / 5 / 5);
	Sprite_Draw(3, dx, dy, patternX * 140, patternY * 200, 140, 200);
}

void SpriteAnim_Uninit(){

}