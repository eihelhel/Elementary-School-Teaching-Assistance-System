#include "student.h"
#include "ui_student.h"
#include "student_work.h"
#include "ui_student_work.h"

student::student(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::student),
    s_w(new student_work())
{
    ui->setupUi(this);
    connect(s_w, SIGNAL(sendScoreAndRate(int, double)), this, SLOT(updateScore(int, double)));
    connect(s_w, SIGNAL(sendsignal()), this, SLOT(reshow()));
    // linkstu_work = new student_work(this);


    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setDatabaseName("student_db");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("password");

    db.open();
}

student::~student()
{
    delete s_w;
    delete ui;
}

void student::reshow()
{
    this->show();
}

void student::on_getButton_clicked()
{
    QString idStr = ui->idlineEdit->text().trimmed();
    QString nameStr = ui->namelineEdit->text().trimmed();
    QString sexStr = ui->sexlineEdit->text().trimmed();
    bool isValid = true;
    QStringList errorMessages;
    // 验证学号
    if (idStr.isEmpty())
    {
        errorMessages.append("学号不能为空");
        isValid = false;
    }
    else
    {
        bool conversionOk;
        idStr.toDouble(&conversionOk);
        if (!conversionOk) {
            errorMessages.append("学号必须为数字");
            isValid = false;
        } else {
            Studentlist.id= idStr.toDouble();
        }
    }
    // 验证姓名
    if (nameStr.isEmpty())
    {
        errorMessages.append("姓名不能为空");
        isValid = false;
    }
    // 验证性别
    if (sexStr.isEmpty())
    {
        errorMessages.append("性别不能为空");
        isValid = false;
    }
    else if (sexStr != "男" && sexStr != "女")
    {
        errorMessages.append("性别必须为男或女");
        isValid = false;
    }

    if (isValid)
    {
        Studentlist.name = nameStr;
        Studentlist.sex = sexStr;
        QMessageBox::information(this,"学生登录提示","学生登录成功");
        // student_work *s_w = new student_work();
        // connect(s_w, SIGNAL(sendsignal()), this, SLOT(reshow()));
        // connect(s_w, SIGNAL(sendScoreAndRate(int, double)), this, SLOT(updateScore(int, double))); // 新增连接
        s_w->resetScoreAndRate();
        s_w->show();
        this->hide();
    }
    else
    {
        QMessageBox::warning(this, "输入错误", errorMessages.join('\n'));
    }
}

void student::updateScore(int score, double rate)
{
    Studentlist.testscore = score;
    Studentlist.testrate = rate;
}

void student::on_cancelButton_clicked()
{
    this->close();
}


void student::on_pushButton_clicked()
{
    QString sql = QString("INSERT INTO students (sid ,sname, ssex, sscore, srate) VALUES (%1, '%2', '%3', %4, %5);").arg(Studentlist.id)
                      .arg(Studentlist.name, Studentlist.sex).arg(Studentlist.testscore).arg(Studentlist.testrate);
    QSqlQuery query;
    if(query.exec(sql))
    {
        QMessageBox::information(this,"数据库录入提示","数据库录入成功");
    }
    else
    {
        QMessageBox::information(this,"数据库录入提示","数据库录入失败");
    }
}


void student::on_pushButton_2_clicked()
{
    ui->scorelabel->setText(QString("%1").arg(Studentlist.testscore));
    ui->ratelabel->setText(QString("%1").arg(Studentlist.testrate));
}

