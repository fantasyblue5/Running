#pragma once

void  preLoadSound(const char* name);
void  playSound(const char* name);

void drawBloodBar(int x, int y, int width, int height, int lineWidth, int boardColor, int emptyColor, int fillColor, float percent);

void initScore();
void updateBloodBar();
void updateScore();
void checkOver();
void checkScore();
void checkWin();
