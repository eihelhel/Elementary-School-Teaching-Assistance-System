#ifndef GOWORK_H
#define GOWORK_H

#include <QWidget>
#include <QTableWidget>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include <QMessageBox>
#include <QTcpSocket>

namespace Ui {
class gowork;
}

class gowork : public QWidget
{
    Q_OBJECT

public:
    explicit gowork(QWidget *parent = nullptr);
    ~gowork();

private slots:
    void on_closeButton_clicked();

    void on_clearButton_clicked();

    void on_sendButton_clicked();

signals:
    void sendsingal();

    void sendText(QString text); // 新增信号

    void goto_studentsingal();   // 原有信号

    void sendTextToStudent(QString text); // 新增信号

private:
    Ui::gowork *ui;
    QString *s;
};

#endif // GOWORK_H
