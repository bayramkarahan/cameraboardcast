QT       += core gui multimedia widgets
QT += multimedia multimediawidgets
# GStreamer ve QtGStreamer kütüphanelerini ekleyin
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0 Qt5GStreamer-1.0
CONFIG += link_pkgconfig
# moc dosyası oluşturmak için
MOC_DIR = ./moc
#LIBS += $(shell pkg-config --libs gstreamer-1.0 gstreamer-video-1.0 gstreamer-audio-1.0 Qt5GStreamer-1.0)
#INCLUDEPATH += $(shell pkg-config --cflags gstreamer-1.0 gstreamer-video-1.0 gstreamer-audio-1.0 Qt5GStreamer-1.0)
LIBS +=  -lQt5GStreamer-1.0
INCLUDEPATH +=-I/usr/include/Qt5GStreamer -DQT_CORE_LIB -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/gstreamer-1.0 -I/usr/include/x86_64-linux-gnu -I/usr/include/orc-0.4 -pthread
#INCLUDEPATH += $(shell pkg-config --cflags gstreamer-1.0 gstreamer-video-1.0 gstreamer-audio-1.0 Qt5GStreamer-1.0)
INCLUDEPATH += /usr/include/gstreamer-1.0 \
               /usr/include/glib-2.0 \
               /usr/lib/glib-2.0/include \
               /usr/include/gstreamer-1.0/gst/video

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
LIBS += -lgstreamer-1.0 -lgstapp-1.0 -lgstvideo-1.0 -lgstaudio-1.0
INCLUDEPATH += /usr/include/gstreamer-1.0
PKGCONFIG += gstreamer-1.0 gstreamer-base-1.0 gstreamer-video-1.0 gstreamer-rtp-1.0
LIBS += -lgstreamer-1.0 -lgstapp-1.0 -lgstvideo-1.0 -lgobject-2.0 -lglib-2.0 -lgstaudio-1.0

INCLUDEPATH += /usr/include/gstreamer-1.0 \
               /usr/include/glib-2.0 \
               /usr/lib/glib-2.0/include \
               /usr/include/gstreamer-1.0/gst/video

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bd.cpp \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    VideoPenceresi.h \
    VideoPlayer.h \
    VideoWidget.h \
    bd.h


