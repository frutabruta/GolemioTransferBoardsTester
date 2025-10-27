QT       += core gui
QT       += xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GolemioClient/connectiongolemio.cpp \
    GolemioClient/connectiongolemiov4.cpp \
    GolemioClient/golemio.cpp \
    GolemioClient/golemioresultv4.cpp \
    GolemioClient/golemiov4.cpp \
    GolemioClient/stopgolemio.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GolemioClient/connectiongolemio.h \
    GolemioClient/connectiongolemiov4.h \
    GolemioClient/golemio.h \
    GolemioClient/golemioresultv4.h \
    GolemioClient/golemiov4.h \
    GolemioClient/stopgolemio.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
