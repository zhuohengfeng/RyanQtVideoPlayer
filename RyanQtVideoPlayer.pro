#-------------------------------------------------
#
# Project created by QtCreator 2020-01-16T09:49:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RyanQtVideoPlayer
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
        main.cpp \
        widget.cpp \
        xffmpeg.cpp

HEADERS += \
        widget.h \
        xffmpeg.h

FORMS += \
        widget.ui

# ***********************************************************
# 开始配置
# ***********************************************************

# 附加包含路径
INCLUDEPATH += \
        $$PWD/ffmpeg/include

# ***********************************************************
# Mac平台下配置
# ***********************************************************
macos {
    # 输出目录
    CONFIG(debug, debug|release) {
        DESTDIR = $$PWD/output/mac/debug
    } else {
        DESTDIR = $$PWD/output/mac/release
    }

    # 依赖模块
    LIBS += \
            -L$$PWD/ffmpeg/lib -lavformat.58 \
            -L$$PWD/ffmpeg/lib -lavcodec.58 \
            -L$$PWD/ffmpeg/lib -lavutil.56 \
            -L$$PWD/ffmpeg/lib -lswscale.5

    # mac bundle file
#    APP_FFMPEG.files = $$files($$PWD/third_party/ffmpeg/lib/*.dylib)
#    APP_FFMPEG.path = Contents/MacOS
#    QMAKE_BUNDLE_DATA += APP_FFMPEG

    # 设置图标
    ICON = $$PWD/res/QtScrcpy.icns
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    $$PWD/res/res.qrc

DISTFILES += \
    .gitignore
