#pragma once
#ifndef COLLSION_H_
#define COLLSION_H_

typedef struct Circle_tag{
	D3DXVECTOR2 position;
	float radius;
}Circle;

bool IsHitCollsion_Circle_Circle(const Circle* pA, const Circle* pB);

#endif // !COLLSION_H_
