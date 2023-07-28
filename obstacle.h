#pragma once

//д��ͷ�ļ����ں����ж�
typedef struct obstacle {
	int type; //�ϰ��������
	int imgIndex; //��ǰ��ʾ��ͼƬ�����
	int x, y; //�ϰ��������
	int speed;
	int power; //��Ѫɱ����

	bool exist; //��ʾ�Ƿ����
	bool hited; //��ʾ�Ƿ��Ѿ�������ײ
	bool passed; //��ʾ�Ƿ�ͨ��
} obstacle_t;


void initObstacle(); //���ϰ����ʼ���������ز�
void createObstacle(); //�����ϰ���Ĳ���
void updateEnemy(); //��Ⱦ�ϰ���
void flyObstacle(); //ʹ�ϰ����ڴ��ڹ���