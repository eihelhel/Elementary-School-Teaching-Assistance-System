#include "text_two.h"
#include "ui_text_two.h"

text_two::text_two(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::text_two)
{
    ui->setupUi(this);

    valid = 1;
    flag = 0;
    count = 0;
    s_num = QString::number(count);
    ui->countlabel->setText(s_num);
    p = '/';
    a = Srand1();
    c = Srand2();
    click = switch_srand();
    do
    {
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

text_two::~text_two()
{
    delete ui;
}


void text_two::on_ensureButton_clicked()
{
    test_two = ui->in_lineEdit->text();
    if(judg(test_two, valid))
    {
        val = test_two.toDouble();
        if(val == s)
        {
            QMessageBox::information(this,"答题提示","答案正确！");
            emit sendsignal_two();
            this->close();
        }
        if(val != s)
        {

            count++;
            s_num = QString::number(count);
            ui->countlabel->setText(QString("你还有 %1 次机会").arg(4-count));
            if (count != 4)
            {
                QMessageBox::information(this,"答题提示",QString("答案错误！你还有 %1 次机会").arg(4-count));
            }
            else
            {
                QMessageBox::warning(this,"答题提示","答案错误！");
                emit sendsignal_two();
                this->close();
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"错误提示","格式错误！");
    }
}

void text_two::on_exitButton_clicked()
{
    emit sendsignal_two();
    this->close();
}


void text_two::on_clearButton_clicked()
{
    ui->in_lineEdit->clear();
}

