#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include <vector> //C++���ȿɱ�����
#include "background.h" //����ͼƬ

#define WIN_WIDTH 1012 
#define WIN_HEIGHT 396
#define OBSTACLE_COUNT 10 //�ϰ�������

extern int bgSpeed[3]; //3�ر�����ͬ���ٶ�


using namespace std; //���������ռ�

typedef enum {
	TORTOISE, //�ڹ� 0
	LION, //ʨ�� 1
	HOOK1,
	HOOK2,
	HOOK3,
	HOOK4,
	OBSTACLE_TYPE_COUNT //�ϰ��������
} obstacle_type;

//ÿһ��Ϊͬһ�ϰ������͵Ĳ�ͬͼƬ��ÿһ��Ϊ��ͬ���ϰ�������
vector<vector<IMAGE>>obstacleImgs; //IMAGE obstacleImgs[][]�ɱ��ά���飬��������ϰ���ĸ���ͼƬ

typedef struct obstacle {
	int type; //�ϰ��������
	int imgIndex; //��ǰ��ʾ��ͼƬ�����
	int x, y; //�ϰ��������
	int speed; //�ϰ�����ٶ�
	int power; //��Ѫɱ����

	bool exist; //��ʾ�Ƿ����
	bool hited; //��ʾ�Ƿ��Ѿ�������ײ
	bool passed; //��ʾ�Ƿ�ͨ��
} obstacle_t;

obstacle_t obstacles[OBSTACLE_COUNT]; //�ϰ����
int lastObsIndex; //�ϰ�������


//�����ϰ����ز�
void initObstacle()
{
	char nameObstacle[64];

	//�����ڹ��زģ������ά����
	IMAGE imgTort;
	loadimage(&imgTort, "res/t1.png");
	vector<IMAGE> imgTortArray;
	imgTortArray.push_back(imgTort);
	obstacleImgs.push_back(imgTortArray);

	//����ʨ���زģ������ά����
	IMAGE imgLion;
	vector<IMAGE> imgLionArray;
	for (int i = 0; i < 6; ++i) {
		sprintf(nameObstacle, "res/p%d.png", i + 1);
		loadimage(&imgLion, nameObstacle);
		imgLionArray.push_back(imgLion);
	}
	obstacleImgs.push_back(imgLionArray);

	//��ʼ���ϰ����
	for (int i = 0; i < OBSTACLE_COUNT; ++i) {
		obstacles[i].exist = false;

	}

	//���������زģ������ά����
	IMAGE imgH;

	for (int i = 0; i < 4; ++i) {
		vector<IMAGE> imgHookArray;
		sprintf(nameObstacle, "res/h%d.png", i + 1);
		loadimage(&imgH, nameObstacle, 63, 260, true);
		imgHookArray.push_back(imgH);
		obstacleImgs.push_back(imgHookArray);
	}

	//�ϰ����ų�ʼ��
	lastObsIndex = -1;
}

//�����ϰ���
void createObstacle()
{
	//���ϰ����˳�
	int i;
	for (i = 0; i < OBSTACLE_COUNT; ++i) {
		if (obstacles[i].exist == false) {
			break;
		}
	}
	if (i >= OBSTACLE_COUNT) {
		return;
	}

	//�ϰ������ֵ��ʼ��
	obstacles[i].exist = true;
	obstacles[i].hited = false;
	obstacles[i].imgIndex = 0;
	obstacles[i].type = rand() % 3;
	obstacles[i].x = WIN_WIDTH;
	obstacles[i].y = 345 + 5 - obstacleImgs[obstacles[i].type][0].getheight();

	//���ӵ������������
	if (obstacles[i].type == HOOK1) {
		obstacles[i].type += rand() % 4;
	}

	//�����ϰ�������
	//�����һ�γ��ֵ������ӣ������ܳ��ֵ�ʨ�Ӹ�Ϊ�ڹ�
	if (lastObsIndex >= 0 &&
		obstacles[lastObsIndex].type >= HOOK1 &&
		obstacles[lastObsIndex].type <= HOOK4 &&
		obstacles[i].type == LION &&
		obstacles[lastObsIndex].x > (WIN_WIDTH - 500)) {
		obstacles[i].type = TORTOISE;
	}

	lastObsIndex = i;

	//��ͬ������ϰ������ò�ͬ
	if (obstacles[i].type == TORTOISE) {
		obstacles[i].speed = 0;
		obstacles[i].power = 5;
		obstacles[i].y = 345 + 5 - obstacleImgs[obstacles[i].type][0].getheight();
	}
	else if (obstacles[i].type == LION) {
		obstacles[i].speed = 4;
		obstacles[i].power = 10;
	}
	else if (obstacles[i].type >= HOOK1 && obstacles[i].type <= HOOK4) {
		obstacles[i].speed = 0;
		obstacles[i].power = 10;
		obstacles[i].y = 0;
	}

	obstacles[i].passed = false;
}

//�����ϰ���
void updateEnemy()
{
	//��Ⱦ�ϰ���
	for (int i = 0; i < OBSTACLE_COUNT; ++i) {
		if (obstacles[i].exist) {
			putimagePNG2(obstacles[i].x, obstacles[i].y, WIN_WIDTH, &obstacleImgs[obstacles[i].type][obstacles[i].imgIndex]);
		}
	}
}

//�ϰ����ܶ�
void flyObstacle()
{
	//�����ϰ���
	static int frameCount = 0;
	static int enemyFre = 50;
	frameCount++;

	//���֮֡���ٳ����ϰ���
	if (frameCount > enemyFre) {
		frameCount = 0;
		enemyFre = 50 + rand() % 50; //(50,99)֡��������ϰ���
		createObstacle();
	}

	//�����ϰ�������
	for (int i = 0; i < OBSTACLE_COUNT; ++i) {
		if (obstacles[i].exist) {
			obstacles[i].x -= obstacles[i].speed + bgSpeed[2];
			if (obstacles[i].x < -obstacleImgs[obstacles[i].type][0].getwidth() * 2) {
				obstacles[i].exist = false;
			}

			//�ϰ���ͼƬ����
			int len = obstacleImgs[obstacles[i].type].size(); //�ϰ���һ���м���ͼƬ
			obstacles[i].imgIndex = (obstacles[i].imgIndex + 1) % len;
		}
	}

}

