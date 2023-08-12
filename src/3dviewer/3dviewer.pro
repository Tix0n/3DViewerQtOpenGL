linux {
  QT += core gui opengl widgets
}

macx {
  QT += core gui openglwidgets
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

include(QtGifImage/src/gifimage/qtgifimage.pri)


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.c \
    affine_transform.c

HEADERS += \
    glview.h \
    mainwindow.h \
    parser.h \
    affine_transform.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
