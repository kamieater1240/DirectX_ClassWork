#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "collision.h"
#include "enemy.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"

bool IsHitCollsion_Circle_Circle(const Circle* pA, const Circle* pB) {
	
	return D3DXVec2LengthSq(&(pB->position - pA->position)) < (pA->radius+pB->radius)*(pA->radius + pB->radius);
}