#include "teacher.h"
#include "ui_teacher.h"

teacher::teacher(QTcpSocket *s, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::teacher)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setDatabaseName("student_db");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("password");

    if(db.open())
    {
        QMessageBox::information(this,"数据库连接提示","数据库连接成功");
    }
    else
    {
        QMessageBox::warning(this,"数据库连接提示","数据库连接失败");
    }
}

teacher::~teacher()
{
    delete ui;
}

struct Teacher
{
    double id;
    QString name;
    QString sex;
    int age;
    QString job;
}Teacherlist;

void teacher::reshow()
{
    this->show();
}

void teacher::on_getButton_clicked()
{
    QString idStr = ui->idEdit->text().trimmed();
    QString nameStr = ui->nameEdit->text().trimmed();
    QString sexStr = ui->sexEdit->text().trimmed();
    QString ageStr = ui->ageEdit->text().trimmed();
    QString jobStr = ui->jobEdit->text().trimmed();
    bool isValid = true;
    QStringList errorMessages;
    // 验证编号
    if (idStr.isEmpty()) {
        errorMessages.append("编号不能为空");
        isValid = false;
    } else {
        bool conversionOk;
        idStr.toDouble(&conversionOk);
        if (!conversionOk) {
            errorMessages.append("编号必须为数字");
            isValid = false;
        } else {
            Teacherlist.id = idStr.toDouble();
        }
    }
    // 验证姓名
    if (nameStr.isEmpty()) {
        errorMessages.append("姓名不能为空");
        isValid = false;
    }
    // 验证性别
    if (sexStr.isEmpty()) {
        errorMessages.append("性别不能为空");
        isValid = false;
    } else if (sexStr != "男" && sexStr != "女") {
        errorMessages.append("性别必须为男或女");
        isValid = false;
    }
    // 验证年龄
    if (ageStr.isEmpty()) {
        errorMessages.append("年龄不能为空");
        isValid = false;
    } else {
        bool conversionOk;
        ageStr.toInt(&conversionOk);
        if (!conversionOk) {
            errorMessages.append("年龄必须为整数");
            isValid = false;
        } else if (ageStr.toInt() < 0) {
            errorMessages.append("年龄不能为负数");
            isValid = false;
        } else {
            Teacherlist.age = ageStr.toInt();
        }
    }
    // 验证职称
    if (jobStr.isEmpty()) {
        errorMessages.append("职称不能为空");
        isValid = false;
    }

    if (isValid) {
        Teacherlist.name = nameStr;
        Teacherlist.sex = sexStr;
        Teacherlist.job = jobStr;
        QString sql = QString("INSERT INTO teachers (tid ,tname, tsex, tage, tjob) VALUES ( %1, '%2', '%3', %4, '%5');").arg(Teacherlist.id)
                          .arg(Teacherlist.name).arg(Teacherlist.sex).arg(Teacherlist.age).arg(Teacherlist.job);
        QSqlQuery query;
        if(query.exec(sql))
        {
            QMessageBox::information(this,"录入数据库提示","数据库录入成功");
        }
        this->hide();
        teacher_work *s = new teacher_work;
        connect(s,SIGNAL(sendsignal()),this,SLOT(reshow()));
        s->show();
    } else {
        QMessageBox::warning(this, "输入错误", errorMessages.join('\n'));
    }
}


void teacher::on_cancelButton_clicked()
{
    this->close();
}

