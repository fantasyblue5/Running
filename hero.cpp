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
int heroX; //玩家的x坐标
int heroY; //玩家的y坐标
int heroIndex; //玩家奔跑的图片序号hero

bool heroJump; //跳跃开关

int jumpHeightMax; //最大跳跃高度
int heroJumpOff; //跳跃偏移量


int update; //是否需要马上刷新画面


bool heroDown; //表示玩家是否处于下蹲状态


void initHero()
{
	char nameHero[64];
	//加载玩家Hero奔跑的图片帧素材
	for (int i = 0; i < 12; ++i) {
		sprintf(nameHero, "res/hero%d.png", i + 1);
		loadimage(&imgHeros[i], nameHero);
	}

	//设置玩家的初始位置																																																																																																											
	heroX = WIN_WIDTH * 0.5 - imgHeros[0].getwidth() * 0.5;
	heroY = 345 - imgHeros[0].getheight();
	heroIndex = 0;

	heroJump = false;
	jumpHeightMax = 345 - imgHeros[0].getheight() - 120;
	heroJumpOff = -4;

	update = true;

	//加载下蹲素材
	loadimage(&imgHeroDown[0], "res/d1.png");
	loadimage(&imgHeroDown[1], "res/d2.png");
	heroDown = false;

	

}

void updateHero()
{
	//人物未下蹲状态
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
	//实现跳跃
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

	//实现下蹲
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

	//在非跳跃状态下人物腿部动作不动
	else {
		heroIndex = (heroIndex + 1) % 12;
	}

}


//玩家按键
void keyEvent()
{
	char ch;
	if (_kbhit()) { //如果有按键按下，Kbhit返回true
		ch = _getch(); //getch()不需要按下回车可直接读取
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
