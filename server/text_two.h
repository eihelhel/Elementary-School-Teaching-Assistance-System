#ifndef TEXT_TWO_H
#define TEXT_TWO_H

#include <QWidget>
#include<stdlib.h>
#include <cmath>
#include <function.h>

namespace Ui {
class text_two;
}

class text_two : public QWidget
{
    Q_OBJECT

public:
    explicit text_two(QWidget *parent = nullptr);
    ~text_two();

signals:
    void sendsignal_two();

private slots:
    void on_ensureButton_clicked();

    void on_exitButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::text_two *ui;
    QString test_two, s_num, division;
    int flag,count,temp;
    char p;
    int valid;
    int d, m, click;
    double a, c, s, e;
    double val;
};

#endif // TEXT_TWO_H
