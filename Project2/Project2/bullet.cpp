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
	//�t���O�̏�����(���g�p)�A�e�N�X�`���̏���
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
	//�t���O���g�p����������A�e�̍��W���X�V�A�e�̏I���`�F�b�N�i���W&�j
	if (g_bullet_isUse) {
		if (g_bullet_position.x > SCREEN_WIDTH + 10.0f)
			g_bullet_isUse = false;

		D3DXVec2Normalize(&g_bullet_dir, &g_bullet_dir);
		g_bullet_position += g_bullet_dir * PLAYER_DEFAULT_SPEED;
	}
}

void bulletDraw() {
	//�g�p����������A�e�̊G��`��
	if (g_bullet_isUse) {
		Sprite_Draw(g_bullet_textureID, g_bullet_position.x, g_bullet_position.y);
	}
}

void CreateBullet(float x, float y, D3DXVECTOR2 dir, BULLET_STYLE style) {
	//�g�p����������A�쐬������_���B�e�̍��W��ݒ�
	if (!g_bullet_isUse) {
		g_bullet_isUse = true;
		g_bullet_position.x = x;
		g_bullet_position.y = y;
		g_bullet_dir = dir;
	}
}