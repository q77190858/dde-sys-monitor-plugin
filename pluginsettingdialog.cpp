#include "pluginsettingdialog.h"
#include "ui_pluginsettingdialog.h"

pluginSettingDialog::pluginSettingDialog(DisplayContentSetting efficient,DisplayContentSetting fashion,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pluginSettingDialog)
{
    ui->setupUi(this);
    if(efficient==DisplayContentSetting::CPUMEM)ui->onlyCPUMEMRadioButton->setChecked(true);
    else if(efficient==DisplayContentSetting::NETSPEED)ui->onlyNetSpeedRadioButton->setChecked(true);
    else ui->showAllRadioButton->setChecked(true);

    if(fashion==DisplayContentSetting::CPUMEM)ui->fashionOnlyCPUMEMRadioButton->setChecked(true);
    else ui->fashionOnlyNetSpeedRadioButton->setChecked(true);
}

pluginSettingDialog::~pluginSettingDialog()
{
    delete ui;
}

void pluginSettingDialog::getDisplayContentSetting(DisplayContentSetting *efficient, DisplayContentSetting *fashion)
{
    if(ui->onlyCPUMEMRadioButton->isChecked())*efficient=DisplayContentSetting::CPUMEM;
    else if(ui->onlyNetSpeedRadioButton->isChecked())*efficient=DisplayContentSetting::NETSPEED;
    else *efficient=DisplayContentSetting::ALL;

    if(ui->fashionOnlyCPUMEMRadioButton->isChecked())*fashion=DisplayContentSetting::CPUMEM;
    else *fashion=DisplayContentSetting::NETSPEED;
}
