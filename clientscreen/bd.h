#ifndef BD_H
#define BD_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <Qt5GStreamer/QGst/Pipeline>
///QGstPipeline>
#include <Qt5GStreamer/QGst/Ui/VideoWidget>
//VideoWidget>
#include <QApplication>
#include <QGst/Init>
#include <QGst/Pipeline>
#include <QGst/Element>
#include <QGst/Bus>
#include <QGst/Message>
#include <iostream>
#include <QApplication>
#include <QGst/Init>
#include <QGst/Pipeline>
#include <QGst/Element>
#include <QGst/Bus>
#include <QGst/Message>
#include <iostream>
#include <gst/gst.h>
#include <QGst/ElementFactory> // Bu satır eklendi
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
//#include <QtGStreamer/QGstUiVideoWidget>
#include <QtWidgets/QVBoxLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <QWidget>

class Bd : public QWidget
{
    Q_OBJECT
public:
    explicit Bd(QWidget *parent = nullptr);
    static GstFlowReturn on_new_sample(GstElement *sink, gpointer data);
    QVideoWidget *videoWidget = new QVideoWidget();

    GError *error = NULL;
    GstElement *pipeline, *source, *depay, *decoder, *sink,*capsfilter;

signals:
};

#endif // BD_H
