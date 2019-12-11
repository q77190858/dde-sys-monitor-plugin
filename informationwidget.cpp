#include "informationwidget.h"
#include <QVBoxLayout>
#include <QDebug>

InformationWidget::InformationWidget(QWidget *parent)
    : QWidget(parent)
    , m_infoLabel(new QLabel)
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

void InformationWidget::UpdateDataCpuMem(const QString &cpu, const QString &mem)
{
    m_infoLabel->setText(QString("CPU:%1\nMEM:%3")
                         .arg(cpu)
                         .arg(mem));
}

void InformationWidget::UpdateDataAll(const QString &cpu,const QString &mem,const QString &sbytes,const QString &rbytes)
{
	m_infoLabel->setText(QString("CPU:%1↑%2/S\nMEM:%3↓%4/S")
						 .arg(cpu).arg(sbytes)
						 .arg(mem).arg(rbytes));
}

void InformationWidget::UpdateDataNetSpeed(const QString &sbytes,const QString &rbytes)
{
    m_infoLabel->setText(QString("↑%1/S\n↓%2/S")
						 .arg(sbytes)
						 .arg(rbytes));
}
