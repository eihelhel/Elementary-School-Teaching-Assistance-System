#include "text_four.h"
#include "function.h"
#include "ui_text_four.h"

text_four::text_four(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::text_four)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    setWindowModality(Qt::ApplicationModal);
    rightCount = 0;
    count = 1;
    score = 0;
    rate = 0;
    ui->scorelabel->setText(QString("目前分数：%1").arg(score));
    ui->ratelabel->setText(QString("目前正确率：%1").arg(rate));
    srand(QTime::currentTime().second());
    valid = 1;
    p = '/';
    update();
}

text_four::~text_four()
{
    delete ui;
}

void text_four::update()
{
    do
    {
        a = Srand1();
        c = Srand2();
        click = switch_srand();
        temp = 0;
        switch(click)
        {
        case 0:
            temp = Division(p, c);
            if (temp == 1)
                break;
            ui->question->setText(QString("%1 / %2 =").arg(a).arg(c));
            s = static_cast<double>(a) / c;
            s = round(s * 100) / 100;//将除法计算值规范为保留两位小数位
            break;
        case 1:
            ui->question->setText(QString("%1 * %2 =").arg(a).arg(c));
            s = a * c;
            break;
        case 2:
            ui->question->setText(QString("%1 + %2 =").arg(a).arg(c));
            s = a + c;
            break;
        default:
            ui->question->setText(QString("%1 - %2 =").arg(a).arg(c));
            s = a - c;
        }
    }while(temp==1);
}

void text_four::on_exitButton_clicked()
{
    emit sendsignal_four();
    this->close();
}


void text_four::on_ensureButton_clicked()
{
    test_four = ui->in_lineEdit->text();
    if(judg(test_four, valid))
    {
        val = test_four.toDouble();
        if(val == s)
        {
            QMessageBox::information(this,"答题提示","答案正确！");
            rightCount++;
            score = StatisticScore(rightCount);
            rate = StatisticRate(rightCount);
            ui->scorelabel->setText(QString("目前分数：%1").arg(score));
            ui->ratelabel->setText(QString("目前正确率：%1").arg(rate));
            emit updateScoreAndRate_2(score, rate);
        }
        else if(val != s)
        {
            QMessageBox::information(this,"答题提示","答案错误！");
        }
        if(count >= 10)
        {
            QMessageBox::information(this,"答题提示","答题已完成！分数与正确率请看学生试题界面！");
            emit sendsignal_four();
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


void text_four::on_clearButton_clicked()
{
    ui->in_lineEdit->clear();
}

