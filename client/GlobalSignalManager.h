#ifndef GLOBALSIGNALMANAGER_H
#define GLOBALSIGNALMANAGER_H
#include <QObject>
class GlobalSignalManager : public QObject {
    Q_OBJECT
public:
    static GlobalSignalManager* instance();
signals:
    void textReceived(QString text); // 跨项目信号
private:
    explicit GlobalSignalManager(QObject *parent = nullptr);
    static GlobalSignalManager* m_instance;
};
#endif // GLOBALSIGNALMANAGER_H
