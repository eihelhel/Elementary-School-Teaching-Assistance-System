#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    socket = new QTcpSocket;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_cancelButton_clicked()
{
    this->close();
}


void Widget::on_linkButton_clicked()
{
    QString IP = ui->iplineEdit->text();
    QString port = ui->portlineEdit->text();

    socket->connectToHost(QHostAddress(IP),port.toShort());

    connect(socket,&QTcpSocket::connected,[this]()
    {
        QMessageBox::information(this,"连接提示","连接成功");
        this->hide();
        teacher *s = new teacher(socket);
        s->show();
    });

    connect(socket,&QTcpSocket::disconnected,[this]()
    {
        QMessageBox::warning(this,"连接提示","连接异常 网络断开");
    });
}

