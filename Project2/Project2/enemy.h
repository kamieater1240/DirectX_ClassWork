#pragma once
#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_MAX 100

#include "collision.h"

typedef struct ENEMY {
	bool isUse;
	D3DXVECTOR2 position;
	int textureID;
	D3DXVECTOR2 dir;
	Circle g_collision;
};

void enemyInit();
void enemyUninit();
void enemyUpdate();
void enemyDraw();
void CreateEnemy(float x, float y, D3DXVECTOR2 dir);
bool enemy_IsUsed(int index);
void enemy_setUsed(int index, bool set);
Circle* enemy_GetCircleCollision(int index);
ENEMY* getEnemy();

#endif // !ENEMY_H_
