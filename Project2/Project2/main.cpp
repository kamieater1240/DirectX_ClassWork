//#pragma comment(lib, "d3d9.lib")
//#if defined(DEBUG) || defined(_DEBUG)
//#pragma comment(lib, "d3dx9d.lib")
//#else
//#pragma comment(lib, "d3dx9.lib")
//#endif

//===============================//
//         Main Program          //
//===============================//
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "main.h"
#include "common.h"
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "SpriteAnim.h"
#include "system_timer.h"
#include "debug_font.h"
#include "input.h"

#define CLASS_NAME		"GameWindow"
#define WINDOW_CAPTION	"ポリゴン描画"

int g_FrameCount = 0;				//フレームカウンター
int g_FPSBaseFrameCount = 0;		//FPS計測用フレームカウンター
double g_FPSBaseTime = 0.0;			//FPS計測用時間
float g_FPS = 0.0;					//FPS
double g_StaticFrameTime = 0.0;

LPDIRECT3DDEVICE9 myDevice;

//ポリゴンの頂点データを作る
Vertex2d v[] = {
	{D3DXVECTOR4(0.0f,   0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR4(512.0f,   0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR4(0.0f, 512.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR4(512.0f, 512.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f)}
};

Vertex2d v3[] = {
	{D3DXVECTOR4(100.0f, 500.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR4(300.0f, 500.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR4(100.0f, 700.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR4(300.0f, 700.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f)}
};

Vertex2d v4[] = {
	{D3DXVECTOR4(599.5f, 99.5f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR4(1199.5f, 99.5f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.0f)},
	{D3DXVECTOR4(599.5f, 699.5f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.25f)},
	{D3DXVECTOR4(1199.5f, 699.5f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)}
};

Vertex2d v2[SCREEN_WIDTH];
float trying = 0.0f;

//Circle's parameter
static const int CIRCLE_RESOLUTION = 64;
Vertex2d circle[CIRCLE_RESOLUTION + 1];

//Star's parameter
Vertex2d star[12];

//Texture IDs
int Texture_IDs[100];
int textureNum;

int alpha;
float angle = 0.0f;

float nowX = 512.0f, nowY = 256.0f;
float moveX = 0.0f, moveY = 0.0f;
float moveSpeed = 14.0f;
float angleNow = 0.0f;
float moveAngle = 0.0f;
float scaleX = 1.0f, scaleY = 1.0f;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//オリジナルウインドウ
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;	//ウインドウプロシージャコールバック関数の登録
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Cursorのタイプが変えられる
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); //背景の色

	RegisterClass(&wc);			//オリジナルウインドウは自分でクラスをシステムに登録(RegisterClass)する必要がある

	//CreateWindowに指定する幅、高さは、スクリーンサイズに他の部分をたした長さで指定する
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	//左 上 右下
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;
	int window_style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);
	AdjustWindowRect(&window_rect, window_style, FALSE);

	//Windowを真ん中に置く
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);
	int window_x = max((desktop_width - window_width) / 2, 0);
	int window_y = max((desktop_height - window_height) / 2, 0);

	HWND hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,
		window_x,												//最初のX座標
		window_y,												//最初のY座標
		window_width,											//Width
		window_height,											//Height
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	Init(hWnd);
	Keyboard_Initialize(hInstance, hWnd);	//Input Initialize

	//メッセージループ-->メッセージを受け取るまで、プログラムをブロックする
	//如果hWnd为NULL，则GetMessage接收属于调用线程的窗口的消息，线程消息由函数PostThreadMessage寄送给调用线程。
	//GetMessage不接收属于其他线程或其他线程的窗口的消息，即使hWnd为NULL。由PostThreadMessage寄送的线程消息，其消息hWnd值为NULL。
	//如果wMsgFilterMin和wMsgFilterMax都为零，GetMessage返回所有可得的消息（即，无范围过滤）。
	//lpMsg：指向MSG结构的指针，该结构从线程的消息队列里接收消息信息。
	//wMsgFilterMin：指定被检索的最小消息值的整数。
	//wMsgFilterMax：指定被检索的最大消息值的整数。
	MSG msg = {};
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//ゲーム処理
			double time = SystemTimer_GetTime();

			if (time - g_StaticFrameTime < 1.0 / 60.0) {
				Sleep(0);
			}
			else {
				g_StaticFrameTime = time;
				Update();
				Draw();
			}
		}
	}
	Uninit();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool Init(HWND hWnd) {

	MyDirect3D_Init(hWnd);
	myDevice = MyDirect3D_GetDevice();

	DebugFont_Initialize();
	SystemTimer_Initialize();
	SystemTimer_Start();
	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPSBaseTime = SystemTimer_GetTime();
	g_FPS = 0.0;

	textureNum = 0;
	Texture_IDs[textureNum++] = Texture_SetLoadFile("Asset/Texture/kobeni.jpg", 256, 256);
	Texture_IDs[textureNum++] = Texture_SetLoadFile("Asset/Texture/leoreiya.png", 256, 256);
	Texture_IDs[textureNum++] = Texture_SetLoadFile("Asset/Texture/spice_and_wolf.jpg", 256, 256);
	SpriteAnim_Init();
	Texture_Load();

	alpha = 255;

	return true;
}

void Uninit(void) {
	if (myDevice != NULL) {
		myDevice->Release();
	}
}

void Update(void) {
	drawST();
	alpha--;
	if (alpha < 0)
		alpha = 255;

	angle += 0.02f;

	g_FrameCount++;
	double time = SystemTimer_GetTime();

	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME) {
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));
		g_FPSBaseTime = time;
		g_FPSBaseFrameCount = g_FrameCount;
	}

	SpriteAnim_Update();
	Keyboard_Update();

}

