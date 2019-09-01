#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "enemyMaker.h"
#include "enemy.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"

int EM_FrameCount;				//�t���[���J�E���^�[

void enemyMakerInit() {
	EM_FrameCount = 0;
}

void enemyMakerUninit() {

}

void enemyMakerUpdate() {
	EM_FrameCount++;

	if (EM_FrameCount % 60 == 0) {
		switch ((EM_FrameCount / 60) % 3)
		{
		case 0:		//��
			CreateEnemy(50.0f, 0.0f, { 0.0, 3.0 });
			break;
		case 1:		//�^��
			CreateEnemy(640.0f, 0.0f, { 0.0, 3.0 });
			break;
		case 2:		//�E
			CreateEnemy(1230.0f, 0.0f, { 0.0, 3.0 });
			break;
		default:
			break;
		}
	}
}