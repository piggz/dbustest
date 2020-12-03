#include "navigationinterface.h"
#include <QDebug>
#include <QDBusReply>

NavigationInterface::NavigationInterface(QObject *parent) : QObject(parent)
  , m_serviceWatcher(new QDBusServiceWatcher(
                         QStringLiteral(SERVICE_NAME), QDBusConnection::sessionBus(),
                         QDBusServiceWatcher::WatchForRegistration | QDBusServiceWatcher::WatchForUnregistration))
{
  QObject::connect(m_serviceWatcher, &QDBusServiceWatcher::serviceRegistered,   this, &NavigationInterface::connectDaemon);
  QObject::connect(m_serviceWatcher, &QDBusServiceWatcher::serviceUnregistered, this, &NavigationInterface::disconnectDaemon);

  connectDaemon();
}

void NavigationInterface::connectDaemon()
{
    qDebug() << Q_FUNC_INFO;

    if (iface) {
        iface->deleteLater();
    }

    iface = new QDBusInterface(QStringLiteral(SERVICE_NAME), QStringLiteral(OBJECT_PATH), QStringLiteral(INTERFACE_NAME), QDBusConnection::sessionBus());

    if (!iface->isValid()) {
        qDebug() << "Interface is not valid";

        iface->deleteLater();
        iface = nullptr;
        return;
    }

    if (!QDBusConnection::sessionBus().connect(QStringLiteral(SERVICE_NAME), QStringLiteral(OBJECT_PATH), QStringLiteral(INTERFACE_NAME), "runningChanged", this, SLOT(slot_runningChanged()))) {
        qDebug()<< "failed to connect running signal";
    }
    if (!QDBusConnection::sessionBus().connect(QStringLiteral(SERVICE_NAME), QStringLiteral(OBJECT_PATH), QStringLiteral(INTERFACE_NAME), "narrativeChanged", this, SLOT(slot_narrativeChanged()))) {
        qDebug()<< "failed to connect narrative signal";
    }
    if (!QDBusConnection::sessionBus().connect(QStringLiteral(SERVICE_NAME), QStringLiteral(OBJECT_PATH), QStringLiteral(INTERFACE_NAME), "iconChanged", this, SLOT(slot_iconChanged()))) {
        qDebug()<< "failed to connect icon signal";
    }
}

void NavigationInterface::disconnectDaemon()
{

}

void NavigationInterface::slot_runningChanged()
{
    qDebug() << Q_FUNC_INFO;

    if (!iface || !iface->isValid()) {
        return;
    }
    bool reply = iface->property("running").toBool();
    qDebug() << reply;

    if (m_running != reply) {
        m_running = reply;
        emit runningChanged(m_running);
    }
}

void NavigationInterface::slot_iconChanged()
{
    qDebug() << Q_FUNC_INFO;

    if (!iface || !iface->isValid()) {
        return;
    }
    QString reply = iface->property("icon").toString();
    qDebug() << reply;

    if (m_icon != reply) {
        m_icon = reply;
        emit narrativeChanged(m_icon, m_narrative);
    }
}

void NavigationInterface::slot_narrativeChanged()
{
    qDebug() << Q_FUNC_INFO;

    if (!iface || !iface->isValid()) {
        return;
    }
    QString reply = iface->property("narrative").toString();
    qDebug() << reply;
    if (m_narrative != reply) {
        m_narrative = reply;
        emit narrativeChanged(m_icon, m_narrative);
    }
}
