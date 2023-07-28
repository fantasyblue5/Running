#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include <vector> //C++���ȿɱ�����
#include "background.h"
#include "hero.h"
#include "obstacle.h"
#include "hit.h"
#include "score.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std; //���������ռ�

#define OBSTACLE_COUNT 10 
#define WIN_SCORE 100

int score; //����
IMAGE imgNumber[10];

extern int heroBlood;
extern int heroX;

extern vector<vector<IMAGE>>obstacleImgs; //IMAGE obstacleImgs[][]�ɱ��ά���飬��������ϰ���ĸ���ͼƬ
extern obstacle_t obstacles[OBSTACLE_COUNT]; //�ϰ����

void initScore()
{
	char nameScore[64];

	//Ԥ������ײ��Ч
	preLoadSound("res/hit.mp3");

	//���ű�������
	mciSendString("play res/bg.mp3", 0, 0, 0);

	//��Ϸ�����ʼ��
	loadimage(0, "res/start1.png");
	system("pause");

	//��Ϸ˵��
	loadimage(0, "res/start2.png");
	system("pause");

	//��������ͼƬ
	for (int i = 0; i < 10; i++) {
		sprintf(nameScore, "res/number/%d.png", i);
		loadimage(&imgNumber[i], nameScore);
	}


}


//����Ѫ��
void updateBloodBar()
{
	drawBloodBar(10, 10, 200, 10, 2, BLUE, DARKGRAY, RED, heroBlood / 100.0);
}

//���ط���
void updateScore()
{
	//������תΪ�ַ���
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

//��Ϸ�����ж�
void checkOver()
{
	if (heroBlood <= 0) {
		loadimage(0, "res/over.png");
		FlushBatchDraw(); //ˢ�´���
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		system("pause");

		//��֮ͣ�������ʼ��һ�֣���ֵ����
		heroBlood = 100;
		score = 0;
		mciSendString("play res/bg.mp3", 0, 0, 0);
	}
}

//ͳ�Ʒ���
void checkScore()
{
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist &&
			obstacles[i].passed == false &&
			obstacles[i].hited == false &&
			obstacles[i].x + obstacleImgs[obstacles[i].type][0].getwidth() < heroX) {
			score += 20;
			obstacles[i].passed = true;
			printf("��ǰ������%d\n", score);
		}
	}
}

//��Ϸʤ���ж�
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





//Ԥ��������
void  preLoadSound(const char* name) {
	char cmd[512];
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
	mciSendString(cmd, 0, 0, 0);
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
	mciSendString(cmd, 0, 0, 0);
}

//��������
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

//����Ѫ��
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
