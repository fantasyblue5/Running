#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include "background.h"
#include "hero.h"
#include "obstacle.h"
#include "hit.h"
#include "score.h"

extern int update;

//������ʱ
//��һ�ε��÷���0���ڶ��ε��÷��ص�ǰʱ��͵�һ�ε���ʱ��Ĳ�
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

//������
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

		//��ʮ��ˢ�´���
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

