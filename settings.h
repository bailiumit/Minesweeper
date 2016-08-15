/*!
 * settings.h
 * Settings类的声明。
 * 这个类用于在开始游戏前弹出“设置”对话框，提醒玩家
 * 设置游戏中雷区的长、宽以及雷数。
 */


#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings:public QObject
{
    Q_OBJECT

public:
    Settings();  //构造函数
    ~Settings();  //析构函数
    void Acquire(int r, int c, int m);  //用于初始化相应数据
    void SettingsShow();  //用于显示“设置”对话框
    int RowReturn();  //用于将row值传到外部
    int ColumnReturn();  //用于将column值传到外部
    int MinesReturn();  //用于将column值传到外部

public slots:
    void RowSetting(int r);  //用于设定row值
    void ColumnSetting(int c);  //用于设定row值
    void MinesSetting(int m);  //用于设定row值

private:
    int row, column, mines;  //分别代表雷区行数、雷区列数、雷数
};

#endif // SETTINGS_H
