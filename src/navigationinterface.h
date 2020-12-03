#ifndef NAVIGATIONINTERFACE_H
#define NAVIGATIONINTERFACE_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusError>
#include <QDBusInterface>
#include <QDBusServiceWatcher>

#define SERVICE_NAME "io.github.rinigus.PureMaps"
#define INTERFACE_NAME "io.github.rinigus.PureMaps.navigator"
#define OBJECT_PATH "/io/github/rinigus/PureMaps/navigator"

class NavigationInterface : public QObject
{
    Q_OBJECT
public:
    explicit NavigationInterface(QObject *parent = nullptr);

signals:

    void runningChanged(bool);
    void narrativeChanged(const QString& icon, const QString& narrative);

private:
    QDBusInterface *iface = nullptr;
    QDBusServiceWatcher *m_serviceWatcher = nullptr;

    void connectDaemon();
    void disconnectDaemon();

    Q_SLOT void slot_narrativeChanged();
    Q_SLOT void slot_runningChanged();
    Q_SLOT void slot_iconChanged();

    bool m_running = false;
    QString m_icon;
    QString m_narrative;
};

#endif // NAVIGATIONINTERFACE_H
