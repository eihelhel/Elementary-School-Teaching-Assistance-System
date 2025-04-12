#ifndef TEXT_ONE_H
#define TEXT_ONE_H

#include <QWidget>
#include <time.h>
#include<stdlib.h>
#include <function.h>

namespace Ui {
class text_one;
}

class text_one : public QWidget
{
    Q_OBJECT

public:
    explicit text_one(QWidget *parent = nullptr);
    ~text_one();


private slots:
    void on_ensureButton_clicked();

    void on_exitButton_clicked();

    void on_clearButton_clicked();

signals:
    void sendsignal_one();

private:
    Ui::text_one *ui;
    QString test_one;
    int valid;
    int a, c, d, m;
    double val;
};

#endif // TEXT_ONE_H
