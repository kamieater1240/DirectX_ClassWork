#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "game.h"
#include "main.h"
#include "fade.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemyMaker.h"
#include "score.h"
#include "judgement.h"
#include "explosion.h"
#include "effect.h"
#include "input.h"
#include "mydirect3d.h"
#include "system_timer.h"
#include "debug_font.h"

int g_FrameCount;				//フレームカウンター
int g_FPSBaseFrameCount;		//FPS計測用フレームカウンター
double g_FPSBaseTime;			//FPS計測用時間
float g_FPS;					//FPS

void gameInit() {
	DebugFont_Initialize();
	SystemTimer_Initialize();
	SystemTimer_Start();

	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPSBaseTime = SystemTimer_GetTime();
	g_FPS = 0.0;

	playerInit();
	bulletInit();
	enemyMakerInit();
	enemyInit();
	explosionInit();
	scoreInit();
	fadeInit();
	effectInit();

	LPDIRECT3DDEVICE9 myDevice = MyDirect3D_GetDevice();
	//Texture setting
	myDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//可以控制polygon vertex的alpha值來讓texture變透明
	myDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	myDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);	//可以讓texture只顯示polygon color

	//透明を設定できるセッティング
	myDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	myDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	myDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void gameUninit() {

}

void gameUpdate() {

	g_FrameCount++;
	double time = SystemTimer_GetTime();

	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME) {
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));
		g_FPSBaseTime = time;
		g_FPSBaseFrameCount = g_FrameCount;
	}

	judgementUpdate();
	playerUpdate();
	bulletUpdate();
	enemyMakerUpdate();
	enemyUpdate();
	explosionUpdate();
	fadeUpdate();
	effectUpdate();
}

void gameDraw() {

	playerDraw();
	effectDraw();
	bulletDraw();
	enemyDraw();
	explosionDraw();
	scoreDraw(getScore(), 640, 250, 7, true, 1);
	//fadeDraw();

	DebugFont_Draw(32, 32, "%.2f", g_FPS);
}