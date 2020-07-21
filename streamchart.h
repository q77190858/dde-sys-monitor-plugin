#ifndef STREAMCHART_H
#define STREAMCHART_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QQueue>
#include <QTimer>
#include <QtGlobal>
#include "type.h"

class StreamChart : public QWidget
{
    Q_OBJECT

public:
    explicit StreamChart(QWidget *parent = nullptr);
    ~StreamChart();
    //重载绘图函数
    void paintEvent(QPaintEvent*);
    //定时更新数据图标的函数
public slots:
    void updateChart(struct Data&);

private:
    QPen *penb,*pen1,*pen2;
    QQueue<struct Data> *queue;
public:
    int height;
    int width;
    int spacing;
    QColor colorBorder,colorBackground,color1,color2;
    int borderRound;
};

#endif // STREAMCHART_H
