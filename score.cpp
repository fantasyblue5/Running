#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include <vector> //C++长度可变数组
#include "background.h"
#include "hero.h"
#include "obstacle.h"
#include "hit.h"
#include "score.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std; //声明命名空间

#define OBSTACLE_COUNT 10 
#define WIN_SCORE 100

int score; //分数
IMAGE imgNumber[10];

extern int heroBlood;
extern int heroX;

extern vector<vector<IMAGE>>obstacleImgs; //IMAGE obstacleImgs[][]可变二维数组，存放所有障碍物的各个图片
extern obstacle_t obstacles[OBSTACLE_COUNT]; //障碍物池

void initScore()
{
	char nameScore[64];

	//预加载碰撞音效
	preLoadSound("res/hit.mp3");

	//播放背景音乐
	mciSendString("play res/bg.mp3", 0, 0, 0);

	//游戏画面初始化
	loadimage(0, "res/start1.png");
	system("pause");

	//游戏说明
	loadimage(0, "res/start2.png");
	system("pause");

	//加载数字图片
	for (int i = 0; i < 10; i++) {
		sprintf(nameScore, "res/number/%d.png", i);
		loadimage(&imgNumber[i], nameScore);
	}


}


//加载血条
void updateBloodBar()
{
	drawBloodBar(10, 10, 200, 10, 2, BLUE, DARKGRAY, RED, heroBlood / 100.0);
}

//加载分数
void updateScore()
{
	//将分数转为字符串
	char str[8];
	sprintf(str, "%d", score);

	int x = 20;
	int y = 25;

	for (int i = 0; str[i]; i++) {
		int number = str[i] - '0';
		putimagePNG2(x, y, &imgNumber[number]);
		x += imgNumber[number].getwidth() + 5;
	}
}

//游戏结束判断
void checkOver()
{
	if (heroBlood <= 0) {
		loadimage(0, "res/over.png");
		FlushBatchDraw(); //刷新窗口
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		system("pause");

		//暂停之后继续开始下一局，数值重置
		heroBlood = 100;
		score = 0;
		mciSendString("play res/bg.mp3", 0, 0, 0);
	}
}

//统计分数
void checkScore()
{
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist &&
			obstacles[i].passed == false &&
			obstacles[i].hited == false &&
			obstacles[i].x + obstacleImgs[obstacles[i].type][0].getwidth() < heroX) {
			score += 20;
			obstacles[i].passed = true;
			printf("当前分数：%d\n", score);
		}
	}
}

//游戏胜利判断
void checkWin()
{
	if (score >= WIN_SCORE) {
		FlushBatchDraw();
		mciSendString("play res/win.mp3", 0, 0, 0);
		Sleep(2000);
		loadimage(0, "res/win.png");
		FlushBatchDraw();
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		system("pause");

		heroBlood = 100;
		score = 0;
		mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	}
}





//预加载音乐
void  preLoadSound(const char* name) {
	char cmd[512];
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
	mciSendString(cmd, 0, 0, 0);
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
	mciSendString(cmd, 0, 0, 0);
}

//播放音乐
void  playSound(const char* name) {
	static int index = 1;
	char cmd[512];

	if (index == 1) {
		sprintf_s(cmd, sizeof(cmd), "play %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
		mciSendString(cmd, 0, 0, 0);
		index++;
	}
	else if (index == 2) {
		sprintf_s(cmd, sizeof(cmd), "play %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
		mciSendString(cmd, 0, 0, 0);
		index = 1;
	}
}

//绘制血条
void drawBloodBar(int x, int y, int width, int height, int lineWidth, int boardColor, int emptyColor, int fillColor, float percent) {
	LINESTYLE lineStyle;
	getlinestyle(&lineStyle);
	int lineColor = getlinecolor();
	int fileColor = getfillcolor();

	if (percent < 0) {
		percent = 0;
	}

	setlinecolor(BLUE);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, lineWidth);
	setfillcolor(emptyColor);
	fillrectangle(x, y, x + width, y + height);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 0);
	setfillcolor(fillColor);
	setlinecolor(fillColor);
	if (percent > 0) {
		fillrectangle(x + 0.5 * lineWidth, y + lineWidth * 0.5, x + width * percent, y + height - 0.5 * lineWidth);
	}

	setlinecolor(lineColor);
	setfillcolor(fillColor);
	setlinestyle(&lineStyle);
}
