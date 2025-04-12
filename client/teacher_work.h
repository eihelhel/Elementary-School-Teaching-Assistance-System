#ifndef TEACHER_WORK_H
#define TEACHER_WORK_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <studata_display.h>
#include <teadata_display.h>

namespace Ui {
class teacher_work;
}

class teacher_work : public QWidget
{
    Q_OBJECT

public:
    explicit teacher_work(QWidget *parent = nullptr);
    ~teacher_work();

typedef struct Teacher
{
    double id;
    QString name;
    QString sex;
    int age;
    QString job;
}Teacherlist;



private slots:
    void on_backButton_clicked();

    void reshow();

    void on_findstudentButton_clicked();

    void on_sendworkerButton_clicked();

signals:
    void sendsignal();

    void forwardTextToStudent(QString text); // 转发信号

private:
    Ui::teacher_work *ui;
};

#endif // TEACHER_WORK_H
