/*!
 * autowork.cpp
 * Autowork类的实现。
 */

#include "pushbutton.h"
#include "autowork.h"

#include <QLabel>
#include <malloc.h>

Autowork::Autowork()
{

}

Autowork::~Autowork()
{

}

void Autowork::Acquire(int r, int c, int rt, int ct, int **f, int **p, PushButton ***b)
{   
    row = r;
    column = c;
    RowTotal = rt;
    ColumnTotal = ct;
    flag = f;
    pointer = p;
    button = b;
}

/*!
 * 思路：
 * 若对方块的所处位置分类讨论，太过繁琐（因为要考虑到边、角）。
 * 故新建立(RowTotal+2)*(ColumnTotal+2)阵，将原有方阵周围
 * 加上一圈空白的边，从而避开繁琐的分类讨论。
 */
int Autowork::Judge(int r, int c)
{
    int **tempmap;
    int **tempflag;
    int i, j;

    tempmap = (int**)malloc((RowTotal+2)*sizeof(int*)); // +2 是因为采用加边法，将row*column阵变成了
    for (i = 0; i<RowTotal+2; i++)                        //(RowTotal+2)*(ColumnTotal+2)阵，避免对边界条件下
        *(tempmap+i) = (int*)malloc((ColumnTotal+2)*sizeof(int));   //某个方格周围雷数的繁琐讨论
    for (i = 0; i<RowTotal+2; i++)
        for (j = 0; j<ColumnTotal+2; j++)
            tempmap[i][j] = -1;
    for (i = 0; i<RowTotal; i++)
        for (j = 0; j<ColumnTotal; j++)
            tempmap[i+1][j+1] = pointer[i][j];

    tempflag = (int**)malloc((RowTotal+2)*sizeof(int*)); // +2 是因为采用加边法，将row*column阵变成了
    for (i = 0; i<RowTotal+2; i++)                        //(RowTotal+2)*(ColumnTotal+2)阵，避免对边界条件下
        *(tempflag+i) = (int*)malloc((ColumnTotal+2)*sizeof(int));   //某个方格周围雷数的繁琐讨论
    for (i = 0; i<RowTotal+2; i++)
        for (j = 0; j<ColumnTotal+2; j++)
            tempflag[i][j] = 0;
    for (i = 0; i<RowTotal; i++)
        for (j = 0; j<ColumnTotal; j++)
            tempflag[i+1][j+1] = flag[i][j];

    if (tempmap[r][c] == 0&&tempflag[r][c] == 1)
        return 1;
    if (tempmap[r][c+1] == 0&&tempflag[r][c+1] == 1)
        return 1;
    if (tempmap[r][c+2] == 0&&tempflag[r][c+2] == 1)
        return 1;
    if (tempmap[r+1][c] == 0&&tempflag[r+1][c] == 1)
        return 1;
    if (tempmap[r+1][c+2] == 0&&tempflag[r+1][c+2] == 1)
        return 1;
    if (tempmap[r+2][c] == 0&&tempflag[r+2][c] == 1)
        return 1;
    if (tempmap[r+2][c+1] == 0&&tempflag[r+2][c+1] == 1)
        return 1;
    if (tempmap[r+2][c+2] == 0&&tempflag[r+2][c+2] == 1)
        return 1;

    return 0;
}

/*!
 * 思路：
 * 不断地扫描所有方块，遇到周围有空方块的非雷且尚未翻开的方块时，
 * 翻开该方块。直到所有应该被翻开的方块均已被翻开。
 */
void Autowork::Scan()
{
    int i, j;
    int whether = 0;
    while (1)
    {
        for (i = 0; i<RowTotal; i++)
            for (j = 0; j<ColumnTotal; j++)
                if (Judge(i, j) == 1&&pointer[i][j] != -1&&flag[i][j] == 0)
                {
                    flag[i][j] = 1;
                    button[i][j]->hide();
                    whether = 1;
                }
        if (whether == 0)
            break;
        whether = 0;  //用以保障所有该被自动翻开的的方块均已自动翻开
    }
}
