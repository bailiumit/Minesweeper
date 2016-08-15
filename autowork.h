/*!
 * autowork.h
 * Autowork的声明。
 * 本类用于自动翻开空方块周围的非雷方块。
 * 思路：
 * 转变思维方式，从“自动翻开空方块周围的非雷方块”转换为
 * “扫描所有方块，当某一非雷且尚未翻开的方块周围有空方块时，
 * 该方块自动翻开”
 */

#ifndef AUTOWORK_H
#define AUTOWORK_H

#include <QObject>
#include "pushbutton.h"

class Autowork:public QObject
{
    Q_OBJECT

public:
    Autowork(); //构造函数
    ~Autowork();  //析构函数
    void Acquire(int r, int c, int rt, int ct, int **f, int **p, PushButton ***b);  //用于初始化相关数据
    int Judge(int r, int c);  //用于判断一个方块周围是否有空方块

public slots:
    void Scan();  //用于扫描所有方块，当某一非雷且尚未翻开的方块周围有已翻开的空方块时，该方块自动翻开

private:
    int row, column;  //分别表示翻开的方块所在的行、列
    int RowTotal, ColumnTotal;  //分别表示雷区总行数、雷区总列数
    int **flag;  //表示整个雷阵方块被翻开的情况
    int **pointer;  //表示地雷分布图
    PushButton ***button;  //表示代表方块的按钮组
};

#endif // AUTOWORK_H
