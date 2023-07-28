#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include "background.h"
#include "hero.h"

#define WIN_WIDTH 1012 
#define WIN_HEIGHT 396

IMAGE imgHeros[12];
IMAGE imgHeroDown[2];
int heroX; //��ҵ�x����
int heroY; //��ҵ�y����
int heroIndex; //��ұ��ܵ�ͼƬ���hero

bool heroJump; //��Ծ����

int jumpHeightMax; //�����Ծ�߶�
int heroJumpOff; //��Ծƫ����


int update; //�Ƿ���Ҫ����ˢ�»���


bool heroDown; //��ʾ����Ƿ����¶�״̬


void initHero()
{
	char nameHero[64];
	//�������Hero���ܵ�ͼƬ֡�ز�
	for (int i = 0; i < 12; ++i) {
		sprintf(nameHero, "res/hero%d.png", i + 1);
		loadimage(&imgHeros[i], nameHero);
	}

	//������ҵĳ�ʼλ��																																																																																																											
	heroX = WIN_WIDTH * 0.5 - imgHeros[0].getwidth() * 0.5;
	heroY = 345 - imgHeros[0].getheight();
	heroIndex = 0;

	heroJump = false;
	jumpHeightMax = 345 - imgHeros[0].getheight() - 120;
	heroJumpOff = -4;

	update = true;

	//�����¶��ز�
	loadimage(&imgHeroDown[0], "res/d1.png");
	loadimage(&imgHeroDown[1], "res/d2.png");
	heroDown = false;

	

}

void updateHero()
{
	//����δ�¶�״̬
	if (heroDown == false) {
		putimagePNG2(heroX, heroY, &imgHeros[heroIndex]);
	}
	else {
		int y = 345 - imgHeroDown[heroIndex].getheight();
		putimagePNG2(heroX, y, &imgHeroDown[heroIndex]);
	}
}

void flyHero()
{
	//ʵ����Ծ
	if (heroJump) {
		if (heroY < jumpHeightMax) {
			heroJumpOff = 4;
		}

		heroY += heroJumpOff;

		if (heroY > 345 - imgHeros[0].getheight()) {
			heroJump = false;
			heroJumpOff = -4;
		}
	}

	//ʵ���¶�
	else if (heroDown) {
		static int count = 0;
		int delays[2] = { 8,35 };
		count++;
		if (count >= delays[heroIndex]) {
			count = 0;
			heroIndex++;
			if (heroIndex >= 2) {
				heroIndex = 0;
				heroDown = false;
			}
		}
	}

	//�ڷ���Ծ״̬�������Ȳ���������
	else {
		heroIndex = (heroIndex + 1) % 12;
	}

}


//��Ұ���
void keyEvent()
{
	char ch;
	if (_kbhit()) { //����а������£�Kbhit����true
		ch = _getch(); //getch()����Ҫ���»س���ֱ�Ӷ�ȡ
		if (ch == ' ') {
			heroJump = true;
			update = true;
		}
		else if (ch == 'a') {
			update = true;
			heroDown = true;
			heroIndex = 0;
		}
	}
}
