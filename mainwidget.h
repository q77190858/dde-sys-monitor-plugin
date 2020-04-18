#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QVBoxLayout>
#include <dde-dock/pluginsiteminterface.h>
#include "pluginsettingdialog.h"

struct Info{
    QString cpu;
    QString mem;
    QString netup;
    QString netdwon;
};

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void UpdateData(const Info& info,Dock::DisplayMode dismode,const Settings& settings);

public:
    int dpi;
    QVBoxLayout *centralLayout;
    // 真正的数据显示在这个 Label 上
    QLabel *m_infoLabel1;
    QLabel *m_infoLabel2;
    // 字体
    QFont font;

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
