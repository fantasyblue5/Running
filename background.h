#pragma once

#include <stdio.h>
#include <Windows.h>
#include <graphics.h>


void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

// ������ y <0 �Լ�y>0���κ����
void putimagePNG2(int x, int y, IMAGE* picture);
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture);

void initBackground();
void updateBg();
void flyBackground();
