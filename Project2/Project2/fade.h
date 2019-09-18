#ifndef FADE_H_
#define FADE_H_

typedef struct FadeVertex_tag {
	D3DXVECTOR4 position;
	D3DCOLOR	color;
}FadeVertex;

void fadeInit();
void fadeUpdate();
void fadeDraw();
void fade_Start(int frame, D3DCOLOR color, bool bOut);
bool fade_isFade();

#endif // !FADE_H_

