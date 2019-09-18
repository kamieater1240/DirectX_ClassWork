#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "score.h"
#include "player.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"

static int scoreTexId;
static int scoreNow;

void scoreInit() {
	Texture_SetLoadFile("Asset/Texture/number.tga", 320, 32);
	Texture_Load();
	scoreTexId = Texture_GetID("Asset/Texture/number.tga");

	scoreNow = 0;
}

void scoreDraw(int score, float x, float y, int digit, bool bZero, bool bLeft) {
	int num;
	for (int i = digit - 1; i >= 0; i--) {
		num = score % 10;
		numberDraw(num, x + i * SCORE_SIZE, y);
		score /= 10;

		if (score == 0 && bZero == false)
			break;
	}
}

void numberDraw(int n, float x, float y) {
	if (n >= 0 && n <= 9) {
		Sprite_Draw(scoreTexId, x, y, n * SCORE_SIZE, 0, SCORE_SIZE, SCORE_SIZE);
	}
}

int getScore() {
	return scoreNow;
}

void addScore(int point) {
	scoreNow += point;
}