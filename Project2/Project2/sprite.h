#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

void Sprite_Init();
void Sprite_Uninit();

//No Cut
void Sprite_Draw(int textureID, float dx, float dy);
void Sprite_Draw(int textureID, float dx, float dy, float scaleX, float scaleY, float scaleZ);
void Sprite_Draw(int textureID, float dx, float dy, float centerX, float centerY, float angle, float scaleX, float scaleY, float scaleZ);


//Cut
void Sprite_Draw(int textureID, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h);
void Sprite_Draw(int textureID, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float centerX, float centerY, float angle);

void Sprite_SetColor(D3DCOLOR color);	

#endif // !SPRITE_H