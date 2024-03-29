#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "mydirect3d.h"
#include "texture.h"

static TextureData g_TextureData[TEXTUREDATA_MAX];

void Texture_Init() {
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		g_TextureData[i].filename[0] = '\0';
		g_TextureData[i].pTexture = NULL;
		g_TextureData[i].id = NULL;
	}
}

int Texture_SetLoadFile(const char* pFileName, int width, int height) {
	//既に登録されていないか？検索
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (strcmp(g_TextureData[i].filename, pFileName) == 0) {
			return i;	//存在しているため、管理番号をリターンする
		}
	}

	//データベースの使用されていない部分を検索し、登録する
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (g_TextureData[i].filename[0] != 0) {
			continue;	//使用済なので次を検索
		}
		strcpy(g_TextureData[i].filename, pFileName);
		g_TextureData[i].width = width;
		g_TextureData[i].height = height;
		g_TextureData[i].id = i;
		return i;	//登録した場所（管理番号を戻す）
	}

	return -1;	//登録できるところがなかった
}

int Texture_Load() {
	int error_count = 0, textureNum;
	HRESULT hr_Texture;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (g_TextureData[i].filename[0] == 0)
			continue;
		if (g_TextureData[i].pTexture != NULL)
			continue;

		hr_Texture = D3DXCreateTextureFromFile(pDevice, g_TextureData[i].filename, &g_TextureData[i].pTexture);
		if (FAILED(hr_Texture)) {
			MessageBox(NULL, "Load texture failure", "Failure", MB_OK | MB_ICONINFORMATION);
			error_count++;
		}
	}

	return error_count;
}

void Texture_Release(int ids[], int count) {
	for (int i = 0; i < count; i++) {
		g_TextureData[ids[i]].pTexture->Release();
		g_TextureData[ids[i]].pTexture = NULL;
		g_TextureData[ids[i]].filename[0] = 0;
	}
}

void Texture_Release() {
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (!g_TextureData[i].pTexture)
			continue;

		g_TextureData[i].pTexture->Release();
		g_TextureData[i].pTexture = NULL;
		g_TextureData[i].filename[0] = 0;
	}
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int id) {
	return g_TextureData[id].pTexture;
}

int Texture_GetWidth(int id) {
	return g_TextureData[id].width;
}

int Texture_GetHeight(int id) {
	return g_TextureData[id].height;
}

int Texture_GetID(const char* pFileName) {
	for (int i = 0; i < TEXTUREDATA_MAX; i++) {
		if (!strcmp(g_TextureData[i].filename, pFileName)) {
			return g_TextureData[i].id;
		}
	}
}