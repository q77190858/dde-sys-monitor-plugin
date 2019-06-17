#include "sysmonitorplugin.h"

SysMonitorPlugin::SysMonitorPlugin(QObject *parent)
    : QObject(parent)
	,m_refreshTimer(new QTimer(this))
{
	oldrbytes=oldsbytes=0;
	// 设置 Timer 超时为 1s，即每 1s 更新一次控件上的数据，并启动这个定时器
    m_refreshTimer->start(1000);
	
	// 连接 Timer 超时的信号到更新数据的槽上
    connect(m_refreshTimer, &QTimer::timeout, this, &SysMonitorPlugin::refreshInfo);
}

void SysMonitorPlugin::refreshInfo()
{
	//获得cpu信息
	fp = fopen("/proc/stat", "r");
    if (fp == NULL) {perror("Could not open stat file");return;}
    user = 0, nice = 0, system = 0, idle = 0;
    iowait = 0, irq = 0, softirq = 0, steal = 0, guest = 0, guestnice = 0;
    char* ret = fgets(buffer, sizeof(buffer) - 1, fp);
    if (ret == NULL) {perror("Could not read stat file");fclose(fp);return;}
    fclose(fp);
    sscanf(buffer,"cpu  %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu",&user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guestnice);
    worktime = user + nice + system;
    totaltime = user + nice + system + idle + iowait + irq + softirq + steal;
    // 得到百分比
    cpuPercent = qRound((worktime-oldworktime)*100.0/(totaltime-oldtotaltime));
    oldtotaltime=totaltime;
    oldworktime=worktime;
	if(cpuPercent<=9)strcpu=QString(" %1\%").arg(cpuPercent);
	else strcpu=QString("%1\%").arg(cpuPercent);
	
	//获得内存信息
    fp=fopen("/proc/meminfo","r");
	if (fp == NULL) {perror("Could not open meminfo file");return;}
	do
	{
		ret = fgets(buffer, sizeof(buffer) - 1, fp);
		if (ret == NULL) {perror("Could not read meminfo file");fclose(fp);return;}
		sscanf(buffer,"%s %lu kB",devname,&tmp);
		if(!strcmp(devname,"MemTotal:"))totalmem=tmp;
		else if(!strcmp(devname,"MemAvailable:"))availablemem=tmp;
		else if(!strcmp(devname,"SwapTotal:"))totalswap=tmp;
		else if(!strcmp(devname,"SwapFree:"))freeswap=tmp;
	}while(strcmp(devname,"SwapFree:"));
    fclose(fp);
	memPercent = qRound((totalmem - availablemem) * 100.0 / totalmem);
	if(memPercent<=9)strmem=QString(" %1\%").arg(memPercent);
	else strmem=QString("%1\%").arg(memPercent);
	
    swapPercent = qRound((totalswap - freeswap) * 100.0 / totalswap);
	if(swapPercent<=9)strswap=QString(" %1\%").arg(swapPercent);
	else strswap=QString("%1\%").arg(swapPercent);
	
	//获得net信息
	fp=fopen("/proc/net/dev","r");
	if (fp == NULL) {perror("Could not open netdev file");return;}
	ret = fgets(buffer, sizeof(buffer) - 1, fp);
	ret = fgets(buffer, sizeof(buffer) - 1, fp);
    if (ret == NULL) {perror("Could not read netdev file");fclose(fp);return;}
	tmpr=tmps=rbytes=sbytes=0;
	while(true)
	{
		ret = fgets(buffer, sizeof(buffer) - 1, fp);
    	if (ret == NULL) break;
		sscanf(buffer,"%s %lu %*lu %*lu %*lu %*lu %*lu %*lu %*lu %lu",devname,&tmpr,&tmps);
		if(strcmp(devname,"lo:")==0)continue;
		rbytes+=tmpr;
		sbytes+=tmps;
	}
    fclose(fp);
	tmpr=(oldrbytes==0?0:rbytes-oldrbytes);
	tmps=(oldsbytes==0?0:sbytes-oldsbytes);
	oldrbytes=rbytes;
	oldsbytes=sbytes;
	
	s=toHumanRead(tmps,"B",0);
	r=toHumanRead(tmpr,"B",0);
	
    // 更新内容
    if(m_pluginWidget)m_pluginWidget->UpdateData(strcpu,strmem,s,r);
}

