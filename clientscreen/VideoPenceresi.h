#include <gst/gst.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMessageBox>
#include <QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include <gst/app/gstappsink.h>

class VideoPenceresi : public QWidget {
    Q_OBJECT

public:
    VideoPenceresi(QWidget *parent = nullptr) : QWidget(parent) {
        gst_init(nullptr, nullptr);
        qDebug()<<"selam";
        //pipeline = gst_parse_launch("udpsrc port=5000 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! appsink name=video_sink", &error);
        pipeline = gst_parse_launch("udpsrc port=5000 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! appsink name=video_sink", &error);

        if (!pipeline) {
            QString hataMesaji = QString("Pipeline oluşturma hatası: %1").arg(error->message);
            QMessageBox::critical(this, "Hata", hataMesaji);
            g_clear_error(&error);
            return;
        }

        videoWidget = new QVideoWidget();
        mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
        mediaPlayer->setVideoOutput(videoWidget);

        GstElement *videoSink = gst_bin_get_by_name(GST_BIN(pipeline), "video_sink");
        g_signal_connect(videoSink, "new-sample", G_CALLBACK(on_new_sample), this);
        qDebug()<<"selam1";
        QGridLayout *layout = new QGridLayout(this);
        layout->addWidget(videoWidget, 0, 0);

        gst_element_set_state(pipeline, GST_STATE_PLAYING);
    }

    ~VideoPenceresi() {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }

public slots:
    static GstFlowReturn on_new_sample(GstElement *sink, gpointer data) {
        VideoPenceresi *pencere = static_cast<VideoPenceresi*>(data);
        GstSample *sample = gst_app_sink_pull_sample(GST_APP_SINK(sink));
        GstBuffer *buffer = gst_sample_get_buffer(sample);
        GstMapInfo map;
        gst_buffer_map(buffer, &map, GST_MAP_READ);
        QImage image(map.data, 500, 500, QImage::Format_RGB888); // width ve height'i ayarlayın
        qDebug()<<"eliff";
        // QImage'i QPixmap'e dönüştürme
        QPixmap pixmap = QPixmap::fromImage(image);
        image.save("ab.png");

        // map.data'yı QImage veya QPixmap'e dönüştürün ve QMediaPlayer'a aktarın
        // ...

        gst_buffer_unmap(buffer, &map);
        gst_sample_unref(sample);
        return GST_FLOW_OK;
    }

private:
    GstElement *pipeline;
    QVideoWidget *videoWidget;
    QMediaPlayer *mediaPlayer;
    GError *error = nullptr;
};

// ...
