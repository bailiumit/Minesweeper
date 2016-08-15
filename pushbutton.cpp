/*!
 * pushbutton.cpp
 * PushButton类的实现。
 */

#include "pushbutton.h"

#include <QtGui>

PushButton::PushButton(QWidget *parent) :
    QPushButton(parent)
{

}

void PushButton::Acquire(int t)
{
    times = t;
}

/*!
 * 思路：
 * 重写mousePressEvent函数。
 * 单击鼠标左键时发出左键被击的信号，并隐藏相应的按钮。
 * 单击鼠标右键时，利用times判断按钮究竟该显示什么图标。
 */
void PushButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton&&times != 1)
    {
        emit LeftClicked();
        this->hide();      
    }
    if(e->button() == Qt::RightButton)
    {
        if (times == 0)
        {
            times = 1;
            this->setIcon(QIcon(":/icon/flag"));
            emit FlagChange(-1);  //发送信号，告知剩余小旗数应该减1
        }
        else if (times == 1)
        {
            times = 2;
            this->setIcon(QIcon(":/icon/unsure"));
            emit FlagChange(1);  //发送信号，告知剩余小旗数应该加1
        }
        else if (times == 2)
        {
            times = 0;
            this->setIcon(QIcon(":/icon/clear"));  //实际上是一张透明图片
        }
    }

    QPushButton::mousePressEvent(e);
}
