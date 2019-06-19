#include "informationwidget.h"

#include <QVBoxLayout>
#include <QDebug>

InformationWidget::InformationWidget(QWidget *parent)
    : QWidget(parent)
    , m_infoLabel(new QLabel)
    // 使用 "/home" 初始化 QStorageInfo
    // 如果 "/home" 没有挂载到一个单独的分区上，QStorageInfo 收集的数据将会是根分区的
{
    m_infoLabel->setStyleSheet("QLabel {"
                               "color: white;"
                               "}");
    //m_infoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    font.setFamily("Noto Mono");
	m_infoLabel->setFont(font);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_infoLabel);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setLayout(centralLayout);
}

void InformationWidget::UpdateData(const QString &cpu,const QString &mem,const QString &sbytes,const QString &rbytes)
{
	m_infoLabel->setText(QString("CPU:%1↑%2/S\nMEM:%3↓%4/S")
						 .arg(cpu).arg(sbytes)
						 .arg(mem).arg(rbytes));
}