void Draw(void) {
	//画面のクリア,           　　　　 クリアしたいターゲット　　　　　　　　　　色　　　　　　　　　　　　　Z　　ステンシル
	myDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(152, 251, 152, 255), 1.0f, 0);

	//ポリゴン描画 1.頂点構造体を作ります　2.デバイスに頂点の形を伝えるためのFVFを宣言する
	//3.頂点データを作る　
	//4.ポリゴン描画命令, ※BeginScene~EndScene間に書く
	myDevice->BeginScene();	//BeginScene後一定要接EndScene
	myDevice->SetFVF(FVF_VERTEX2D);

	//DrawPrimitiveUPの引数　=>　図形の描くタイプ　　数　　頂点データ先頭アドレス　　頂点1個分のサイズ

	//Sprite_Draw(0, 256, 256);
	Sprite_Draw(1, nowX, nowY, nowX, nowY, angleNow, scaleX, scaleY, 1.0f);
	//Sprite_Draw(2, 768, 256, 0, 0, 64, 64, 768, 256, angle);
	//Sprite_Draw(0, 256, 512, 100, 100, 100, 100);

	if (Keyboard_IsPress(DIK_W)) {		//Move Up
		moveY -= moveSpeed;
	}
	if (Keyboard_IsPress(DIK_A)) {		//Move Left
		//nowX--;
		moveX -= moveSpeed;
	}
	if (Keyboard_IsPress(DIK_S)) {		//Move Down
		moveY += moveSpeed;
	}
	if (Keyboard_IsPress(DIK_D)) {		//Move Right
		//nowX++;
		moveX += moveSpeed;
	}
	if (Keyboard_IsPress(DIK_Q)) {		//Rotate Left
		//angleNow -= 0.02f;
		moveAngle -= 2.0f;
	}
	if (Keyboard_IsPress(DIK_E)) {		//Rotate Right
		//angleNow += 0.02f;
		moveAngle += 2.0f;
	}
	if (Keyboard_IsPress(DIK_Z)) {		//Scale Up
		scaleX += 0.01f;
		scaleY += 0.01f;
	}
	if (Keyboard_IsPress(DIK_C)) {		//Scale Down
		scaleX -= 0.01f;
		scaleY -= 0.01f;
	}

	//摩擦力
	moveX *= 0.95f;
	moveY *= 0.95f;
	moveAngle *= 0.95f;

	//位置更新
	nowX += moveX;
	nowY += moveY;
	angleNow += moveAngle;

	/*myDevice->SetTexture(0, g_pTexture);
	myDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	myDevice->SetTexture(0, NULL);

	myDevice->SetTexture(0, g_pTexture2);
	myDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v4, sizeof(Vertex2d));
	myDevice->SetTexture(0, NULL);*/

	//Texture setting
	myDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//可以控制polygon vertex的alpha值來讓texture變透明
	myDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	myDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);	//可以讓texture只顯示polygon color

	//透明を設定できるセッティング
	myDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	myDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	myDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (int i = 0; i < 4; i++) {
		v3[i].color = D3DCOLOR_RGBA(255, 255, 255, alpha);
	}

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

	DebugFont_Draw(32, 32, "%.2f", g_FPS);

	myDevice->EndScene();		//在Call下一個BeginScene之前一定要接EndScene
	myDevice->Present(NULL, NULL, NULL, NULL);

}

