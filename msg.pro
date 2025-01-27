#-------------------------------------------------
#
# Project created by QtCreator 2019-06-07T16:17:48
#
#-------------------------------------------------

QT       += core gui network
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = msg
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Base64Decoder.cpp \
        activation.cpp \
        finder.cpp \
        forgotpass.cpp \
        forgotpassrepeat.cpp \
        glavnaya.cpp \
        main.cpp \
        mainwindow.cpp \
        regactivation.cpp \
        registration.cpp \
        smtp.cpp \
        sql_query1.cpp \
        sql_query2.cpp \
        sql_query3.cpp \
        sql_query4.cpp

HEADERS += \
        Base64Decoder.h \
        Crypter.h \
        activation.h \
        finder.h \
        forgotpass.h \
        forgotpassrepeat.h \
        glavnaya.h \
        lib.h \
        mainwindow.h \
        regactivation.h \
        registration.h \
        smtp.h \
        sql_query1.h \
        sql_query2.h \
        sql_query3.h \
        sql_query4.h

FORMS += \
        activation.ui \
        finder.ui \
        forgotpass.ui \
        forgotpassrepeat.ui \
        form.ui \
        glavnaya.ui \
        mainwindow.ui \
        regactivation.ui \
        registration.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
