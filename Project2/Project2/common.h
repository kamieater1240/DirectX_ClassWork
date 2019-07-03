#pragma once

static bool Init(HWND hWnd);
static void Uninit(void);
static void Update(void);
static void Draw(void);
void spinTheTriangle(float pivotX, float pivotY, float spinAngle);
void floatWithTide();
void fillCircle();
void fillStar(float pivotX, float pivotY);
void drawST();
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);