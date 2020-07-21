#ifndef PLUGINSETTINGDIALOG_H
#define PLUGINSETTINGDIALOG_H
#include <QDir>
#include <QMap>
#include <QMapIterator>
#include <QDialog>
#include <QColorDialog>
#include <QDebug>
#include "type.h"

namespace Ui {
class pluginSettingDialog;
}

class pluginSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit pluginSettingDialog(Settings *settings,QWidget *parent = 0);
    ~pluginSettingDialog();
    //公有函数获得显示设置
    void getDisplayContentSetting(Settings *settings);

private slots:
    void selectColor(void);

private:
    Ui::pluginSettingDialog *ui;
    //公用的画板
    QPalette pal;
};

#endif // PLUGINSETTINGDIALOG_H
