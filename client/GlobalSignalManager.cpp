
#include "GlobalSignalManager.h"
GlobalSignalManager* GlobalSignalManager::m_instance = nullptr;

GlobalSignalManager* GlobalSignalManager::instance() {
    if (!m_instance) {
        m_instance = new GlobalSignalManager();
    }
    return m_instance;
}

GlobalSignalManager::GlobalSignalManager(QObject *parent) : QObject(parent) {}
