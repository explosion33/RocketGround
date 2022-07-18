QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_ICONS = icon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dynchart.cpp \
    grabapi.cpp \
    led.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp

HEADERS += \
    dynchart.h \
    grabapi.h \
    led.h \
    mainwindow.h \
    settings.h

FORMS += \
    mainwindow.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


unix|win32: LIBS += -LD:/vcpkg/packages/zlib_x64-windows/lib/ -lzlib
INCLUDEPATH += D:/vcpkg/packages/zlib_x64-windows/include
INCLUDEPATH += D:/vcpkg/packages/zlib_x64-windows/bin
DEPENDPATH += D:/vcpkg/packages/zlib_x64-windows/bin
DEPENDPATH += D:/vcpkg/packages/zlib_x64-windows/include


unix|win32: LIBS += -LD:/vcpkg/packages/curl_x64-windows/lib/ -llibcurl
INCLUDEPATH += D:/vcpkg/packages/curl_x64-windows/include
INCLUDEPATH += D:/vcpkg/packages/curl_x64-windows/bin
DEPENDPATH += D:/vcpkg/packages/curl_x64-windows/bin
DEPENDPATH += D:/vcpkg/packages/curl_x64-windows/include

DISTFILES += \
    ../../../../../Downloads/settings.png
