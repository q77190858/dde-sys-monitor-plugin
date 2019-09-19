#include "informationwidget.h"

#include <QScreen>
#include <QApplication>
#include <QVBoxLayout>
#include <QDebug>

#include <QMessageBox>

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

void InformationWidget::UpdateData(const QString &cpu,const QString &mem,const QString &sbytes,const QString &rbytes)
{
    m_infoLabel->setText(QString("CPU:%1 ↑%2/S\nMEM:%3 ↓%4/S")
                         .arg(cpu).arg(sbytes)
                         .arg(mem).arg(rbytes));
	//m_infoLabel->adjustSize();
}

void InformationWidget::UpdateData(const QString &sbytes,const QString &rbytes)
{
	m_infoLabel->setText(QString("%1/S\n%2/S")
						 .arg(sbytes)
						 .arg(rbytes));
}
