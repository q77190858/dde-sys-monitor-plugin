#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QScreen>
#include <QApplication>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    m_infoLabel1(new QLabel),m_infoLabel2(new QLabel)
{
//    ui->m_infoLabel->setStyleSheet("QLabel {"
//                               "color: #000;"
//                               "}");
    m_infoLabel1->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    m_infoLabel2->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    font.setFamily("Noto Mono");
    // 获取dpi，一般默认都是96，根据dpi进行字体的缩放，直接设置pointsize无法解决hidpi问题
    dpi = QApplication::primaryScreen()->logicalDotsPerInch();
    int fontsize = 9; // >10在时尚模式下有些显示不全
    font.setPixelSize((dpi*fontsize)/72);
    m_infoLabel1->setFont(font);
    m_infoLabel2->setFont(font);

    centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_infoLabel1);
    centralLayout->addWidget(m_infoLabel2);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setLayout(centralLayout);
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::UpdateData(const Info &info, Dock::DisplayMode dismode, const Settings &settings)
{
    font.setPixelSize((dpi*settings.fontSize)/72);
    m_infoLabel1->setFont(font);
    m_infoLabel2->setFont(font);
    QString style=QString("QLabel {color: %1;}").arg(settings.fontColor==0?"#fff":"#000");
    m_infoLabel1->setStyleSheet(style);
    m_infoLabel2->setStyleSheet(style);
    m_infoLabel1->setFixedHeight(settings.lineHeight);
    m_infoLabel2->setFixedHeight(settings.lineHeight);

    if(dismode==Dock::Efficient)//高效模式
    {
        switch (settings.efficient) {
        case DisplayContentSetting::CPUMEM:
            m_infoLabel1->setText(QString("CPU:%1").arg(info.cpu));
            m_infoLabel2->setText(QString("MEM:%1").arg(info.mem));
            break;
        case DisplayContentSetting::NETSPEED:
            m_infoLabel1->setText(QString("↑%1/S").arg(info.netup));
            m_infoLabel2->setText(QString("↓%1/S").arg(info.netdwon));
            break;
        case DisplayContentSetting::ALL:
            m_infoLabel1->setText(QString("CPU:%1↑%2/S").arg(info.cpu).arg(info.netup));
            m_infoLabel2->setText(QString("MEM:%1↓%2/S").arg(info.mem).arg(info.netdwon));
            break;
        default:
            m_infoLabel1->setText(QString("CPU:%1↑%2/S").arg(info.cpu).arg(info.netup));
            m_infoLabel2->setText(QString("MEM:%1↓%2/S").arg(info.mem).arg(info.netdwon));
            break;
        }
    }
    else//时尚模式
    {
        switch (settings.fashion) {
        case DisplayContentSetting::CPUMEM:
            m_infoLabel1->setText(QString("CPU:%1").arg(info.cpu));
            m_infoLabel2->setText(QString("MEM:%1").arg(info.mem));
            break;
        case DisplayContentSetting::NETSPEED:
            m_infoLabel1->setText(QString("↑%1/S").arg(info.netup));
            m_infoLabel2->setText(QString("↓%1/S").arg(info.netdwon));
            break;
        default:
            m_infoLabel1->setText(QString("↑%1/S").arg(info.netup));
            m_infoLabel2->setText(QString("↓%1/S").arg(info.netdwon));
            break;
        }
    }
}
