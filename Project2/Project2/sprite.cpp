#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"
#include "main.h"

static D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);

void Sprite_Draw(int textureID, float dx, float dy) {
	int width = Texture_GetWidth(textureID);
	int height = Texture_GetHeight(textureID);

	Vertex2d v[] = {
		{D3DXVECTOR4(dx - width / 2, dy - height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 0.0f)},
		{D3DXVECTOR4(dx + width / 2, dy - height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 0.0f)},
		{D3DXVECTOR4(dx - width / 2, dy + height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 1.0f)},
		{D3DXVECTOR4(dx + width / 2, dy + height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 1.0f)},
	};

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureID));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	pDevice->SetTexture(0, NULL);
}

//No Cut, Rotating + Scaling Method
void Sprite_Draw(int textureID, float dx, float dy, float centerX, float centerY, float angle, float scaleX, float scaleY, float scaleZ) {
	int width = Texture_GetWidth(textureID);
	int height = Texture_GetHeight(textureID);

	Vertex2d v[] = {
		{D3DXVECTOR4(dx - width / 2, dy - height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 0.0f)},
		{D3DXVECTOR4(dx + width / 2, dy - height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 0.0f)},
		{D3DXVECTOR4(dx - width / 2, dy + height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 1.0f)},
		{D3DXVECTOR4(dx + width / 2, dy + height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 1.0f)},
	};

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxR, mtxS, mtxT, mtxIT, mtxW;
	//�ϐ��Ɋ֐����g�p���Ēl��������
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS, scaleX, scaleY, scaleZ);

	//���ڋ�w
	D3DXMatrixTranslation(&mtxT, -centerX, -centerY, 0.0f);
	D3DXMatrixTranslation(&mtxIT, centerX, centerY, 0.0f);

	mtxW = mtxT * mtxR * mtxS * mtxIT;
	//���W�ϊ�����
	//D3DXVec4Transform(&v[0].position, &v[0].position, &mtrxR);
	//					�o��				����
	for (int i = 0; i < 4; i++) {
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureID));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	pDevice->SetTexture(0, NULL);
}

//================================================Cut Method================================================//
void Sprite_Draw(int textureID, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h) {
	int width = Texture_GetWidth(textureID);
	int height = Texture_GetHeight(textureID);
	float u0 = cut_x / (float)width;
	float v0 = cut_y / (float)height;
	float u1 = (cut_x + cut_w) / (float)width;
	float v1 = (cut_y + cut_h) / (float)height;

	Vertex2d v[] = {
		{D3DXVECTOR4(dx - cut_w / 2, dy - cut_h / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + cut_w / 2, dy - cut_h / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx - cut_w / 2, dy + cut_h / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + cut_w / 2, dy + cut_h / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u1, v1)},
	};

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureID));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	pDevice->SetTexture(0, NULL);
}

void Sprite_Draw(int textureID, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float centerX, float centerY, float angle) {
	int width = Texture_GetWidth(textureID);
	int height = Texture_GetHeight(textureID);
	float u0 = cut_x / (float)width;
	float v0 = cut_y / (float)height;
	float u1 = (cut_x + cut_w) / (float)width;
	float v1 = (cut_y + cut_h) / (float)height;

	Vertex2d v[] = {
		{D3DXVECTOR4(dx - width / 2, dy - height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + width / 2, dy - height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx - width / 2, dy + height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + width / 2, dy + height / 2, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u1, v1)},
	};

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxR, mtxT, mtxIT, mtxW;
	//�ϐ��Ɋ֐����g�p���Ēl��������
	D3DXMatrixRotationZ(&mtxR, angle);

	//���ڋ�w
	D3DXMatrixTranslation(&mtxT, -centerX, -centerY, 0.0f);
	D3DXMatrixTranslation(&mtxIT, centerX, centerY, 0.0f);

	//Scale Matrix�֐��@D3DXMatrixScaling(&mtxS, x scale, y scale, z scale); 1.0 -> ����

	mtxW = mtxT * mtxR * mtxIT;
	//���W�ϊ�����
	//D3DXVec4Transform(&v[0].position, &v[0].position, &mtrxR);
	//					�o��				����
	for (int i = 0; i < 4; i++) {
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);
	}

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(textureID));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	pDevice->SetTexture(0, NULL);
}