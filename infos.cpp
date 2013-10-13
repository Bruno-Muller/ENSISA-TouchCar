#include "infos.h"
#include "ui_infos.h"

Infos::Infos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Infos)
{
    ui->setupUi(this);
}

Infos::~Infos()
{
    delete ui;
}
