#include "teacher_work.h"
#include "ui_teacher_work.h"

teacher_work::teacher_work(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::teacher_work)
{
    ui->setupUi(this);
}


teacher_work::~teacher_work()
{
    delete ui;
}

void teacher_work::reshow()
{
    this->show();
}


void teacher_work::on_backButton_clicked()
{
    emit sendsignal();
    this->close();
}



void teacher_work::on_findstudentButton_clicked()
{
    this->hide();
    studata_display *db = new studata_display;
    connect(db,SIGNAL(sendsignal_2()),this,SLOT(reshow()));
    db->show();

}


void teacher_work::on_sendworkerButton_clicked()
{
    this->hide();
    teadata_display *db = new teadata_display;
    connect(db,SIGNAL(sendsignal_3()),this,SLOT(reshow()));
    db->show();
}

