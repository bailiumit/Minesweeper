/*!
 * pushbutton.h
 * PushButton类的声明。
 * 这是一个继承了QPushbutton的类。
 * 用于创造出新型按钮，以实现扫雷游戏中左键点击方块
 * 能够将其翻开，右键点击一次方块插上小旗、点击两次
 * 变成问号、点击三次恢复原有按钮的目的。
 */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QWidget *parent = 0);
    void Acquire(int t);  //用于初始化times

protected:
    void mousePressEvent(QMouseEvent *e);  //用于重写mousePressEvent函数

signals:
    void LeftClicked();  //左键点击时，发出此信号
    void FlagChange(int f);  //右键点击使方块插上小旗或显示问号时，发送此信号，从而使相应的显示装置改变显示数字

private:
    int times;  //方块上的标记（0代表无标记，1代表小旗，2代表问号）
};

#endif // PUSHBUTTON_H
