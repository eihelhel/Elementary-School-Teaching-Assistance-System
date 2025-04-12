#ifndef TEXT_FIVE_H
#define TEXT_FIVE_H

#include <QWidget>
#include<stdlib.h>
#include <function.h>
#include <cmath>

namespace Ui {
class text_five;
}

class text_five : public QWidget
{
    Q_OBJECT

public:
    explicit text_five(QWidget *parent = nullptr);
    ~text_five();

signals:
    void sendsignal_five();

    void updateScoreAndRate_3(int score, double rate);

private slots:
    void update();

    void on_exitButton_clicked();

    void on_ensureButton_clicked();

    void on_clearButton_clicked();

private:
    int rightCount = 0;
    Ui::text_five *ui;
    QString test_five;
    int valid;
    int count,temp;
    int a, c, d, m;
    int click;
    char p;
    double val, rate, s, t;
    int score;
};

#endif // TEXT_FIVE_H
