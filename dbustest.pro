# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = dbustest

QT += dbus

CONFIG += sailfishapp

SOURCES += src/dbustest.cpp \
    src/navigationinterface.cpp

DISTFILES += rpm/dbustest.spec \
    rpm/dbustest.yaml

HEADERS += \
    src/navigationinterface.h
