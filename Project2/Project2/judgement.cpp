#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "judgement.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"

void judgementInit() {

}

void judgementUninit() {

}

void judgementUpdate() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		for (int j = 0; j < BULLET_MAX; j++) {
			if (enemy_IsUsed(i) && bullet_IsUsed(j)) {
				if (IsHitCollsion_Circle_Circle(enemy_GetCircleCollision(i), bullet_GetCircleCollision(j))) {
					enemy_setUsed(i, false);
					bullet_setUsed(j, false);
					ENEMY* enemy = getEnemy();
					CreateExplosion((enemy + j)->position.x, (enemy + j)->position.y + 50.0f);
				}
			}
		}
	}
}