QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    business.cpp \
    businessresult.cpp \
    individual.cpp \
    individualresult.cpp \
    main.cpp \
    mainwindow.cpp \
    multilist.cpp

HEADERS += \
    business.h \
    businessresult.h \
    individual.h \
    individualresult.h \
    mainwindow.h \
    multilist.h

FORMS += \
    business.ui \
    businessresult.ui \
    individual.ui \
    individualresult.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrs.qrc

DISTFILES +=