const QString SysMonitorPlugin::toHumanRead(unsigned long l,const char *unit,int digit)
{
	int count;
	QString str;
	double f=(double)l;
	if(!strcmp(unit,"B"))count=0;
	else if(!strcmp(unit,"KB"))count=1;
	while(f>999.0)
	{
		f=f/1024.0;
		count++;
	}
	
	if(f<=9)str="  "+QString::number(f,'f',digit);
	else if(f<=99)str=" "+QString::number(f,'f',digit);
	else str=QString::number(f,'f',digit);
	
	if(count==0)str+=" B";
    else if(count==1)str+="KB";
	else if(count==2)str+="MB";
	else if(count==3)str+="GB";
	else if(count==4)str+="TB";
	else if(count==4)s+="PB";
	return str;
}

const QString SysMonitorPlugin::pluginDisplayName() const
{
    return QString("Sys Monitor");
}

const QString SysMonitorPlugin::pluginName() const
{
    return QStringLiteral("sys_monitor");
}

void SysMonitorPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_pluginWidget = new InformationWidget;
    m_tipsWidget = new QLabel;
    m_appletWidget = new QLabel;

    // 如果插件没有被禁用则在初始化插件时才添加主控件到面板上
    if (!pluginIsDisable()) {
        m_proxyInter->itemAdded(this, pluginName());
    }
}

QWidget *SysMonitorPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_pluginWidget;
}

QWidget *SysMonitorPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    // 设置/刷新 tips 中的信息
    m_tipsWidget->setText(QString("MEM:%1/%2=%3\nSWAP:%4/%5=%6\nUP:%7 %8/S\nDOWN:%9 %10/S")
                            .arg(toHumanRead(totalmem-availablemem,"KB",1)).arg(toHumanRead(totalmem,"KB",1)).arg(strmem)
                            .arg(toHumanRead(totalswap-freeswap,"KB",1)).arg(toHumanRead(totalswap,"KB",1)).arg(strswap)
                            .arg(toHumanRead(oldsbytes,"B",1)).arg(toHumanRead(tmps,"B",1))
                            .arg(toHumanRead(oldrbytes,"B",1)).arg(toHumanRead(tmpr,"B",1))
                            );

    return m_tipsWidget;
}

QWidget *SysMonitorPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    m_appletWidget->setText(QString("MEM:%1/%2=%3\nSWAP:%4/%5=%6\nUP:%7 %8/S\nDOWN:%9 %10/S")
                            .arg(toHumanRead(totalmem-availablemem,"KB",1)).arg(toHumanRead(totalmem,"KB",1)).arg(strmem)
                            .arg(toHumanRead(totalswap-freeswap,"KB",1)).arg(toHumanRead(totalswap,"KB",1)).arg(strswap)
                            .arg(toHumanRead(oldsbytes,"B",1)).arg(toHumanRead(tmps,"B",1))
                            .arg(toHumanRead(oldrbytes,"B",1)).arg(toHumanRead(tmpr,"B",1))
                            );
	
    return m_appletWidget;
}

bool SysMonitorPlugin::pluginIsAllowDisable()
{
    // 告诉 dde-dock 本插件允许禁用
    return true;
}

bool SysMonitorPlugin::pluginIsDisable()
{
    // 第二个参数 “disabled” 表示存储这个值的键（所有配置都是以键值对的方式存储的）
    // 第三个参数表示默认值，即默认不禁用
    return m_proxyInter->getValue(this, "disabled", false).toBool();
}

void SysMonitorPlugin::pluginStateSwitched()
{
    // 获取当前禁用状态的反值作为新的状态值
    const bool disabledNew = !pluginIsDisable();
    // 存储新的状态值
    m_proxyInter->saveValue(this, "disabled", disabledNew);

    // 根据新的禁用状态值处理主控件的加载和卸载
    if (disabledNew) {
        m_proxyInter->itemRemoved(this, pluginName());
    } else {
        m_proxyInter->itemAdded(this, pluginName());
    }
}

const QString SysMonitorPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(2);

    QMap<QString, QVariant> refresh;
    refresh["itemId"] = "refresh";
    refresh["itemText"] = "Refresh";
    refresh["isActive"] = true;
    items.push_back(refresh);

    QMap<QString, QVariant> open;
    open["itemId"] = "open";
    open["itemText"] = "Open system-monitor";
    open["isActive"] = true;
    items.push_back(open);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // 返回 JSON 格式的菜单数据
    return QJsonDocument::fromVariant(menu).toJson();
}

void SysMonitorPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);

    // 根据上面接口设置的 id 执行不同的操作
    if (menuId == "refresh") {
        
    } else if ("open") {
        QProcess::startDetached("deepin-system-monitor");
    }
}
