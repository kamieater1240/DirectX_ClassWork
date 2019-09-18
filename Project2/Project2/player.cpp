#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "player.h"
#include "main.h"
#include "bullet.h"
#include "effect.h"
#include "sprite.h"
#include "SpriteAnim.h"
#include "texture.h"
#include "mydirect3d.h"
#include "sound.h"
#include "input.h"

Vertex2d v3[] = {
	{D3DXVECTOR4(100.0f, 100.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.4f, 0.0f)},
	{D3DXVECTOR4(234.0f, 100.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.6f, 0.0f)},
	{D3DXVECTOR4(100.0f, 196.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.4f, 1.0f)},
	{D3DXVECTOR4(234.0f, 196.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.6f, 1.0f)}
};

//Texture IDs
int Texture_IDs[100];
int textureNum;

//player parameter
static D3DXVECTOR2 g_player_position;
static float g_player_speed;
static int g_player_textureID;
static int g_player_shootingCD;

void playerInit() {
	
	Texture_SetLoadFile("Asset/Texture/player1.png", 256, 256);
	Texture_Load();

	g_player_position = D3DXVECTOR2(SCREEN_WIDTH*0.5f, SCREEN_HEIGHT - PLAYER_HEIGHT);
	g_player_speed = PLAYER_DEFAULT_SPEED;
	g_player_textureID = Texture_GetID("Asset/Texture/player1.png");
	g_player_shootingCD = 0;
}

void playerUninit() {

}

void playerUpdate() {
	D3DXVECTOR2 dir(0.0f, 0.0f);

	if (Keyboard_IsPress(DIK_W)) {		//Move Up
		//moveY -= moveSpeed;
		dir.y -= 1.0f;
	}
	if (Keyboard_IsPress(DIK_A)) {		//Move Left
		//moveX -= moveSpeed;
		dir.x -= 1.0f;
	}
	if (Keyboard_IsPress(DIK_S)) {		//Move Down
		//moveY += moveSpeed;
		dir.y += 1.0f;
	}
	if (Keyboard_IsPress(DIK_D)) {		//Move Right
		//moveX += moveSpeed;
		dir.x += 1.0f;
	}
	if (Keyboard_IsPress(DIK_B)) {		//Fire Bullet
		if (g_player_shootingCD == 0) {
			CreateBullet(g_player_position.x + 40.0f, g_player_position.y, { 2.0, 0.0 }, BULLET_NORMAL);
			g_player_shootingCD = 30;
			PlaySound(SOUND_LABEL_SE_SHOT);
		}
	}

	//エフェクト生成, create only when player moves
	if (dir.x != 0.0f || dir.y != 0.0f) {
		Effect_Create(g_player_position.x, g_player_position.y, D3DCOLOR_RGBA(255, 60, 60, 255), 120, 0.5f);
	}

	//位置更新
	D3DXVec2Normalize(&dir, &dir);
	g_player_position += dir * PLAYER_DEFAULT_SPEED; //プレイヤー座標 = プレイヤー座標 + 方向ベクトルX速度(単位ベクトル)
	
	if (g_player_shootingCD != 0) {
		--g_player_shootingCD;
	}
}

void playerDraw() {

	//DrawPrimitiveUPの引数　=>　図形の描くタイプ　　数　　頂点データ先頭アドレス　　頂点1個分のサイズ

	//Sprite_Draw(0, 256, 256);
	//Sprite_Draw(g_player_textureID, g_player_position.x, g_player_position.y/*, g_player_position.x, g_player_position.y, angleNow, scaleX, scaleY, 1.0f*/);
	Sprite_Draw(g_player_textureID, g_player_position.x, g_player_position.y, 0, 0, 50, 50);
	//Sprite_Draw(2, 768, 256, 0, 0, 64, 64, 768, 256, angle);
	//Sprite_Draw(0, 256, 512, 100, 100, 100, 100);

	//SpriteAnim_Draw(900, 500);

	//--------------------圖片放大縮小時Sampler用法--------------------//
	/*g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(200, 150, 200, 255));*/

	/*g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetTexture(0, g_pTexture);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v4, sizeof(Vertex2d));
	g_pDevice->SetTexture(0, NULL);*/

	//Sampling state ANISOTROPY
	/*g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);*/
	//---------------------------------------------------------------//

	//↑↑↑ 要注意是用什麼畫圖方式!!不同方式頂點的安排順序也不一樣!!!
}
