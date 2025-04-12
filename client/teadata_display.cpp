#include "teadata_display.h"
#include "ui_teadata_display.h"

teadata_display::teadata_display(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::teadata_display)
{
    ui->setupUi(this);

    m = new QSqlTableModel;
    m->setTable("teachers");
    ui->tableView->setModel(m);
}

teadata_display::~teadata_display()
{
    delete ui;
}

void teadata_display::on_findButton_clicked()
{
    m->select();
}


void teadata_display::on_exitButton_clicked()
{
    emit sendsignal_3();
    this->hide();
}

