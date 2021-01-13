#include "okno.h"
#include "ui_okno.h"
#include <QMessageBox>



okno::okno(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::okno)
{
    ui->setupUi(this);
}

okno::~okno()
{
    delete ui;
}

void okno::on_pushButton_clicked()
{
    QString name = ui->login->text();
     name.replace(' ', '_');

    QMessageBox::information(this, "спасибо", name);
}

