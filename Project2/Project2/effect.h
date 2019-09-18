#pragma once
#ifndef EFFECT_H_
#define EFFECT_H_

#define EFFECT_MAX 10000

typedef struct EFFECT {
	bool isUse;
	D3DXVECTOR2 position;
	D3DCOLOR color;
	int life;
	float scale;
	float minusScale;
	int firstFrame;
};

void effectInit();
void effectUninit();
void effectUpdate();
void effectDraw();
void Effect_Create(float x, float y, D3DCOLOR color, int life, float scale);

#endif // !EFFECT_H_
#pragma once
