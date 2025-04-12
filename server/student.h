#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include <QTcpSocket>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include <QMessageBox>
#include <student_work.h>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>


namespace Ui {
class student;
}

class student : public QWidget
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = nullptr);
    ~student();
    Ui::student *ui;
    struct Student//定义一个链表数据类型
    {
        double id;//学号
        QString name;//姓名
        QString sex;//性别
        int testscore = 0;//分数
        double testrate = 0;//正确率
    }Studentlist;
    // student_work *linkstu_work;

private slots:
    void on_getButton_clicked();

    void updateScore(int score, double rate);

    void reshow();

    void on_cancelButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QSqlDatabase db;
    student_work *s_w;
};

#endif // STUDENT_H
