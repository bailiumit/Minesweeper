/*!
 * mainwindow.cpp
 * MainWindow类的实现。
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QTime>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);  //因本程序尚未用到UI界面，故将其隐藏；但不删除，以备之后拓展程序之需要

    //!为菜单栏添加动作
    QAction *new_action = new QAction(QIcon(":/icon/new"), tr("重玩"), this);
    QObject::connect(new_action, SIGNAL(triggered()), this, SLOT(NewShow()));

    QAction *settings_action = new QAction(QIcon(":/icon/settings"), tr("设置"), this);
    QObject::connect(settings_action, SIGNAL(triggered()), this, SLOT(NewShow()));

    QAction *help_action = new QAction(QIcon(":/icon/help"), tr("游戏玩法"), this);
    QObject::connect(help_action, SIGNAL(triggered()), this , SLOT(HelpShow()));

    QAction *info_action = new QAction(QIcon(":/icon/info"), tr("关于扫雷"), this);
    QObject::connect(info_action, SIGNAL(triggered()), this, SLOT(InfoShow()));

    QMenu *Game = menuBar()->addMenu(tr("游戏"));
    Game->addAction(new_action);
    Game->addAction(settings_action);

    QMenu *Help = menuBar()->addMenu(tr("帮助"));
    Help->addAction(help_action);
    Help->addAction(info_action);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * 思路：
 * 当该类接收到数据后，根据数据创建LCD显示窗。
 */
void MainWindow::Acquire(int r, int c, int m)
{
    row = r;
    column = c;
    mines = m;

    JudgeStart = 0;
    time_counter = new QTimer(this);
    connect(time_counter, SIGNAL(timeout()), this, SLOT(TimeShow()));  //实现每隔一段时间触发一次TimeShow()

    time_count = new QLCDNumber(this);
    time_count->setGeometry(20, 50, 100, 40);
    time_count->setSegmentStyle(QLCDNumber::Filled);
    time_count->display(0);
    time_count->show();

    QLabel *time_icon = new QLabel(this);
    time_icon->setGeometry(145, 45, 50, 50);
    QPixmap pix_time(":/icon/time");
    time_icon->setPixmap(pix_time);

    flag_left = new QLCDNumber(this);
    flag_left->setSegmentStyle(QLCDNumber::Filled);
    flag_left->show();

    QLabel *flag_icon = new QLabel(this);
    flag_icon->setGeometry(50*column-150, 45, 50, 50);
    QPixmap pix_flag(":/icon/flagleft");
    flag_icon->setPixmap(pix_flag);

    flag_left->setGeometry(50*column-80, 50, 100, 40);
    flag_left->display(mines);
}

/*!
 * 思路：
 * 开启计时器时，记录当前时间。
 * 结束计时器时，断开计时器的信号和槽的连接，从而停止计时。
 */
void MainWindow::TimeManage(int w)
{
    if (w == 0&&JudgeStart == 0)
    {
        JudgeStart = 1;
        time_counter->start(1000);
        QTime TimeStart = QTime::currentTime();
        start = TimeStart.minute()*60+TimeStart.second();
    }
    else if (w == 1)
        time_counter->disconnect(this);
}

/*!
 * 思路：
 * 每隔一秒这个函数就会被触发一次，显示计时长度。
 */
void MainWindow::TimeShow()
{
    QTime TimeEnd = QTime::currentTime();
    end = TimeEnd.minute()*60+TimeEnd.second()-start;
    time_count->display(end);
}

/*!
 * 思路：
 * f为-1，代表插上了一个小旗，使剩余小旗的数量mines减1。
 * f为1，代表有一个小旗被替换成了问号，剩余小旗的数量增加了一个。
 */
void MainWindow::FlagNum(int f)
{
    mines = mines+f;
    flag_left->display(mines);
}

void MainWindow::NewShow()
{
    QProcess *p = new QProcess(this);
    QString str = QApplication::applicationFilePath();
    p->startDetached(str, QStringList());
    close();
}

void MainWindow::HelpShow()
{
    QDialog *help = new QDialog;
    QLabel *help_text = new QLabel;

    help->setWindowTitle(tr("游戏玩法"));
    help->setWindowIcon(QIcon(":/icon/help"));
    help->setFixedSize(762, 627);

    help_text = new QLabel(help);
    QPixmap pix_help_text(":/icon/helptext");
    help_text->setPixmap(pix_help_text);

    help_text->show();
    help->exec();
}

void MainWindow::InfoShow()
{
    QDialog *info = new QDialog;
    QLabel *info_text = new QLabel;

    info->setWindowTitle(tr("关于扫雷"));
    info->setWindowIcon(QIcon(":/icon/info"));
    info->setFixedSize(480, 135);

    info_text = new QLabel(info);
    QPixmap pix_info_text(":/icon/infotext");
    info_text->setPixmap(pix_info_text);

    info_text->show();
    info->exec();
}
