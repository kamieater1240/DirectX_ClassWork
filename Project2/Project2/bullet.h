#pragma once
#ifndef BULLET_H_
#define BULLET_H_

#define BULLET_MAX 100

enum BULLET_STYLE {
	BULLET_NORMAL = 0,
	BULLET_FIRE,
	BULLET_ICE,
	BULLET_DEADIMMEDIATELY,
};

typedef struct BULLET {
	bool isUse;
	float dx, dy;
	int textureID;
	D3DXVECTOR2 dir;
	BULLET_STYLE style;
};

void bulletInit();
void bulletUninit();
void bulletUpdate();
void bulletDraw();
void CreateBullet(float x, float y, D3DXVECTOR2 dir, BULLET_STYLE style);

#endif // !BULLET_H_
