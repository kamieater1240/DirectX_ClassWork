#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "fade.h"
#include "player.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"

D3DCOLOR g_FadeColor = 0;
bool     g_bFadeOut = false;	//If is fade in : false, fade out : true
bool     g_bFade = false;		//If is doing fading effect, then true
int      g_FadeFrame = 0;		//Need how many frames to do the frame effect
int      g_FadeFrameCount = 0;
int      g_FadeStartFrame = 0;

void fadeInit() {
	g_bFade = false;
	g_FadeFrameCount = 0;
}

void fadeUpdate() {
	if (g_bFade) {
		int elapsedFrame = g_FadeFrameCount - g_FadeStartFrame;
		float e = (float)elapsedFrame / g_FadeFrame;		//elapsed time

		if (e >= 1.f) {		//Finish fade
			e = 1.f;
			g_bFade = false;
		}

		float alpha = g_bFadeOut ? e : 1.f - e;
		D3DXCOLOR color = g_FadeColor;
		color.a = alpha;
		g_FadeColor = color;
	}
	g_FadeFrameCount++;
}

void fadeDraw() {
	D3DXCOLOR color = g_FadeColor;
	if (color.a <= 0.0001f) {
		return;
	}

	FadeVertex v[] = {
		{D3DXVECTOR4(		  0.f,			 0.f, 0.f, 1.f), g_FadeColor},
		{D3DXVECTOR4(SCREEN_WIDTH,			 0.f, 0.f, 1.f), g_FadeColor},
		{D3DXVECTOR4(		  0.f, SCREEN_HEIGHT, 0.f, 1.f), g_FadeColor},
		{D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 0.f, 1.f), g_FadeColor}
	};

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	pDevice->SetFVF(FVF_FADE_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FadeVertex));
}

void fade_Start(int frame, D3DCOLOR color, bool bOut) {
	g_FadeColor = color;
	g_FadeFrame = frame;
	g_FadeStartFrame = g_FadeFrameCount;
	g_bFadeOut = bOut;
	g_bFade = true;
}

bool fade_isFade() {
	return true;
}