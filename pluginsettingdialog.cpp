#include "pluginsettingdialog.h"
#include "ui_pluginsettingdialog.h"

pluginSettingDialog::pluginSettingDialog(Settings *settings,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pluginSettingDialog)
{
    ui->setupUi(this);
    if(settings->efficient==DisplayContentSetting::CPUMEM)ui->onlyCPUMEMRadioButton->setChecked(true);
    else if(settings->efficient==DisplayContentSetting::NETSPEED)ui->onlyNetSpeedRadioButton->setChecked(true);
    else ui->showAllRadioButton->setChecked(true);

    if(settings->fashion==DisplayContentSetting::CPUMEM)ui->fashionOnlyCPUMEMRadioButton->setChecked(true);
    else ui->fashionOnlyNetSpeedRadioButton->setChecked(true);

    ui->lineHeightSpinBox->setValue(settings->lineHeight);
    ui->fontSizeSpinBox->setValue(settings->fontSize);
    ui->fontColorComboBox->setCurrentIndex(settings->fontColor);
    ui->batInfoComboBox->setCurrentIndex(settings->batInfo);
}

pluginSettingDialog::~pluginSettingDialog()
{
    delete ui;
}

void pluginSettingDialog::getDisplayContentSetting(Settings *settings)
{
    if(ui->onlyCPUMEMRadioButton->isChecked())settings->efficient=DisplayContentSetting::CPUMEM;
    else if(ui->onlyNetSpeedRadioButton->isChecked())settings->efficient=DisplayContentSetting::NETSPEED;
    else settings->efficient=DisplayContentSetting::ALL;

    if(ui->fashionOnlyCPUMEMRadioButton->isChecked())settings->fashion=DisplayContentSetting::CPUMEM;
    else settings->fashion=DisplayContentSetting::NETSPEED;

    settings->lineHeight=ui->lineHeightSpinBox->value();
    settings->fontSize=ui->fontSizeSpinBox->value();
    settings->fontColor=ui->fontColorComboBox->currentIndex();
    settings->batInfo=ui->batInfoComboBox->currentIndex();
}
