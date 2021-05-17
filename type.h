#ifndef TYPE_H
#define TYPE_H
#include <QString>
#include <QVariant>
//主插件类传递给widget的信息结构体
struct Info{
    QString scpu;int cpu;
    QString scputemp;double cputemp;
    QString smem;int mem;
    QString snetup;int netup;
    QString snetdwon;int netdown;
};

//显示内容设置返回的枚举类型
enum DisplayContentSetting
{
    CPUMEM=0,//只显示CPU内存
    NETSPEED=1,//只显示网速
    ALL=2//两个都显示
};

struct SettingItem{
    QString name;
    QVariant value;
};

typedef QMap<QString,QVariant> Settings;

struct Data
{
    int x;
    int y;
};

#endif // TYPE_H
