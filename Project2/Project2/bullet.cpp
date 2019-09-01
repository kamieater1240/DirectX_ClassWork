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
	//�t���O�̏�����(���g�p)�A�e�N�X�`���̏���
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
	//�t���O���g�p����������A�e�̍��W���X�V�A�e�̏I���`�F�b�N�i���W&�j
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
	//�g�p����������A�e�̊G��`��
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullets[i].isUse) {
			Sprite_Draw(bullets[i].textureID, bullets[i].position.x, bullets[i].position.y);
		}
	}
}

void CreateBullet(float x, float y, D3DXVECTOR2 dir, BULLET_STYLE style) {
	//�g�p����������A�쐬������_���B�e�̍��W��ݒ�
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