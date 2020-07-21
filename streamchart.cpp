#include "streamchart.h"

StreamChart::StreamChart(QWidget *parent) :
    QWidget(parent)
{
    penb=new QPen();
    penb->setWidth(2);
    pen1=new QPen();
    pen1->setWidth(1);
    pen2=new QPen();
    pen2->setWidth(1);
    queue=new QQueue<struct Data>();
}

StreamChart::~StreamChart()
{
    delete penb;
    delete pen1;
    delete pen2;
    delete queue;
}

void StreamChart::paintEvent(QPaintEvent *)
{
    if(!queue->isEmpty())
    {
        QPainter pt(this);

        //画背景
        pt.fillRect(0,0,width,height,colorBackground);
        int x,dy1,dy2;
        //画线条
        for(int i=0;i<queue->size();i++)
        {
            x=width-queue->size()+i;//+spacing;
            dy1=queue->at(i).x*height/100;
            dy1=(dy1==1?dy1+1:dy1);
            dy2=queue->at(i).y*height/100;
            //dy2=(dy2==1?dy2+1:dy2);
            pen1->setColor(color1);
            pt.setPen(*pen1);
            pt.drawLine(x,height,x,height-dy1);
            if(color2.alpha())
            {
                pen2->setColor(color2);
                pt.setPen(*pen2);
                pt.drawLine(x,height,x,height-dy2);
            }

        }
        //最后画矩形
        penb->setColor(colorBorder);
        pt.setPen(*penb);
        pt.drawRoundRect(0,0,width,height,borderRound,borderRound);
    }
}

void StreamChart::updateChart(struct Data& data)
{
    queue->enqueue(data);
    setMinimumSize(width,height);
    setMaximumSize(width,height);
    if(queue->size()>width)queue->dequeue();
    update();
}
