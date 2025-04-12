#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#include <QMessageBox>
#include <QByteArray>
#include <QTime>
#include <QRandomGenerator>

class function
{
public:
    function();
};

// extern int rightCount;

int Srand1();

int Srand2();

int switch_srand();

int Division(char b, double c);

int judg(QString s, int valid);

int StatisticScore(int c);

double StatisticRate(double c);

void pending(int s, int flag);

QString stage(double v, int precision);

#endif // FUNCTION_H
