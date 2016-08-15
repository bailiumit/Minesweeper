/*!
 * detect.h
 * Detect类的实现。
 */

#include "pushbutton.h"
#include "detect.h"

#include <QDialog>
#include <QLabel>
#include <QApplication>
#include <QProcess>

Detect::Detect()
{

}

Detect::~Detect()
{

}

void Detect::Acquire(int r, int c, int rt, int ct, int **f, int **p, int w, PushButton ***b)
{    
    row = r;
    column = c;
    RowTotal = rt;
    ColumnTotal = ct;
    flag = f;
    pointer = p;
    WhetherStart = w;
    button = b;
}

int Detect::Check()
{
    int whether = 1;
    int i, j;

    for (i = 0; i<RowTotal; i++)
        for (j = 0; j<ColumnTotal; j++)
            if (pointer[i][j] != -1&&flag[i][j] == 0)
                whether = 0;

    return whether;
}

/*!
 * 思路：
 * 创建对话框，拥有一样的按钮，但是分输、赢两种情况
 * 来设置文本框内容。
 */
void Detect::ResultDialog(int res)
{
    int i, j;

    QDialog *result = new QDialog;
    QLabel *tell;
    QPushButton *restart, *quit;

    result->setFixedSize(320, 120);
    result->setWindowFlags(Qt::CustomizeWindowHint);  //隐藏对话框的边框

    for (i = 0; i<RowTotal; i++)
        for (j = 0; j<ColumnTotal; j++)
            {
                flag[i][j] = 1;
                button[i][j]->hide();
            }

    tell = new QLabel(result);
    if (res == 1)
        tell->setText(tr("恭喜，您赢了!"));
    else
        tell->setText(tr("抱歉，您输了!"));
    tell->setGeometry(100, 20, 120, 20);

    restart = new QPushButton(result);
    restart->setGeometry(70, 50, 85, 50);
    restart->setText(tr("重玩"));

    quit = new QPushButton(result);
    quit->setGeometry(165, 50, 85, 50);
    quit->setText(tr("结束"));

    QObject::connect(restart, SIGNAL(clicked()), this, SLOT(Restart()));
    QObject::connect(quit,&QPushButton::clicked,&QApplication::quit);

    tell->show();
    result->exec();
}

/*!
 * 思路：
 * 当该函数第一次被触发时，发送使计时器开始计时的信号。
 * 触到-1，代表触雷，玩家输，发送使计时器停止计时的信号，
 * 游戏结束，弹出“结果”对话框。
 * 触到0，代表触到空方块，发送自动翻开方块的信号。
 * Check()为1时，玩家赢，发送使计时器停止计时的信号，
 * 游戏结束，弹出“结果”对话框。
 */
void Detect::React()
{
    flag[row][column] = 1;
    if (WhetherStart == 0)
    {
        emit TimerControl(0);
        WhetherStart = 1;
    }
    if (pointer[row][column] == -1)
    {
       emit TimerControl(1);
       ResultDialog(0);
    }
    if (pointer[row][column] == 0)
       emit BottonHide();
    if (Check() == 1)
    {
       emit TimerControl(1);
       ResultDialog(1);
    }
}

void Detect::Restart()
{
    QProcess *p = new QProcess(this);
    QString str = QApplication::applicationFilePath();
    p->startDetached(str, QStringList());
    QApplication::quit();
}
