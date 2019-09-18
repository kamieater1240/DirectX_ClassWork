#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "effect.h"
#include "bullet.h"
#include "player.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"

EFFECT effects[EFFECT_MAX];
unsigned int effectTexID;
int FrameCounter;

void effectInit() {
	//フラグの初期化(未使用)、テクスチャの準備
	Texture_SetLoadFile("Asset/Texture/effect.jpg", 80, 80);
	Texture_Load();
	effectTexID = Texture_GetID("Asset/Texture/effect.jpg");

	for (int i = 0; i < EFFECT_MAX; i++) {
		effects[i].isUse = false;
		
	}

	FrameCounter = 0;
}

void effectUninit() {

}

void effectUpdate() {
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effects[i].isUse) {
			int age = FrameCounter - effects[i].firstFrame;
			if (age >= effects[i].life) {		//Dead
				effects[i].isUse = false;
				continue;
			}
			else {
				float e = age / (float)effects[i].life;
				D3DXCOLOR color = effects[i].color;
				color.a = 1 - e;
				effects[i].color = color;
				effects[i].scale -= effects[i].minusScale;
			}
		}
	}

	FrameCounter++;
}

void effectDraw() {
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	// レンダーステート(加算合成処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// αデスティネーションカラーの指定(1.0)

	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effects[i].isUse) {
			Sprite_SetColor(effects[i].color);
			Sprite_Draw(effectTexID, effects[i].position.x, effects[i].position.y, effects[i].scale, effects[i].scale, 1.f);
		}
	}

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	// レンダーステート(通常ブレンド処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定(1.0 - SRC)
}

void Effect_Create(float x, float y, D3DCOLOR color, int life, float scale) {
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (!effects[i].isUse) {
			effects[i].isUse = true;
			effects[i].position.x = x;
			effects[i].position.y = y;
			effects[i].color = color;
			effects[i].life = life;
			effects[i].scale = scale;
			effects[i].minusScale = scale / life;
			effects[i].firstFrame = FrameCounter;
			break;
		}
	}
}