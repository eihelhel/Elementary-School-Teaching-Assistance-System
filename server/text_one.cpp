#include "text_one.h"
#include "ui_text_one.h"


text_one::text_one(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::text_one)
{
    ui->setupUi(this);
    valid = 1;
    a = Srand1();
    c = Srand2();
    d = a * c;
    ui->question->setText(QString("%1 * %2 =").arg(a).arg(c));

}

text_one::~text_one()
{
    delete ui;
}

void text_one::on_ensureButton_clicked()
{
    test_one = ui->in_lineEdit->text();
    if(judg(test_one, valid))
    {
        val = test_one.toDouble();
        if(val == d)
        {
            QMessageBox::information(this,"答题提示","答案正确！");
            emit sendsignal_one();
            this->close();
        }
        if(val != d)
        {
            QMessageBox::information(this,"答题提示","答案错误！");
        }
    }
    else
    {
        QMessageBox::warning(this,"错误提示","格式错误！");
    }
}

void text_one::on_exitButton_clicked()
{
    emit sendsignal_one();
    this->close();
}


void text_one::on_clearButton_clicked()
{
    ui->in_lineEdit->clear();
}

