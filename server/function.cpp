#include "function.h"
#include <cstdlib>

function::function() {}

QRandomGenerator randomGenerator;

int Srand1()//产生1~9随机数，且返回此数
{
    srand(QTime::currentTime().second());
    int randomInRange1 = randomGenerator.bounded(1, 10);
    return randomInRange1;
}

int Srand2()
{
    srand(QTime::currentTime().second());
    int randomInRange2= randomGenerator.bounded(1, 10);
    return randomInRange2;
}

int switch_srand()
{
    int randomNumber = rand();
    return randomNumber % 4;
}

int Division(char b, double c)
{
    int temp;
    temp = 0;
    if(b == '/' && c == 0)
    {
        temp = 1;
    }
    return temp;
}

int judg(QString s, int valid)
{
    char *ch;
    int i, h;
    int count, sign;
    QByteArray ba = s.toLatin1();
    ch = ba.data();
    count = 0;
    sign = 0;
    h = strlen(ch);
    if(h == 0)//检查空字符串
    {
        valid = 0;
    }
    for(i = 0; i < h && valid; i++)
    {
        if(i == 0 && (s[i] == '+' || s[i] == '-'))//允许首字符为符号
        {
            sign = 1;
            continue;
        }

        if(s[i] == '.')//统计小数点数量
        {
            count++;
            if(count > 1)//禁止多个小数点
            {
                valid = 0;
                break;
            }
        }
        else if(!(s[i] >= '0' && s[i] <= '9'))//检查是否为数字
        {
            valid = 0;
            break;
        }
    }
    if(valid)//检查无效格式（如 "-", ".", "123.", "-.5" 等）
    {
        if (sign && h == 1) valid = 0;                //只有符号（如 "-"）
        else if (count == 1 && h == 1) valid = 0;  //只有小数点（如 "."）
        else if (count == 1 && s[h-1] == '.') valid = 0; //结尾是小数点（如 "12."）
        else return 1;
    }
    if(!valid)
    {
        return 0;
    }
}

int StatisticScore(int c)//统计并返回答题的分数
{
    int x;
    x = c * 10;
    return x;
}

double StatisticRate(double c)//计算并返回答题的正确率
{
    double y;
    y = c/10;
    return y;
}

QString stage(double v, int precision) //precision为需要保留的精度，2位小数变为2
{
    return (v >= 0.00 ? QString::number(v, 'f', precision) : "");
}

