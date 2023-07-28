#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include "background.h"
#include "hero.h"
#include "obstacle.h"
#include "hit.h"
#include "score.h"

extern int update;

//计算延时
//第一次调用返回0，第二次调用返回当前时间和第一次调用时间的差
int getDelay() {
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}

//主函数
int main(void)
{
	initBackground();
	initHero();
	initObstacle();
	initHit();
	initScore();

	int timer = 0;

	while (1) {
		keyEvent();

		//三十秒刷新窗口
		timer += getDelay();
		if (timer > 30) {
			timer = 0;
			update = true;
		}

		if (update) {
			update = false;

			BeginBatchDraw();
			updateBg();
			updateHero();
			updateEnemy();
			updateBloodBar();
			updateScore();
			checkWin();
			EndBatchDraw();

			checkOver();
			checkScore();

			flyBackground();
			flyHero();
			flyObstacle();

			checkHit();
		}

	}

	system("pause");
}

