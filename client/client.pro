QT       += core gui \
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    qcustomplot.cpp \
    clientdialog.cpp \
    connection_info.cpp \
    connectionclient.cpp \
    main.cpp \
    mainwindow.cpp \
    signal_processing.cpp

HEADERS += \
    qcustomplot.h \
    clientdialog.h \
    connection_info.h \
    connectionclient.h \
    mainwindow.h \
    ../connection_structure.h \
    signal_processing.h

FORMS += \
    clientdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
