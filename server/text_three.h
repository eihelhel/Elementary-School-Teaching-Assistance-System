#ifndef TEXT_THREE_H
#define TEXT_THREE_H

#include <QWidget>
#include <time.h>
#include<stdlib.h>
#include <function.h>
#include <QTimer>


namespace Ui {
class text_three;
}

class text_three : public QWidget
{
    Q_OBJECT

public:
    explicit text_three(QWidget *parent = nullptr);
    ~text_three();

signals:
    void sendsignal_three();

    void updateScoreAndRate_1(int score, double rate);

private slots:
    void update();

    void on_exitButton_clicked();

    void on_ensureButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::text_three *ui;
    int rightCount = 0;
    QString test_three;
    int valid;
    int a, c, d, m, count;
    double val, rate;
    int score;

};

#endif // TEXT_THREE_H
