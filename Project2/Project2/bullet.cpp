#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "bullet.h"
#include "player.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"

BULLET bullets[BULLET_MAX];

void bulletInit() {
	//フラグの初期化(未使用)、テクスチャの準備
	Texture_SetLoadFile("Asset/Texture/bullet.png", 20, 20);
	Texture_Load();

	for (int i = 0; i < BULLET_MAX; i++) {
		bullets[i].isUse = false;
		bullets[i].textureID = Texture_GetID("Asset/Texture/bullet.png");
	}
}

void bulletUninit() {

}

void bulletUpdate() {
	//フラグが使用中だったら、弾の座標を更新、弾の終了チェック（座標&）
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullets[i].isUse) {
			if (bullets[i].position.x > SCREEN_WIDTH + 10.0f)
				bullets[i].isUse = false;

			D3DXVec2Normalize(&bullets[i].dir, &bullets[i].dir);
			bullets[i].position += bullets[i].dir * 10.0f;
			bullets[i].collision.position = bullets[i].position;
		}
	}
}

void bulletDraw() {
	//使用中だったら、弾の絵を描く
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullets[i].isUse) {
			Sprite_Draw(bullets[i].textureID, bullets[i].position.x, bullets[i].position.y);
		}
	}
}

void CreateBullet(float x, float y, D3DXVECTOR2 dir, BULLET_STYLE style) {
	//使用中だったら、作成しちゃダメ。弾の座標を設定
	for (int i = 0; i < BULLET_MAX; i++) {
		if (!bullets[i].isUse) {
			bullets[i].isUse = true;
			bullets[i].position.x = x;
			bullets[i].position.y = y;
			bullets[i].dir = dir;
			bullets[i].collision.position = bullets[i].position;
			bullets[i].collision.radius = 10.0f;
			break;
		}
	}
}

bool bullet_IsUsed(int index) {
	return bullets[index].isUse;
}

void bullet_setUsed(int index, bool set) {
	bullets[index].isUse = set;
}

Circle* bullet_GetCircleCollision(int index) {
	return &bullets[index].collision;
}

BULLET* getBullet() {
	return bullets;
}