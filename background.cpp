
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <graphics.h>
#include "background.h"

#define WIN_WIDTH 1012 
#define WIN_HEIGHT 396

IMAGE imgBgs[3]; //背景图片
int bgX[3]; //背景图片X坐标
int bgSpeed[3] = { 1,2,4 }; //3重背景不同的速度


//初始化背景
void initBackground()
{
	//创建游戏窗口
	initgraph(WIN_WIDTH, WIN_HEIGHT, 1);

	//加载背景资源
	char nameBg[64];
	for (int i = 0; i < 3; ++i) {
		sprintf(nameBg, "res/bg%03d.png", i + 1);
		loadimage(&imgBgs[i], nameBg);

		bgX[i] = 0;
	}

}

//加载背景
void updateBg()
{
	putimagePNG2(bgX[0], 0, &imgBgs[0]);
	putimagePNG2(bgX[1], 119, &imgBgs[1]);
	putimagePNG2(bgX[2], 330, &imgBgs[2]);
}

//背景循环播放
void flyBackground()
{
	//三重背景调速
	for (int i = 0; i < 3; ++i) {
		bgX[i] -= bgSpeed[i];
		if (bgX[i] < -WIN_WIDTH) {
			bgX[i] = 0;
		}
	}

}




// 载入PNG图并去透明部分（开源）
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
    int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
    int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
    int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
    int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
    int dstX = 0;    //在显存里像素的角标

    // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //在显存里像素的角标
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
            int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
                    | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
                    | (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
            }
        }
    }
}

// 适用于 y <0 以及x<0的任何情况
void putimagePNG2(int x, int y, IMAGE* picture) {
    IMAGE imgTmp;
    if (y < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, 0, -y,
            picture->getwidth(), picture->getheight() + y);
        SetWorkingImage();
        y = 0;
        picture = &imgTmp;
    }

    if (x < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, -x, 0, picture->getwidth() + x, picture->getheight());
        SetWorkingImage();
        x = 0;
        picture = &imgTmp;
    }

    putimagePNG(x, y, picture);
}

// 适用于 y <0 以及y>0的任何情况（开源）
void putimagePNG2(int x, int y, int winWidth, IMAGE* picture) {
    IMAGE imgTmp;
    if (y < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, 0, -y,
            picture->getwidth(), picture->getheight() + y);
        SetWorkingImage();
        y = 0;
        picture = &imgTmp;
    }

    if (x < 0) {
        SetWorkingImage(picture);
        getimage(&imgTmp, -x, 0, picture->getwidth() + x, picture->getheight());
        SetWorkingImage();
        x = 0;
        picture = &imgTmp;
    }
    else if (x >= winWidth) {
        return;
    }
    else if (x > winWidth - picture->getwidth()) {
        SetWorkingImage(picture);
        getimage(&imgTmp, 0, 0, winWidth - x, picture->getheight());
        SetWorkingImage();
        picture = &imgTmp;
    }

    putimagePNG(x, y, picture);
}
