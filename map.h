/*!
 * map.h
 * 此头文件用于创建记录雷阵信息的二维数组:
 * -1代表雷，0~8代表这一方块周围的雷数。
 */


#ifndef MAP_H
#define MAP_H

#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int **MapCreate(int r, int c, int m);   //创建记录雷阵信息的二维数组
int **MineCreate(int r, int c, int m);   //随机创建r行，c列，m个雷的原始雷阵数组（有雷区为-1，无雷区为0）
int MineCount(int **pointer, int r, int c);    //统计位于第r行第c列的方块周围的雷数

/*!
 *思路：
 *通过调用MineCreate、MineCount来完成记录
 *雷阵信息的二维数组的创建。
 */
int **MapCreate(int r, int c, int m)
{
    int i, j;
    int **map, **mine;

    map = (int**)malloc(r*sizeof(int*));
    for (i = 0; i<r; i++)
        *(map+i) = (int*)malloc(c*sizeof(int)); //创建记录雷阵信息的二维数组

    mine = MineCreate(r, c, m);   //创建原始雷阵数组

    for (i = 0; i<r; i++)
        for (j = 0; j<c; j++)
            map[i][j] = MineCount(mine, i+1, j+1);  //统计每个方块周围的雷数并赋值给记录雷阵信息的二维数组

    return map;
}

/*!
 * 思路：
 * 先建立长度为r*c的一维数组，均初始化为0。
 * 再通过时间随机函数，将其中m个数字标为-1，代表被选中的
 * 地雷埋藏点。
 * 再采用取整、取余的方法将长为r*c的一维数组化为r行c列的
 * 二维数组。
 */
int **MineCreate(int r, int c, int m)
{
    int **pointer;
    int *temp;
    int i, j, t;

    srand(time(NULL));

    temp = (int*)malloc(r*c*sizeof(int));

    for (i = 0; i<r*c; i++)
        temp[i] = 0;              //先建立一维数组，方便初始随机化

    for (i = 0; i<m; i++)
    {
        t = rand()%(r*c);
        if (temp[t ] == -1)
            i--;
        else
            temp[t] = -1;         //将尚未被标成雷的区域赋值-1，表示在这里放置雷
    }

    pointer = (int**)malloc((r+2)*sizeof(int*)); // +2 是因为采用加边法，将row*column阵变成了
    for (i = 0; i<r+2; i++)                        //(row+2)*(column+2)阵，避免对边界条件下
        *(pointer+i) = (int*)malloc((c+2)*sizeof(int));   //某个方格周围雷数的繁琐讨论

    for (i = 0; i<r+2; i++)
        for (j = 0; j<c+2; j++)
            pointer[i][j] = 0;

    for (i = 0; i<r*c; i++)
        pointer[i/c+1][i%c+1] = temp[i];

    return pointer;
}

/*!
 * 思路：
 * 先判断值，若为-1，代表此处埋雷，直接返回-1，
 * 终止函数。
 * 若不为-1，代表此处无雷，开始计算周围雷数，返回
 * 周围雷数。
 */
int MineCount(int **pointer, int r, int c)
{
    int num = 0;
    if (pointer[r][c] == -1)
        return -1;
    else
    {
        if (pointer[r-1][c-1] == -1)
            num++;
        if (pointer[r-1][c] == -1)
            num++;
        if (pointer[r-1][c+1] == -1)
            num++;
        if (pointer[r][c-1] == -1)
            num++;
        if (pointer[r][c+1] == -1)
            num++;
        if (pointer[r+1][c-1] == -1)
            num++;
        if (pointer[r+1][c] == -1)
            num++;
        if (pointer[r+1][c+1] == -1)
            num++;
        return num;
    }
}

#endif // MAP_H
