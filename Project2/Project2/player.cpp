#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "player.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"
#include "input.h"
#include "bullet.h"

Vertex2d v3[] = {
	{D3DXVECTOR4(100.0f, 500.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR4(300.0f, 500.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR4(100.0f, 700.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR4(300.0f, 700.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f)}
};

//Texture IDs
int Texture_IDs[100];
int textureNum;

//player parameter
static D3DXVECTOR2 g_player_position;
static float g_player_speed;
static int g_player_textureID;
//float nowX = 512.0f, nowY = 256.0f;
//float moveX = 0.0f, moveY = 0.0f;
//float moveSpeed = 5.0f;
//float angleNow = 0.0f;
//float moveAngle = 0.0f;
//float moveAngleSpeed = 0.05f;
//float scaleX = 1.0f, scaleY = 1.0f;
//int alpha = 255;
//float angle = 0.0f;

void playerInit() {
	
	Texture_SetLoadFile("Asset/Texture/player.png", 256, 256);
	Texture_Load();

	g_player_position = D3DXVECTOR2(SCREEN_WIDTH*0.5f, SCREEN_HEIGHT - PLAYER_HEIGHT);
	g_player_speed = PLAYER_DEFAULT_SPEED;
	g_player_textureID = Texture_GetID("Asset/Texture/player.png");

	//LPDIRECT3DDEVICE9 myDevice = MyDirect3D_GetDevice();
	////Texture setting
	//myDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//可以控制polygon vertex的alpha值來讓texture變透明
	//myDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//myDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	////g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);	//可以讓texture只顯示polygon color

	////透明を設定できるセッティング
	//myDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//myDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//myDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
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
		//moveX += moveSpeed;
		CreateBullet(g_player_position.x + 40.0f, g_player_position.y, {2.0, 0.0}, BULLET_NORMAL);
	}

	//if (Keyboard_IsPress(DIK_Q)) {		//Rotate Left
	//	moveAngle -= moveAngleSpeed;
	//}
	//if (Keyboard_IsPress(DIK_E)) {		//Rotate Right
	//	moveAngle += moveAngleSpeed;
	//}
	//if (Keyboard_IsPress(DIK_Z)) {		//Scale Up
	//	scaleX += 0.01f;
	//	scaleY += 0.01f;
	//}
	//if (Keyboard_IsPress(DIK_C)) {		//Scale Down
	//	scaleX -= 0.01f;
	//	scaleY -= 0.01f;
	//}

	////摩擦力
	//moveX *= 0.95f;
	//moveY *= 0.95f;
	//moveAngle *= 0.95f;

	//位置更新
	D3DXVec2Normalize(&dir, &dir);
	g_player_position += dir * PLAYER_DEFAULT_SPEED; //プレイヤー座標 = プレイヤー座標 + 方向ベクトルX速度(単位ベクトル)
	//angleNow += moveAngle;

	////境界判定
	//nowX = max(nowX, Texture_GetWidth(1) / 2);
	//nowX = min(nowX, SCREEN_WIDTH - Texture_GetWidth(1) / 2);
	//nowY = max(nowY, Texture_GetHeight(1) / 2);
	//nowY = min(nowY, SCREEN_HEIGHT + 100 - Texture_GetHeight(1) / 2);
}

void playerDraw() {

	//DrawPrimitiveUPの引数　=>　図形の描くタイプ　　数　　頂点データ先頭アドレス　　頂点1個分のサイズ

	//Sprite_Draw(0, 256, 256);
	Sprite_Draw(g_player_textureID, g_player_position.x, g_player_position.y/*, g_player_position.x, g_player_position.y, angleNow, scaleX, scaleY, 1.0f*/);
	//Sprite_Draw(2, 768, 256, 0, 0, 64, 64, 768, 256, angle);
	//Sprite_Draw(0, 256, 512, 100, 100, 100, 100);

	/*myDevice->SetTexture(0, g_pTexture);
	myDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	myDevice->SetTexture(0, NULL);

	myDevice->SetTexture(0, g_pTexture2);
	myDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v4, sizeof(Vertex2d));
	myDevice->SetTexture(0, NULL);*/

	/*myDevice->SetTexture(0, g_pTexture1);
	myDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v3, sizeof(Vertex2d));
	myDevice->SetTexture(0, NULL);*/

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
