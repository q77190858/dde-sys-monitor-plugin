#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
}

aboutDialog::~aboutDialog()
{
    delete ui;
}

void aboutDialog::on_blogPushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://blog.mxslly.com"));
}

void aboutDialog::on_giteePushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://gitee.com/q77190858/dde-sys-monitor-plugin"));
}

void aboutDialog::on_githubPushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/q77190858/dde-sys-monitor-plugin"));
}
