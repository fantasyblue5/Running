#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <vector> //C++���ȿɱ�����
#include "obstacle.h"
#include "hit.h"
#include "score.h"

#define WIN_WIDTH 1012 
#define WIN_HEIGHT 396
#define OBSTACLE_COUNT 10 

using namespace std; //���������ռ�

extern IMAGE imgHeros[12];
extern int heroX; //��ҵ�x����
extern int heroY; //��ҵ�y����
extern int heroIndex; //��ұ��ܵ�ͼƬ���hero
int heroBlood;

extern IMAGE imgHeroDown[2];

extern bool heroDown; //��ʾ����Ƿ����¶�״̬

extern obstacle_t obstacles[OBSTACLE_COUNT]; //�ϰ����

//ÿһ��Ϊͬһ�ϰ������͵Ĳ�ͬͼƬ��ÿһ��Ϊ��ͬ���ϰ�������
extern vector<vector<IMAGE>>obstacleImgs; //IMAGE obstacleImgs[][]�ɱ��ά���飬��������ϰ���ĸ���ͼƬ


//��ʼ������Ѫ��
void initHit()
{
	heroBlood = 100;

}

//�ж��Ƿ���ײ
void checkHit()
{
	//���������Ƿ��ཻ
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist && obstacles[i].hited == false) {
			int a1x, a1y, a2x, a2y;
			int off = 30;

			//���¶ף����ܻ���Ծ��
			if (!heroDown) {
				a1x = heroX + off;
				a1y = heroY + off;
				a2x = heroX + imgHeros[heroIndex].getwidth() - off;
				a2y = heroY + imgHeros[heroIndex].getheight();
			}
			else {
				a1x = heroX + off;
				a1y = 345 - imgHeroDown[heroIndex].getheight();
				a2x = heroX + imgHeroDown[heroIndex].getwidth() - off;
				a2y = 345;
			}

			//�ϰ����4������
			int b1x = obstacles[i].x + off;
			int b1y = obstacles[i].y + off;
			int b2x = obstacles[i].x + obstacleImgs[obstacles[i].type][obstacles[i].imgIndex].getwidth() - 10;
			int b2y = obstacles[i].y + obstacleImgs[obstacles[i].type][obstacles[i].imgIndex].getheight() - 10;

			//��ײ��Ѫ
			if (rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y)) {
				heroBlood -= obstacles[i].power;
				printf("Ѫ��ʣ��%d\n", heroBlood);
				playSound("res/hit.mp3");
				obstacles[i].hited = true;
			}
		}
	}
}





//��A[x01,y01,x02,y02]  B[x11,y11,x12,y12].
//�ж��Ƿ��ཻ
bool rectIntersect(int x01, int y01, int x02, int y02,
    int x11, int y11, int x12, int y12)
{
    int zx = abs(x01 + x02 - x11 - x12);
    int x = abs(x01 - x02) + abs(x11 - x12);
    int zy = abs(y01 + y02 - y11 - y12);
    int y = abs(y01 - y02) + abs(y11 - y12);
    return  (zx <= x && zy <= y);
}