void spinTheTriangle(float pivotX, float pivotY, float spinAngle) {
	Vertex2d tmp;

	//計算後的位置
	for (int i = 0; i < 3; i++) {
		//平移到原點
		v[i].position.x = v[i].position.x - pivotX;
		v[i].position.y = v[i].position.y - pivotY;

		//計算後的位置
		tmp.position.x = v[i].position.x * cos(spinAngle) - v[i].position.y * sin(spinAngle);
		tmp.position.y = v[i].position.x * sin(spinAngle) + v[i].position.y * cos(spinAngle);
		tmp.color = v[i].color;
		v[i] = tmp;

		//平移回原本的軸心
		v[i].position.x = v[i].position.x + pivotX;
		v[i].position.y = v[i].position.y + pivotY;
	}
}

void floatWithTide() {

	for (int i = 0; i < 3; i++) {
		float a = sinf(0.01f*i - trying) * 100;
		float b = sinf(0.01f*i * 2 * 30 - trying) * 20;
		v[i].position = D3DXVECTOR4(v[i].position.x, b + v[i].position.y, 0.0f, 1.0f);
	}
}

void fillCircle() {
	static int alpha = 255;

	for (int i = 0; i < CIRCLE_RESOLUTION + 1; i++) {
		circle[i].position.x = 100.0f + 100.0f * cos(D3DX_PI*(i / (CIRCLE_RESOLUTION / 2.0f)));
		circle[i].position.y = 100.0f + 100.0f * sin(D3DX_PI*(i / (CIRCLE_RESOLUTION / 2.0f)));
		circle[i].position.z = 0.0f;
		circle[i].position.w = 1.0f;
		circle[i].color = D3DCOLOR_RGBA(255, 255, 0, alpha);
		circle[i].uv = D3DXVECTOR2(0.0f, 0.0f);
	}

	alpha--;
}

void fillStar(float pivotX, float pivotY) {
	Vertex2d tmp;

	star[0] = { D3DXVECTOR4(0.0f + pivotX, -tan(D3DX_PI * 3.0f / 10.0f) * 10.0f + pivotY, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255) };

	for (int i = 1; i < 12; i++) {
		if (i == 1) {
			star[i].position.x = 0.0f + pivotX;
			star[i].position.y = tan(D3DX_PI / 3.0f) * 10.0f + pivotY;

		}
		else if (i == 2) {
			star[i].position.x = -1.0f * 10.0f + pivotX;
			star[i].position.y = 0.0f + pivotY;
		}
		else {
			//平移到原點
			tmp.position.x = star[i - 2].position.x - star[0].position.x;
			tmp.position.y = star[i - 2].position.y - star[0].position.y;

			//計算後的位置
			star[i].position.x = tmp.position.x * cos(D3DX_PI * 2.0f / 5.0f) - tmp.position.y * sin(D3DX_PI * 2.0f / 5.0f);
			star[i].position.y = tmp.position.x * sin(D3DX_PI * 2.0f / 5.0f) + tmp.position.y * cos(D3DX_PI * 2.0f / 5.0f);

			//平移回原本的軸心
			star[i].position.x = star[i].position.x + star[0].position.x;
			star[i].position.y = star[i].position.y + star[0].position.y;
		}

		star[i].position.z = 0.0f;
		star[i].position.w = 1.0f;
		star[i].color = D3DCOLOR_RGBA(255, 255, 0, 255);
		star[i].uv = D3DXVECTOR2(0.0f, 0.0f);
	}
}

void drawST() {
	trying += 0.5f;

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		float a = sinf(0.01f*i) * 100;
		float b = sinf(0.01f*i * 30 - trying) * 20;
		float c = cosf(0.01f*i * 30) * 20;
		//sinf(0.15f*i-trying)*20 <== -trying可以讓波移動

		v2[i].position = D3DXVECTOR4(i, a + b + SCREEN_HEIGHT * 0.5f/* + rand() % 10*/, 0.0f, 1.0f);
		v2[i].color = D3DCOLOR_RGBA(i * 255 / SCREEN_WIDTH, 0, 0, 255);
	}

}