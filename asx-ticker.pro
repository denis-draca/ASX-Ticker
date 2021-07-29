#-------------------------------------------------
#
# Project created by QtCreator 2021-07-25T13:26:15
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = asx-ticker
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


INCLUDEPATH += /home/denis/Desktop/git-repos/qt-material-widgets/components/

INCLUDEPATH += src/ src/general src/widgets src/dialogs
INCLUDEPATH += header/ header/general header/widgets header/dialogs
INCLUDEPATH += ui/


CONFIG += c++11

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/general/asxcurl.cpp \
        src/general/portfolio_handler.cpp \
        src/widgets/lot.cpp \
        src/widgets/lotview.cpp \
        src/widgets/materialtabs.cpp \
        src/dialogs/buydialog.cpp \
        src/dialogs/selldialog.cpp \
        src/dialogs/tickeradddialog.cpp \
        src/widgets/ownedlots.cpp \
        src/widgets/soldlots.cpp \
        src/dialogs/setkeydialog.cpp

HEADERS += \
        header/mainwindow.h \
        header/general/asxcurl.h \
        header/general/portfolio_handler.h \
        header/widgets/lot.h \
        header/widgets/lotview.h \
        header/widgets/materialtabs.h \
        header/dialogs/buydialog.h \
        header/dialogs/selldialog.h \
        header/dialogs/tickeradddialog.h \
        header/widgets/ownedlots.h \
        header/widgets/soldlots.h \
        header/dialogs/setkeydialog.h

FORMS += \
        ui/buydialog.ui \
ui/selldialog.ui \
ui/mainwindow.ui \
ui/tickeradddialog.ui \
    ui/setkeydialog.ui

LIBS += -lcomponentsd -lcurl

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
