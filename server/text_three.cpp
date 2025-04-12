#include "text_three.h"
#include "ui_text_three.h"
#include "student_work.h"


text_three::text_three(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::text_three)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint); // 设置为独立窗口
    setWindowModality(Qt::ApplicationModal);
    rightCount = 0;
    count = 1;
    score = 0;
    rate = 0;
    ui->scorelabel->setText(QString("目前分数：%1").arg(score));
    ui->ratelabel->setText(QString("目前正确率：%1").arg(rate));
    srand(QTime::currentTime().second());
    valid = 1;
    a = Srand1();
    c = Srand2();
    d = a * c;
    ui->question->setText(QString("%1 * %2 =").arg(a).arg(c));
    // connect(this, SIGNAL(timeout()), this, SLOT(update()));
}

text_three::~text_three()
{
    delete ui;
}

void text_three::update()
{
    a = Srand1();
    c = Srand2();
    d = a * c;
    ui->question->setText(QString("%1 * %2 =").arg(a).arg(c));
}

void text_three::on_exitButton_clicked()
{
    emit sendsignal_three();
    this->close();
}

void text_three::on_ensureButton_clicked()
{
    test_three = ui->in_lineEdit->text();
    if(judg(test_three, valid))
    {
        val = test_three.toDouble();
        if(val == d)
        {
            QMessageBox::information(this,"答题提示","答案正确！");
            rightCount++;
            score = StatisticScore(rightCount);
            rate = StatisticRate(rightCount);
            ui->scorelabel->setText(QString("目前分数：%1").arg(score));
            ui->ratelabel->setText(QString("目前正确率：%1").arg(rate));
            emit updateScoreAndRate_1(score, rate);
        }
        else if(val != d)
        {
            QMessageBox::information(this,"答题提示","答案错误！");
        }
        if(count >= 10)
        {
            QMessageBox::information(this,"答题提示","答题已完成！分数与正确率请看学生试题界面！");
            emit sendsignal_three();
            this->close();
        }
        else
        {
            count++;  // 递增计数器
            update();
        }
    }
    else
    {
        QMessageBox::warning(this,"错误提示","格式错误！");
    }
}


void text_three::on_clearButton_clicked()
{
    ui->in_lineEdit->clear();
}

