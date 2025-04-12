#include "student_work.h"
#include "ui_student_work.h"
#include "student.h"
#include "text_three.h"

student_work::student_work(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::student_work)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);

    score = 0;
    rate = 0.0;

    ui->scoreworklabel->setText(QString("目前分数：%1").arg(score));
    ui->rateworklabel->setText(QString("目前正确率：%1").arg(rate));

    one = new text_one();       // 无父对象
    two = new text_two();
    three = new text_three();
    connect(three, SIGNAL(updateScoreAndRate_1(int, double)), this, SLOT(updateUI(int, double)));
    four = new text_four();
    connect(four, SIGNAL(updateScoreAndRate_2(int, double)), this, SLOT(updateUI(int, double)));
    five = new text_five();
    connect(five, SIGNAL(updateScoreAndRate_3(int, double)), this, SLOT(updateUI(int, double)));

    connect(one,SIGNAL(sendsignal_one()),this,SLOT(reshow()));
    connect(two,SIGNAL(sendsignal_two()),this,SLOT(reshow()));
    connect(three,SIGNAL(sendsignal_three()),this,SLOT(reshow()));
    connect(four,SIGNAL(sendsignal_four()),this,SLOT(reshow()));
    connect(five,SIGNAL(sendsignal_five()),this,SLOT(reshow()));

    // linkthree = new text_three(this);

}

void student_work::resetScoreAndRate() {
    score = 0;
    rate = 0.0;
    ui->scoreworklabel->setText(QString("目前分数：%1").arg(score));
    ui->rateworklabel->setText(QString("目前正确率：%1").arg(rate));
}

student_work::~student_work()
{
    delete ui;
}

void student_work::reshow()
{
    this->show();
}

void student_work::updateUI(int newscore, double newrate) {
    score = newscore;
    rate = newrate;
    ui->scoreworklabel->setText(QString("目前分数：%1").arg(score));
    ui->rateworklabel->setText(QString("目前正确率：%1").arg(rate));
    emit sendScoreAndRate(score, rate); // 添加此行以实时发送信号
}

void student_work::on_backButton_clicked()
{
    emit sendsignal();                   // 发送返回信号
    this->close();
}

void student_work::on_text_one_Button_clicked()
{
    one->move(this->x() + 100, this->y() + 100);
    one->show();
    this->hide();
}

void student_work::on_text_two_Button_clicked()
{
    two->move(this->x() + 100, this->y() + 100);
    two->show();
    this->hide();
}


void student_work::on_text_three_Button_clicked()
{
    three->move(this->x() + 100, this->y() + 100);
    three->show();
    this->hide();
}


void student_work::on_text_four_Button_clicked()
{
    four->move(this->x() + 100, this->y() + 100);
    four->show();
    this->hide();
}


void student_work::on_text_five_Button_clicked()
{
    five->move(this->x() + 100, this->y() + 100);
    five->show();
    this->hide();
}

