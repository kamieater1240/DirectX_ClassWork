#ifndef SCORE_H_
#define SCORE_H_

#define SCORE_SIZE 32

void scoreInit();
void scoreDraw(int score, float x, float y, int digit, bool bZero, bool bLeft);
static void numberDraw(int n, float x, float y);
int getScore();
void addScore(int point);

#endif // !SCORE_H_

