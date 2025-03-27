#ifndef VIDEPLAYER_H
#define VIDEPLAYER_H
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <iostream>
#include<QDebug>
#include<QVideoWidget>

class VideoPlayer : public QWidget {
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = nullptr) : QWidget(parent) {
        gst_init(nullptr, nullptr);
        qDebug()<<"açıldın";
         QVideoWidget *videoWidget = new QVideoWidget(this);
        pipeline = gst_pipeline_new("video-pipeline");

        source = gst_element_factory_make("udpsrc", "source");
        rtpdepay = gst_element_factory_make("rtph264depay", "rtpdepay");
        decoder = gst_element_factory_make("avdec_h264", "decoder");
        sink = gst_element_factory_make("autovideosink", "sink");


        if (!pipeline || !source || !rtpdepay || !decoder || !sink) {
            std::cerr << "GStreamer elementleri oluşturulamadı!" << std::endl;
            exit(1);
        }

        g_object_set(source, "port", 5000, nullptr); // UDP portunu ayarlayın
        g_object_set(source, "caps", gst_caps_from_string("application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96"), nullptr);

        gst_bin_add_many(GST_BIN(pipeline), source, rtpdepay, decoder, sink, nullptr);
        gst_element_link_many(source, rtpdepay, decoder, sink, nullptr);
        g_object_set(pipeline, "video-sink", videoWidget, nullptr);
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
        //pipeline = gst_parse_launch(videoPipeline.c_str(), &error);

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &VideoPlayer::checkPipelineState);
        timer->start(1000); // Durumu her saniyede kontrol et
    }

    ~VideoPlayer() {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }

public slots:
    void checkPipelineState() {
        qDebug()<<"dddd";
        GstState state, pending;
        //GstClockTime duration, position;
         gint64 duration, position; // gint64 türünde değişkenler oluşturuyoruz.
        gst_element_get_state(pipeline, &state, &pending, GST_CLOCK_TIME_NONE);

        if (state == GST_STATE_PLAYING) {
            if (gst_element_query_duration(pipeline, GST_FORMAT_TIME, &duration)) {
                //std::cout << "Süre: " << GST_TIME_ARGS(duration) << std::endl;
            }
            if (gst_element_query_position(pipeline, GST_FORMAT_TIME, &position)) {
                //std::cout << "Pozisyon: " << GST_TIME_ARGS(position) << std::endl;
            }
        }
    }

private:
    GstElement *pipeline, *source, *rtpdepay, *decoder, *sink;
};

#endif // VIDEPLAYER_H
