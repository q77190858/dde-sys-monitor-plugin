#ifndef PLUGINSETTINGDIALOG_H
#define PLUGINSETTINGDIALOG_H
#include <QDir>
#include <QDialog>

//显示内容设置返回的枚举类型
enum DisplayContentSetting
{
    CPUMEM=1,//只显示CPU内存
    NETSPEED=2,//只显示网速
    ALL=3//两个都显示
};
struct Settings//设置结构体
{
    DisplayContentSetting efficient;
    DisplayContentSetting fashion;
    int lineHeight;
};

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

private:
    Ui::pluginSettingDialog *ui;
};

#endif // PLUGINSETTINGDIALOG_H
