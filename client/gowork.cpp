#include "gowork.h"
#include "ui_gowork.h"

gowork::gowork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gowork)
{
    ui->setupUi(this);

}

gowork::~gowork()
{
    delete ui;
}

void gowork::on_closeButton_clicked()
{
    emit sendsingal();
    this->hide();
}

void gowork::on_clearButton_clicked()
{
    ui->textlineEdit->clear();
}

void gowork::on_sendButton_clicked()
{
    QString inputText = ui->textlineEdit->text();
    QTcpSocket *socket = new QTcpSocket(this);
    // socket->connectToHost("127.0.0.1", 8000); // 学生端监听的端口
    // if (socket->waitForConnected()) {
        socket->write(inputText.toUtf8());
        socket->flush();
    // }
    ui->textlineEdit->clear();
}

