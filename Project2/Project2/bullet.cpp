#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "bullet.h"
#include "player.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"

//BULLET bullets[BULLET_MAX];
static D3DXVECTOR2 g_bullet_position;
static float g_bullet_speed;
static bool g_bullet_isUse;
D3DXVECTOR2 g_bullet_dir;
int g_bullet_textureID;

void bulletInit() {
	//フラグの初期化(未使用)、テクスチャの準備
	Texture_SetLoadFile("Asset/Texture/bullet.png", 20, 20);
	Texture_Load();

	g_bullet_isUse = false;
	g_bullet_speed = 2.0f;
	g_bullet_dir = { 0.0f, 0.0f };
	g_bullet_textureID = Texture_GetID("Asset/Texture/bullet.png");
}

void bulletUninit() {

}

void bulletUpdate() {
	//フラグが使用中だったら、弾の座標を更新、弾の終了チェック（座標&）
	if (g_bullet_isUse) {
		if (g_bullet_position.x > SCREEN_WIDTH + 10.0f)
			g_bullet_isUse = false;

		D3DXVec2Normalize(&g_bullet_dir, &g_bullet_dir);
		g_bullet_position += g_bullet_dir * PLAYER_DEFAULT_SPEED;
	}
}

void bulletDraw() {
	//使用中だったら、弾の絵を描く
	if (g_bullet_isUse) {
		Sprite_Draw(g_bullet_textureID, g_bullet_position.x, g_bullet_position.y);
	}
}

void CreateBullet(float x, float y, D3DXVECTOR2 dir, BULLET_STYLE style) {
	//使用中だったら、作成しちゃダメ。弾の座標を設定
	if (!g_bullet_isUse) {
		g_bullet_isUse = true;
		g_bullet_position.x = x;
		g_bullet_position.y = y;
		g_bullet_dir = dir;
	}
}