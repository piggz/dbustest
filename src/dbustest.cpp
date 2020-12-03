#include <QCoreApplication>
#include "navigationinterface.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    NavigationInterface navInterface;

    return app.exec();
}
