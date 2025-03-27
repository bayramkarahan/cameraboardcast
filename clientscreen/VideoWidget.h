#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H
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
class VideoWidget : public QWidget {
    Q_OBJECT
public:
    VideoWidget(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        QVideoWidget *videoWidget = new QVideoWidget(this);
        layout->addWidget(videoWidget);
        setLayout(layout);
        gst_init(nullptr, nullptr);
        GError *error = NULL;

        // Video ve ses pipeline'ları
        //std::string videoPipeline = "udpsrc port=5000 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink";
        //std::string audioPipeline = "udpsrc port=5001 ! capsfilter caps=\"application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97\" ! rtpopusdepay ! opusdec ! autoaudiosink";


        //pipeline = gst_parse_launch(videoPipeline.c_str(), &error);
        GstElement *pipeline = gst_parse_launch(
            "udpsrc port=5000 address=239.0.0.1 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! appsink name=videosink",
            nullptr);

        GstElement *sink = gst_bin_get_by_name((GstBin*)pipeline,"videosink");
        g_object_set(sink, "emit-signals", TRUE, NULL);

        g_signal_connect(sink, "new-sample", G_CALLBACK(on_new_sample),this);

        //g_signal_connect(sink, "new-sample", G_CALLBACK(on_new_sample),this);


       // g_signal_connect(sink, "new-sample", G_CALLBACK(on_new_sample),this);

        // Video pipeline'ı oluştur
        //pipeline = gst_parse_launch(videoPipeline.c_str(), &error);
         //   g_object_set(pipeline, sink, videoWidget, nullptr);
        gst_element_set_state(pipeline, GST_STATE_PLAYING);


        std::cout << "Alıcı başladı (Ctrl+C ile durdurun)..." << std::endl;

        // Alıcı devam ederken (Ctrl+C ile durdurulana kadar) bekleyin
        GMainLoop *loop = g_main_loop_new(NULL, FALSE);
        g_main_loop_run(loop);

        // Pipeline'ları durdur ve temizle
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
                // Video pipeline'ı oluştur
        //pipeline = gst_parse_launch(videoPipeline.c_str(), &error);
       //g_object_set(pipeline, "video-sink", videoWidget, nullptr);
        //gst_element_set_state(pipeline, GST_STATE_PLAYING);
    }
private:
static  GstFlowReturn on_new_sample(GstElement *sink, gpointer data) {
        // ...
        GstSample *sample = gst_app_sink_pull_sample(GST_APP_SINK(sink));
        GstBuffer *buffer = gst_sample_get_buffer(sample);
        GstMapInfo map;
        gst_buffer_map(buffer, &map, GST_MAP_READ);
        // ... Görüntüyü işle ...
        qDebug()<<"işlemler";
        gst_buffer_unmap(buffer, &map);
        gst_sample_unref(sample);
        return GST_FLOW_OK;
    }
};

#endif // VIDEOWIDGET_H
