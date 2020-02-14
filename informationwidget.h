#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <dde-dock/pluginsiteminterface.h>
#include "pluginsettingdialog.h"

struct Info{
    QString cpu;
    QString mem;
    QString netup;
    QString netdwon;
};

class InformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InformationWidget(QWidget *parent = nullptr);
    void UpdateData(const Info& info,Dock::DisplayMode dismode,const Settings& settings);

public:
    // 真正的数据显示在这个 Label 上
    QLabel *m_infoLabel;
    // 字体
	QFont font;
};

#endif // INFORMATIONWIDGET_H
