#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QStorageInfo>
#include "pluginsettingdialog.h"

class InformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InformationWidget(QWidget *parent = nullptr);
    void UpdateDataCpuMem(const QString &cpu,const QString &mem);
    void UpdateDataNetSpeed(const QString &sbytes,const QString &rbytes);
    void UpdateDataAll(const QString &cpu,const QString &mem,const QString &sbytes,const QString &rbytes);

public:
    // 真正的数据显示在这个 Label 上
    QLabel *m_infoLabel;
    // 字体
	QFont font;
};

#endif // INFORMATIONWIDGET_H
