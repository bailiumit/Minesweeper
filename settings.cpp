#include "settings.h"

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>

Settings::Settings()
{

}

Settings::~Settings()
{

}

void Settings::Acquire(int r, int c, int m)
{
    row = r;
    column = c;
    mines = m;
}

/*!
 * 思路：
 * 创建对话框、标签、SpinBox、确认按钮，并将其放置在
 * 网格布局管理器。
 */
void Settings::SettingsShow()
{
    QDialog *settings;
    QLabel *label_row, *label_column, *label_mines;
    QSpinBox *settings_row, *settings_column, *settings_mines;
    QPushButton *confirm;
    QGridLayout *layout;

    settings = new QDialog;
    settings->setWindowTitle(tr("设置"));
    settings->setWindowIcon(QIcon(":/icon/settings"));

    label_row = new QLabel(settings);
    label_row->setText(tr("行数(9-20)"));

    label_column = new QLabel(settings);
    label_column->setText(tr("列数(9-36)"));

    label_mines = new QLabel(settings);
    label_mines->setText(tr("雷数"));

    settings_row = new QSpinBox(settings);
    settings_row->setRange(9, 20);
    settings_row->setValue(9);
    QObject::connect(settings_row, SIGNAL(valueChanged(int)), this, SLOT(RowSetting(int)));

    settings_column = new QSpinBox(settings);
    settings_column->setRange(9, 36);
    settings_column->setValue(9);
    QObject::connect(settings_column, SIGNAL(valueChanged(int)), this, SLOT(ColumnSetting(int)));

    settings_mines = new QSpinBox(settings);
    settings_mines->setRange(1, 720);
    settings_mines->setValue(10);
    QObject::connect(settings_mines, SIGNAL(valueChanged(int)), this, SLOT(MinesSetting(int)));

    confirm = new QPushButton(settings);
    confirm->setText(tr("确定"));
    QObject::connect(confirm, SIGNAL(clicked()), settings, SLOT(close()));

    layout = new QGridLayout;
    layout->addWidget(label_row, 0, 0);
    layout->addWidget(label_column, 1, 0);
    layout->addWidget(label_mines, 2, 0);
    layout->addWidget(settings_row, 0, 1);
    layout->addWidget(settings_column, 1, 1);
    layout->addWidget(settings_mines, 2, 1);
    layout->addWidget(confirm, 3, 0, 1, 2);

    settings->setLayout(layout);

    settings->exec();
}

int Settings::RowReturn()
{
    return row;
}

int Settings::ColumnReturn()
{
    return column;
}

int Settings::MinesReturn()
{
    return mines;
}

void Settings::RowSetting(int r)
{
    row = r;
}

void Settings::ColumnSetting(int c)
{
    column = c;
}

void Settings::MinesSetting(int m)
{
    mines = m;
}
