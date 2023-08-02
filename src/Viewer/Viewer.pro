DEFINES += \
    GL_SILENCE_DEPRECATION

QT       += core gui
QT       += opengl
QT       += openglwidgets

include(../QtGifImage/src/gifimage/qtgifimage.pri)


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets \
    opengl

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../affine.c \
    ../file_to_object.c \
    main.cpp \
    mainwindow.cpp \
    ogl.cpp

HEADERS += \
    ../affine.h \
    ../file_to_object.h \
    mainwindow.h \
    ogl.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../README_RUS_viewer.md \
    ../cube.obj
