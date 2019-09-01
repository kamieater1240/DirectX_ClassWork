#include "sprite.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "texture.h"
#include "SpriteAnim.h"

int FrameCount = 0;

void SpriteAnim_Init() {

	Texture_SetLoadFile("Asset/Texture/ship.png", 800, 480);
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
	Sprite_Draw(Texture_GetID("Asset/Texture/ship.png"), dx, dy, patternX * 160, patternY * 240, 160, 240);
}

void SpriteAnim_Draw(const char* fileName, float dx, float dy, int sprite_width, int sprite_height) {
	int patternX = FrameCount / 5 % 5;
	int patternY = FrameCount / 5 / 5;
	Sprite_Draw(Texture_GetID(fileName), dx, dy, patternX * sprite_width, patternY * sprite_height, sprite_width, sprite_height);
}

void SpriteAnim_Uninit(){

}