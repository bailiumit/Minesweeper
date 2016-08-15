/*!
 * main.cpp
 * 思路：
 * 先通过“设置”对话框，将雷区初始化为row行，
 * column列，mines个雷。
 * 然后通过标签将雷阵信息的二维数组用图标表示，形成背景图。
 * 最后用按钮组覆盖背景图，并通过连接信号和槽使按钮组形成
 * 对鼠标左键单击、右键单击的反馈机制。
 */

#include "mainwindow.h"
#include "settings.h"
#include "pushbutton.h"
#include "detect.h"
#include "autowork.h"

#include "create.h"
#include "map.h"

#include <QApplication>
#include <QObject>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    int row, column, mines;
    int i, j;
    int **mine_map;
    int **mine_flag;

    QApplication a(argc, argv);
    Settings set;
    MainWindow w;
    PushButton ***mine_area;
    QLabel ***mine_background;
    Detect unit[20][36];
    Autowork item[20][36];

    //!将雷区初始化
    set.Acquire(9, 9, 10);  //将set初始化
    set.SettingsShow();  //弹出“设置”窗口
    row = set.RowReturn();  //为row赋值
    column = set.ColumnReturn();  //为column赋值
    if (set.MinesReturn()>row*column)
        mines = row*column;  //为mines赋值
    else  //当返回的mines值不大于方块数时才用返回值
        mines = set.MinesReturn();

    w.Acquire(row, column, mines);  //将窗口初始化
    w.setFixedSize(40+50*column, 120+50*row);  //设置窗口尺寸

    mine_map = MapCreate(row, column, mines);
    mine_flag = FlagCreate(row, column);
    mine_area = ButtonCreate(row, column);
    mine_background = LabelCreate(row, column);

    //!形成雷阵信息背景图
    for (i = 0; i<row; i++)
            for (j = 0; j<column; j++)
            {
                mine_background[i][j] = new QLabel(&w);
                mine_background[i][j]->setGeometry(20+50*j, 100+50*i, 50, 50);
                if (mine_map[i][j] == -1)
                {
                    QPixmap pix_mine(":/icon/mine");
                    mine_background[i][j]->setPixmap(pix_mine);
                }
                if (mine_map[i][j] == 0)
                {
                    QPixmap pix_num0(":/icon/num0");
                    mine_background[i][j]->setPixmap(pix_num0);
                }
                if (mine_map[i][j] == 1)
                {
                    QPixmap pix_num1(":/icon/num1");
                    mine_background[i][j]->setPixmap(pix_num1);
                }
                if (mine_map[i][j] == 2)
                {
                   QPixmap pix_num2(":/icon/num2");
                   mine_background[i][j]->setPixmap(pix_num2);
                }
                if (mine_map[i][j] == 3)
                {
                   QPixmap pix_num3(":/icon/num3");
                   mine_background[i][j]->setPixmap(pix_num3);
                }
                if (mine_map[i][j] == 4)
                {
                   QPixmap pix_num4(":/icon/num4");
                   mine_background[i][j]->setPixmap(pix_num4);
                }
                if (mine_map[i][j] == 5)
                {
                   QPixmap pix_num5(":/icon/num5");
                   mine_background[i][j]->setPixmap(pix_num5);
                }
                if (mine_map[i][j] == 6)
                {
                   QPixmap pix_num6(":/icon/num6");
                   mine_background[i][j]->setPixmap(pix_num6);
                }
                if (mine_map[i][j] == 7)
                {
                   QPixmap pix_num7(":/icon/num7");
                   mine_background[i][j]->setPixmap(pix_num7);
                }
                if (mine_map[i][j] == 8)
                {
                    QPixmap pix_num8(":/icon/num8");
                    mine_background[i][j]->setPixmap(pix_num8);
                }
                mine_background[i][j]->show();
            }

    //!创建按钮组并连接相应的信号和槽
    for (i = 0; i<row; i++)
        for (j = 0; j<column; j++)
        {
            mine_area[i][j] = new PushButton(&w);
            mine_area[i][j]->Acquire(0);
            mine_area[i][j]->setGeometry(20+50*j, 100+50*i, 50, 50);

            unit[i][j].Acquire(i, j, row, column, mine_flag, mine_map, 0, mine_area);
            item[i][j].Acquire(i, j, row, column, mine_flag, mine_map, mine_area);

            QObject::connect(mine_area[i][j], SIGNAL(LeftClicked()), &unit[i][j], SLOT(React()));
            QObject::connect(mine_area[i][j], SIGNAL(FlagChange(int)), &w, SLOT(FlagNum(int)));
            QObject::connect(&unit[i][j], SIGNAL(BottonHide()), &item[i][j], SLOT(Scan()));
            QObject::connect(&unit[i][j], SIGNAL(TimerControl(int)), &w, SLOT(TimeManage(int)));
        }

    w.move((QApplication::desktop()->width()-w.width())/2, (QApplication::desktop()->height()-w.height())/2);
    w.show();

    return a.exec();
}
