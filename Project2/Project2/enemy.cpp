#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "enemy.h"
#include "player.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"

ENEMY enemies[ENEMY_MAX];

static D3DXVECTOR2 g_enemy_position;
static float g_enemy_speed;
static bool g_enemy_isUse;
D3DXVECTOR2 g_enemy_dir;
int g_enemy_textureID;

void enemyInit() {
	//フラグの初期化(未使用)、テクスチャの準備
	Texture_SetLoadFile("Asset/Texture/enemy.png", 256, 256);
	Texture_Load();

	/*g_enemy_isUse = false;
	g_enemy_speed = 2.0f;
	g_enemy_dir = { 0.0f, 0.0f };*/
	g_enemy_textureID = Texture_GetID("Asset/Texture/enemy.png");

	for (int i = 0; i < ENEMY_MAX; i++) {
		enemies[i].isUse = false;
		enemies[i].textureID = g_enemy_textureID;
	}
}

void enemyUninit() {

}

void enemyUpdate() {
	
	/*if (g_enemy_isUse) {
		D3DXVec2Normalize(&g_enemy_dir, &g_enemy_dir);
		g_enemy_position += g_enemy_dir * PLAYER_DEFAULT_SPEED;
	}*/
}

void enemyDraw() {
	
	/*if (g_enemy_isUse) {
		Sprite_Draw(g_enemy_textureID, g_enemy_position.x, g_enemy_position.y);
	}*/
}

void CreateEnemy(float x, float y, D3DXVECTOR2 dir) {

}