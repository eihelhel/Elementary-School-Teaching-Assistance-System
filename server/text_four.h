#ifndef TEXT_FOUR_H
#define TEXT_FOUR_H

#include <QWidget>
#include<stdlib.h>
#include <cmath>
#include <function.h>

namespace Ui {
class text_four;
}

class text_four : public QWidget
{
    Q_OBJECT

public:
    explicit text_four(QWidget *parent = nullptr);
    ~text_four();

signals:
    void sendsignal_four();

    void updateScoreAndRate_2(int score, double rate);

private slots:
    void update();

    void on_exitButton_clicked();

    void on_ensureButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::text_four *ui;
    int rightCount = 0;
    QString test_four;
    int valid;
    int count,temp;
    int a, c, d, m;
    int click;
    char p;
    double val, rate, s, t;
    int score;
};

#endif // TEXT_FOUR_H
