#include "studata_display.h"
#include "ui_studata_display.h"

studata_display::studata_display(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::studata_display)
{
    ui->setupUi(this);

    ui->fieldComboBox->setCurrentIndex(0);    // 默认选中“学号”
    ui->orderComboBox->setCurrentIndex(0);

    m = new QSqlTableModel;
    m->setTable("students");
    ui->tableView->setModel(m);
    m_fieldMap["学号"] = "sid";
    m_fieldMap["姓名"] = "sname";
    m_fieldMap["分数"] = "sscore";

    m_currentSortColumn = m->fieldIndex("sid"); // 默认按学号排序
    m_currentOrder = Qt::AscendingOrder;

    connect(ui->fieldComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_sortFieldChanged(int)));
    connect(ui->orderComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_sortOrderChanged(int)));
}

studata_display::~studata_display()
{
    delete ui;
}

void studata_display::on_exitButton_clicked()
{
    emit sendsignal_2();
    this->hide();
}

void studata_display::on_sortFieldChanged(int index) {
    QString fieldName = ui->fieldComboBox->itemText(index);
    QString dbField = m_fieldMap[fieldName];
    m_currentSortColumn = m->fieldIndex(dbField); // 更新当前排序字段
    m->sort(m_currentSortColumn, m_currentOrder); // 调用排序
    m->select();
}

// 处理排序方式变化
void studata_display::on_sortOrderChanged(int index) {
    m_currentOrder = (index == 0) ? Qt::AscendingOrder : Qt::DescendingOrder; // 更新排序顺序
    m->sort(m_currentSortColumn, m_currentOrder); // 调用排序
    m->select();
}

void studata_display::on_saveButton_clicked() {
    // 获取桌面路径（兼容不同系统）
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    if (desktopPath.isEmpty()) {
        QMessageBox::warning(this, tr("错误"), tr("无法获取桌面路径！"));
        return;
    }

    // 构建完整文件路径
    QString fileName = desktopPath + "/students_data.txt";

    // 打开文件（覆盖模式）
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("文件打开失败：%1").arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);  // 确保中文正常

    // 写入表头（使用制表符分隔）
    QStringList headers;
    for (int col = 0; col < m->columnCount(); ++col) {
        headers << m->headerData(col, Qt::Horizontal).toString();
    }
    out << headers.join("\t") << "\n";

    // 遍历数据行
    for (int row = 0; row < m->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < m->columnCount(); ++col) {
            QModelIndex index = m->index(row, col);
            rowData << m->data(index).toString();
        }
        out << rowData.join("\t") << "\n";
    }

    file.close();
    QMessageBox::information(this, tr("保存成功"), tr("数据已保存至：\n%1").arg(fileName));
}

