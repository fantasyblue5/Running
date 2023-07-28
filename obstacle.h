#pragma once

//写入头文件用于后续判定
typedef struct obstacle {
	int type; //障碍物的类型
	int imgIndex; //当前显示的图片的序号
	int x, y; //障碍物的坐标
	int speed;
	int power; //扣血杀伤力

	bool exist; //表示是否存在
	bool hited; //表示是否已经发生碰撞
	bool passed; //表示是否通过
} obstacle_t;


void initObstacle(); //将障碍物初始化，导入素材
void createObstacle(); //设置障碍物的参数
void updateEnemy(); //渲染障碍物
void flyObstacle(); //使障碍物在窗口滚动