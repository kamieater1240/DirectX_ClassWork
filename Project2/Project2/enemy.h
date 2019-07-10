#pragma once
#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_MAX 100

typedef struct ENEMY {
	bool isUse;
	float dx, dy;
	int textureID;
	D3DXVECTOR2 dir;
};

void enemyInit();
void enemyUninit();
void enemyUpdate();
void enemyDraw();
void CreateEnemy(float x, float y, D3DXVECTOR2 dir);

#endif // !ENEMY_H_
