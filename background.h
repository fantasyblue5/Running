#pragma once

#include <stdio.h>
#include <Windows.h>
#include <graphics.h>


void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

// 适用于 y <0 以及y>0的任何情况
void putimagePNG2(int x, int y, IMAGE* picture);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);

void initBackground();
void updateBg();
void flyBackground();
