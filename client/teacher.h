#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include <QTcpSocket>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include <QMessageBox>
#include <teacher_work.h>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>

namespace Ui {
class teacher;
}

class teacher : public QWidget
{
    Q_OBJECT

public:
    explicit teacher(QTcpSocket *s, QWidget *parent = nullptr);
    ~teacher();

private slots:

    void on_getButton_clicked();

    void reshow();

    void on_cancelButton_clicked();

private:
    Ui::teacher *ui;
    QTcpSocket *socket;
    QString expression;
    teacher_work *teacherlist;
    QSqlDatabase db;
};

#endif // TEACHER_H
