#include "text_five.h"
#include "ui_text_five.h"

text_five::text_five(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::text_five)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    setWindowModality(Qt::ApplicationModal);

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

text_five::~text_five()
{
    delete ui;
}

void text_five::update()
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
            s = round(t * 100) / 100;//将除法计算值规范为保留两位小数位
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

void text_five::on_exitButton_clicked()
{
    emit sendsignal_five();
    this->close();
}


void text_five::on_ensureButton_clicked()
{
    test_five = ui->in_lineEdit->text();
    if(judg(test_five, valid))
    {
        val = test_five.toDouble();
        if(val == s)
        {
            QMessageBox::information(this,"答题提示","答案正确！");
            rightCount++;
            // score = StatisticScore(rightCount);
            rate = StatisticRate(rightCount);
            // ui->scorelabel->setText(QString("目前分数：%1").arg(score));
            ui->ratelabel->setText(QString("目前正确率：%1").arg(rate));
            emit updateScoreAndRate_3(score, rate);
        }
        else if(val != s)
        {
            QMessageBox::information(this,"答题提示","答案错误！");
        }
        if(count >= 10)
        {
            if(rate <= 0.75)
            {
                count = 0;
            }
            else
            {
                QMessageBox::information(this,"答题提示","答题已完成！正确率请看学生试题界面！");
                emit sendsignal_five();
                this->close();
            }
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


void text_five::on_clearButton_clicked()
{
    ui->in_lineEdit->clear();
}

