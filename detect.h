/*!
 * detect.h
 * Detect类的声明。
 * 本类用于鼠标左键点击方块时作出相应的回应，
 * 包括自动翻开空方块周围的方块、判断玩家输赢。
 */

#ifndef DETECT_H
#define DETECT_H

#include "pushbutton.h"

#include <QObject>

class Detect:public QObject
{
    Q_OBJECT

public:
    Detect();  //构造函数
    ~Detect();  //析构函数
    void Acquire(int r, int c, int rt, int ct, int **f, int **p, int w, PushButton ***b);  //用于初始化相关数据
    int Check();  //用于判断当前玩家是否已赢得本局游戏
    void ResultDialog(int res);  //用于显示表示输赢的“结果”对话框

public slots:
    void React();  //用于在翻开一个方块时，根据其代表的地雷分布情况选择相应的措施
    void Restart();  //用于重启游戏

signals:
    void BottonHide();  //当翻开空方块时，发出此信号，促使周围非雷方块自动翻开
    void TimerControl(int w);  //当翻开第一个方块时，发出此信号使计时器开始工作；当玩家赢或输时，发出此信号使计时器停止工作

private:
    int row, column;  //分别表示翻开的方块所在的行、列
    int RowTotal, ColumnTotal;  //分别表示雷区总行数、雷区总列数
    int **flag;  //表示整个雷阵方块被翻开的情况
    int **pointer;  //表示地雷分布图
    int WhetherStart;  //表示游戏是否已经开始（0为未开始，1为已开始）
    PushButton ***button;  //表示代表方块的按钮组
};

#endif // DETECT_H
