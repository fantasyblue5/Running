#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include <vector> //C++长度可变数组
#include "background.h" //载入图片

#define WIN_WIDTH 1012 
#define WIN_HEIGHT 396
#define OBSTACLE_COUNT 10 //障碍物种类

extern int bgSpeed[3]; //3重背景不同的速度


using namespace std; //声明命名空间

typedef enum {
	TORTOISE, //乌龟 0
	LION, //狮子 1
	HOOK1,
	HOOK2,
	HOOK3,
	HOOK4,
	OBSTACLE_TYPE_COUNT //障碍物的数量
} obstacle_type;

//每一行为同一障碍物类型的不同图片，每一列为不同的障碍物类型
vector<vector<IMAGE>>obstacleImgs; //IMAGE obstacleImgs[][]可变二维数组，存放所有障碍物的各个图片

typedef struct obstacle {
	int type; //障碍物的类型
	int imgIndex; //当前显示的图片的序号
	int x, y; //障碍物的坐标
	int speed; //障碍物的速度
	int power; //扣血杀伤力

	bool exist; //表示是否存在
	bool hited; //表示是否已经发生碰撞
	bool passed; //表示是否通过
} obstacle_t;

obstacle_t obstacles[OBSTACLE_COUNT]; //障碍物池
int lastObsIndex; //障碍物的序号


//导入障碍物素材
void initObstacle()
{
	char nameObstacle[64];

	//加载乌龟素材，存入二维数组
	IMAGE imgTort;
	loadimage(&imgTort, "res/t1.png");
	vector<IMAGE> imgTortArray;
	imgTortArray.push_back(imgTort);
	obstacleImgs.push_back(imgTortArray);

	//加载狮子素材，存入二维数组
	IMAGE imgLion;
	vector<IMAGE> imgLionArray;
	for (int i = 0; i < 6; ++i) {
		sprintf(nameObstacle, "res/p%d.png", i + 1);
		loadimage(&imgLion, nameObstacle);
		imgLionArray.push_back(imgLion);
	}
	obstacleImgs.push_back(imgLionArray);

	//初始化障碍物池
	for (int i = 0; i < OBSTACLE_COUNT; ++i) {
		obstacles[i].exist = false;

	}

	//加载柱子素材，存入二维数组
	IMAGE imgH;

	for (int i = 0; i < 4; ++i) {
		vector<IMAGE> imgHookArray;
		sprintf(nameObstacle, "res/h%d.png", i + 1);
		loadimage(&imgH, nameObstacle, 63, 260, true);
		imgHookArray.push_back(imgH);
		obstacleImgs.push_back(imgHookArray);
	}

	//障碍物编号初始化
	lastObsIndex = -1;
}

//创建障碍物
void createObstacle()
{
	//无障碍物退出
	int i;
	for (i = 0; i < OBSTACLE_COUNT; ++i) {
		if (obstacles[i].exist == false) {
			break;
		}
	}
	if (i >= OBSTACLE_COUNT) {
		return;
	}

	//障碍物参数值初始化
	obstacles[i].exist = true;
	obstacles[i].hited = false;
	obstacles[i].imgIndex = 0;
	obstacles[i].type = rand() % 3;
	obstacles[i].x = WIN_WIDTH;
	obstacles[i].y = 345 + 5 - obstacleImgs[obstacles[i].type][0].getheight();

	//柱子的类型随机出现
	if (obstacles[i].type == HOOK1) {
		obstacles[i].type += rand() % 4;
	}

	//更新障碍物类型
	//如果上一次出现的是柱子，将可能出现的狮子改为乌龟
	if (lastObsIndex >= 0 &&
		obstacles[lastObsIndex].type >= HOOK1 &&
		obstacles[lastObsIndex].type <= HOOK4 &&
		obstacles[i].type == LION &&
		obstacles[lastObsIndex].x > (WIN_WIDTH - 500)) {
		obstacles[i].type = TORTOISE;
	}

	lastObsIndex = i;

	//不同种类的障碍物设置不同
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

//加载障碍物
void updateEnemy()
{
	//渲染障碍物
	for (int i = 0; i < OBSTACLE_COUNT; ++i) {
		if (obstacles[i].exist) {
			putimagePNG2(obstacles[i].x, obstacles[i].y, WIN_WIDTH, &obstacleImgs[obstacles[i].type][obstacles[i].imgIndex]);
		}
	}
}

//障碍物跑动
void flyObstacle()
{
	//创建障碍物
	static int frameCount = 0;
	static int enemyFre = 50;
	frameCount++;

	//随机帧之后再出现障碍物
	if (frameCount > enemyFre) {
		frameCount = 0;
		enemyFre = 50 + rand() % 50; //(50,99)帧随机出现障碍物
		createObstacle();
	}

	//更新障碍物坐标
	for (int i = 0; i < OBSTACLE_COUNT; ++i) {
		if (obstacles[i].exist) {
			obstacles[i].x -= obstacles[i].speed + bgSpeed[2];
			if (obstacles[i].x < -obstacleImgs[obstacles[i].type][0].getwidth() * 2) {
				obstacles[i].exist = false;
			}

			//障碍物图片播放
			int len = obstacleImgs[obstacles[i].type].size(); //障碍物一共有几张图片
			obstacles[i].imgIndex = (obstacles[i].imgIndex + 1) % len;
		}
	}

}

