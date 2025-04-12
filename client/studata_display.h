#ifndef STUDATA_DISPLAY_H
#define STUDATA_DISPLAY_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDir>
#include <QStandardPaths>


namespace Ui {
class studata_display;
}

class studata_display : public QWidget
{
    Q_OBJECT

public:
    explicit studata_display(QWidget *parent = nullptr);
    ~studata_display();

private slots:
    void on_exitButton_clicked();

    // void on_findButton_clicked();

    void on_sortFieldChanged(int index);  // 新增：处理字段选择变化

    void on_sortOrderChanged(int index);

    void on_saveButton_clicked();

signals:
    void sendsignal_2();

private:
    Ui::studata_display *ui;
    QSqlTableModel *m;
    QMap<QString, QString> m_fieldMap;
    int m_currentSortColumn;       // 新增：当前排序字段的列索引
    Qt::SortOrder m_currentOrder;
};

#endif // STUDATA_DISPLAY_H
