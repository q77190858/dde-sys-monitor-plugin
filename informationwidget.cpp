#include "informationwidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QScreen>
#include <QApplication>

InformationWidget::InformationWidget(QWidget *parent)
    : QWidget(parent)
    , m_infoLabel(new QLabel)
{
    m_infoLabel->setStyleSheet("QLabel {"
                               "color: white;"
                               "}");
    //m_infoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    font.setFamily("Noto Mono");
    // 获取dpi，一般默认都是96，根据dpi进行字体的缩放，直接设置pointsize无法解决hidpi问题
    int dpi = QApplication::primaryScreen()->logicalDotsPerInch();
    int fontsize = 9; // >10在时尚模式下有些显示不全
    font.setPixelSize((dpi*fontsize)/72);
	m_infoLabel->setFont(font);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_infoLabel);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setLayout(centralLayout);
}

void InformationWidget::UpdateData(const Info& info,Dock::DisplayMode dismode,const Settings& settings)
{
    if(dismode==Dock::Efficient)//高效模式
    {
        switch (settings.efficient) {
        case DisplayContentSetting::CPUMEM:
            m_infoLabel->setText(QString("<p style='line-height:%1%'>CPU:%2<br/>MEM:%3</p>")
                                 .arg(settings.lineHeight)
                                 .arg(info.cpu)
                                 .arg(info.mem));
            break;
        case DisplayContentSetting::NETSPEED:
            m_infoLabel->setText(QString("<p style='line-height:%1%'>↑%2/S<br/>↓%3/S</p>")
                                 .arg(settings.lineHeight)
                                 .arg(info.netup)
                                 .arg(info.netdwon));
            break;
        case DisplayContentSetting::ALL:
            m_infoLabel->setText(QString("<p style='line-height:%1%'>CPU:%2↑%3/S<br/>MEM:%4↓%5/S</p>")
                                 .arg(settings.lineHeight)
                                 .arg(info.cpu).arg(info.netup)
                                 .arg(info.mem).arg(info.netdwon));
            break;
        default:
            m_infoLabel->setText(QString("<p style='line-height:%1%'>CPU:%2↑%3/S<br/>MEM:%4↓%5/S</p>")
                                 .arg(settings.lineHeight)
                                 .arg(info.cpu).arg(info.netup)
                                 .arg(info.mem).arg(info.netdwon));
            break;
        }
    }
    else//时尚模式
    {
        switch (settings.fashion) {
        case DisplayContentSetting::CPUMEM:
            m_infoLabel->setText(QString("<p style='line-height:%1%'>CPU:%2<br/>MEM:%3</p>")
                                 .arg(settings.lineHeight)
                                 .arg(info.cpu)
                                 .arg(info.mem));
            break;
        case DisplayContentSetting::NETSPEED:
            m_infoLabel->setText(QString("<p style='line-height:%1%'>↑%2/S<br/>↓%3/S</p>")
                                 .arg(settings.lineHeight)
                                 .arg(info.netup)
                                 .arg(info.netdwon));
            break;
        default:
            m_infoLabel->setText(QString("<p style='line-height:%1%'>↑%2/S<br/>↓%3/S</p>")
                                 .arg(settings.lineHeight)
                                 .arg(info.netup)
                                 .arg(info.netdwon));
            break;
        }
    }
}
