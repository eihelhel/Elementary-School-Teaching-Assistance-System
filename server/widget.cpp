#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new QTcpServer;

    server->listen(QHostAddress::AnyIPv4,PORT);

    connect(server,&QTcpServer::newConnection,this,&Widget::newClientHandler);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newClientHandler()
{
    QTcpSocket *socket = server->nextPendingConnection();

    socket->peerAddress();
    socket->peerPort();

    ui->iplineEdit->setText(socket->peerAddress().toString());
    ui->portlineEdit->setText(QString::number(socket->peerPort()));

    this->hide();
    student *s = new student;
    s->show();
}
