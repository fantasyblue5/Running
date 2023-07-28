#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <vector> //C++长度可变数组
#include "obstacle.h"
#include "hit.h"
#include "score.h"

#define WIN_WIDTH 1012 
#define WIN_HEIGHT 396
#define OBSTACLE_COUNT 10 

using namespace std; //声明命名空间

extern IMAGE imgHeros[12];
extern int heroX; //玩家的x坐标
extern int heroY; //玩家的y坐标
extern int heroIndex; //玩家奔跑的图片序号hero
int heroBlood;

extern IMAGE imgHeroDown[2];

extern bool heroDown; //表示玩家是否处于下蹲状态

extern obstacle_t obstacles[OBSTACLE_COUNT]; //障碍物池

//每一行为同一障碍物类型的不同图片，每一列为不同的障碍物类型
extern vector<vector<IMAGE>>obstacleImgs; //IMAGE obstacleImgs[][]可变二维数组，存放所有障碍物的各个图片


//初始化人物血量
void initHit()
{
	heroBlood = 100;

}

//判断是否碰撞
void checkHit()
{
	//两个矩形是否相交
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist && obstacles[i].hited == false) {
			int a1x, a1y, a2x, a2y;
			int off = 30;

			//非下蹲（奔跑或跳跃）
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

			//障碍物的4个顶点
			int b1x = obstacles[i].x + off;
			int b1y = obstacles[i].y + off;
			int b2x = obstacles[i].x + obstacleImgs[obstacles[i].type][obstacles[i].imgIndex].getwidth() - 10;
			int b2y = obstacles[i].y + obstacleImgs[obstacles[i].type][obstacles[i].imgIndex].getheight() - 10;

			//碰撞扣血
			if (rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y)) {
				heroBlood -= obstacles[i].power;
				printf("血量剩余%d\n", heroBlood);
				playSound("res/hit.mp3");
				obstacles[i].hited = true;
			}
		}
	}
}





//设A[x01,y01,x02,y02]  B[x11,y11,x12,y12].
//判断是否相交
bool rectIntersect(int x01, int y01, int x02, int y02,
    int x11, int y11, int x12, int y12)
{
    int zx = abs(x01 + x02 - x11 - x12);
    int x = abs(x01 - x02) + abs(x11 - x12);
    int zy = abs(y01 + y02 - y11 - y12);
    int y = abs(y01 - y02) + abs(y11 - y12);
    return  (zx <= x && zy <= y);
}
