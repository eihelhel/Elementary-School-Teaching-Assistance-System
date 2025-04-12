#ifndef TEADATA_DISPLAY_H
#define TEADATA_DISPLAY_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class teadata_display;
}

class teadata_display : public QWidget
{
    Q_OBJECT

public:
    explicit teadata_display(QWidget *parent = nullptr);
    ~teadata_display();

signals:
    void sendsignal_3();

private slots:
    void on_findButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::teadata_display *ui;
    QSqlTableModel *m;
};

#endif // TEADATA_DISPLAY_H
