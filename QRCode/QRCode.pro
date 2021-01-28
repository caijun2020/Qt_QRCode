QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ImageRender.cpp \
    QRGenerator.cpp \
    QRParser.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ImageRender.h \
    MainWindow.h \
    QRGenerator.h \
    QRParser.h \
    QZXing/QZXing.h \
    libqrencode/qrencode.h

FORMS += \
    ImageRender.ui \
    MainWindow.ui \
    QRGenerator.ui \
    QRParser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += ./libqrencode
LIBS += $$PWD/libqrencode/libqrencode.dll

INCLUDEPATH += ./QZXing
LIBS += $$PWD/QZXing/QZXing2.dll


RC_FILE = icon.rc

DEFINES += QZXING_LIBRARY

