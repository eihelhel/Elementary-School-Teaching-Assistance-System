#ifndef STUDENT_WORK_H
#define STUDENT_WORK_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <text_one.h>
#include <text_two.h>
#include <text_three.h>
#include <text_four.h>
#include <text_five.h>

namespace Ui {
class student_work;
}

class student_work : public QWidget
{
    Q_OBJECT

public:
    explicit student_work(QWidget *parent = nullptr);
    ~student_work();
    Ui::student_work *ui;
    void resetScoreAndRate();


private slots:


    void updateUI(int newscore, double newrate);

    void reshow();

    void on_backButton_clicked();

    void on_text_one_Button_clicked();

    void on_text_two_Button_clicked();

    void on_text_three_Button_clicked();

    void on_text_four_Button_clicked();

    void on_text_five_Button_clicked();

signals:
    void sendsignal();

    void sendScoreAndRate(int s, double r);



private:
    int score;
    double rate;
    text_one *one;
    text_two *two;
    text_three *three;
    text_four *four;
    text_five *five;


};

#endif // STUDENT_WORK_H
