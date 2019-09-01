#pragma once
#ifndef BULLET_H_
#define BULLET_H_

#define BULLET_MAX 100

#include "collision.h"

enum BULLET_STYLE {
	BULLET_NORMAL = 0,
	BULLET_FIRE,
	BULLET_ICE,
	BULLET_DEADIMMEDIATELY,
};

typedef struct BULLET {
	bool isUse;
	D3DXVECTOR2 position;
	int textureID;
	D3DXVECTOR2 dir;
	BULLET_STYLE style;
	Circle collision;
};

void bulletInit();
void bulletUninit();
void bulletUpdate();
void bulletDraw();
void CreateBullet(float x, float y, D3DXVECTOR2 dir, BULLET_STYLE style);
bool bullet_IsUsed(int index);
void bullet_setUsed(int index, bool set);
Circle* bullet_GetCircleCollision(int index);
BULLET* getBullet();

#endif // !BULLET_H_
