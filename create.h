/*!
 * create.h
 * 此头文件包含创建按钮组、雷区分布标签组、
 * 雷阵被翻开的情况组的函数。
 */

#ifndef CREATE_H
#define CREATE_H

#include "pushbutton.h"

#include <QLabel>

//该函数动态生成了row*column的按钮组
PushButton ***ButtonCreate(int row, int column)
{
    PushButton ***area;
    int i;

    area = (PushButton***)malloc(row*sizeof(PushButton**));
    for (i = 0; i<row; i++)
        *(area+i) = (PushButton**)malloc(column*sizeof(PushButton*));

    return area;
}

//该函数动态生成了row*column的标签组
QLabel ***LabelCreate(int row, int column)
{
    QLabel ***background;
    int i;

    background = (QLabel***)malloc(row*sizeof(QLabel**));
    for (i = 0; i<row; i++)
        *(background+i) = (QLabel**)malloc(column*sizeof(QLabel*));

    return background;
}

//该函数动态生成了row*column的二维组并对其初始化
//0代表此方块尚未被翻开
int **FlagCreate(int row, int column)
{
    int **flag;
    int i, j;

    flag = (int**)malloc(row*sizeof(int*));
    for (i = 0; i<row; i++)
        *(flag+i) = (int*)malloc(column*sizeof(int));

    for (i = 0; i<row; i++)
        for (j = 0; j<column; j++)
            flag[i][j] = 0;

    return flag;
}

#endif // CREATE_H
