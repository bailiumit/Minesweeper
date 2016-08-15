/*!
 * mainwindow.h
 * MainWindow类的声明。
 * 本类用于创建游戏界面框架，包括菜单栏、计时器、
 * 剩余旗数显示。
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QTimer>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();  //析构函数
    void Acquire(int r, int c, int m);  //用于初始化相关数据

public slots:
    void TimeManage(int w);  //用于根据开始、结束信号而控制计时器
    void TimeShow();  //用于显示计时
    void FlagNum(int f);  //用于显示剩余的旗数
    void NewShow();  //用于重启游戏
    void HelpShow();  //用于显示“游戏玩法”
    void InfoShow();  //用于显示“关于扫雷”

private:
    Ui::MainWindow *ui;
    QAction *setAction;

    QLCDNumber *time_count, *flag_left;  //分别代表显示计时、剩余旗数的LCD
    QTimer *time_counter;  //计时器
    int row, column, mines;  //分别代表雷区行数、雷区列数、雷数
    int start, end;  //分别代表计时开始时的时间、计时长度
    int JudgeStart;  //代表对是否已经开启计时器的判断（0为未开启，1为已开启）
};

#endif // MAINWINDOW_H
