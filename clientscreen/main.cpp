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
//#include<VideoPenceresi.h>
#include<QMediaPlayer>

/*
class VideoWidget : public QWidget {
    Q_OBJECT
public:
    VideoWidget(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        QVideoWidget *videoWidget = new QVideoWidget(this);
        layout->addWidget(videoWidget);
        setLayout(layout);

        // Initialize GStreamer
        gst_init(nullptr, nullptr);
        GstElement *pipeline = gst_parse_launch("playbin uri=file:///a.mp4", nullptr);
        g_object_set(pipeline, "video-sink", videoWidget, nullptr);
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
    }
};
*/


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    // Video ve ses pipeline'ları
 /*   std::string videoPipeline = "udpsrc port=5000 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink";
    std::string audioPipeline = "udpsrc port=5001 ! capsfilter caps=\"application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97\" ! rtpopusdepay ! opusdec ! autoaudiosink";

    pipeline = gst_parse_launch(videoPipeline.c_str(), &error);
    GstElement *sink = gst_bin_get_by_name((GstBin*)pipeline,"sink");
    g_object_set(pipeline, "sink", videoWidget, nullptr);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    //videoWidget->show();
*/
   /* pipeline = gst_pipeline_new("udp-player");
    source = gst_element_factory_make("udpsrc", "source");
    //depay = gst_element_factory_make("rtph264depay", "depay");
   // capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
    depay = gst_element_factory_make("rtph264depay", "depay");
    // g_object_set(G_OBJECT(depay), "payload-type", 96, nullptr); // Yük türünü ayarlayın
    decoder = gst_element_factory_make("avdec_h264", "decoder");
   //sink = gst_element_factory_make("appsink", "sink");
    // capsfilter caps ayarı
    /*GstCaps *caps = gst_caps_new_simple("application/x-rtp",
                                        "media", G_TYPE_STRING, "video",
                                        "clock-rate", G_TYPE_INT, 90000,
                                        "encoding-name", G_TYPE_STRING, "H264",
                                        "payload", G_TYPE_INT, 96,
                                        nullptr);
*/
   // g_object_set(G_OBJECT(capsfilter), "caps", caps, nullptr);
   /* g_object_set(G_OBJECT(source), "port", 5000, nullptr);
   // g_object_set(G_OBJECT(sink), "emit-signals", TRUE, "sync", FALSE, nullptr);
    // Öğeleri boru hattına ekleme..
    gst_bin_add_many(GST_BIN(pipeline), source, depay, decoder, nullptr);
    gst_element_link_many (source, depay, decoder,  nullptr);
*/
    //gst_bin_add_many (GST_BIN (video_pipeline), video_source, video_convert, video_encode, video_pay, video_sink, NULL);
   // gst_element_link_many (video_source, video_convert, video_encode, video_pay, video_sink, nullptr);

   // GstStateChangeReturn video_ret = gst_element_set_state(video_pipeline, GST_STATE_PLAYING);
    //GstStateChangeReturn audio_ret  = gst_element_set_state(audio_pipeline, GST_STATE_PLAYING);

     //VideoWidget pencere;
   // pencere.show();
QMediaPlayer *receiver = new QMediaPlayer;
    QMediaPlayer *receiver1 = new QMediaPlayer;

QVideoWidget *videoWidget = new QVideoWidget;
    QVideoWidget *videoWidget1 = new QVideoWidget;
receiver->setVideoOutput(videoWidget);
    receiver1->setVideoOutput(videoWidget1);
//receiver->setMedia(QUrl("gst-pipeline: udpsrc address=239.0.0.1 port=5000 ! \
  //  application/x-rtp,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! \
   // xvimagesink name=qtvideosink"));
//receiver->setMedia(QUrl("gst-pipeline: udpsrc address=239.0.0.1 port=5000 ! application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96 ! rtph264depay ! avdec_h264 !  xvimagesink name=qtvideosink"));
//receiver->play();
///receiver->setMedia(QUrl("gst-pipeline: udpsrc port=5000 address=239.0.0.101 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert !  xvimagesink name=qtvideosink"));
//receiver->setMedia(QUrl("gst-pipeline: udpsrc port=5000 address="+newIp+" ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert !  xvimagesink name=qtvideosink"));
receiver->setMedia(QUrl("gst-pipeline: udpsrc port=5000 address=239.0.1.101 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert !  xvimagesink name=qtvideosink"));
receiver->play();

    receiver->play();
videoWidget->setStyleSheet("QVideoWidget {"
"background-color:rgba(50, 50, 50, 0);"
" border: 1px solid #555;"
"  border-radius: 5px;"
"  padding: 5px;"
"  color: white;"
             "}");
    // Arka plan rengini değiştirme
    QPalette palette = videoWidget->palette();
    palette.setColor(QPalette::Window, Qt::gray);
    videoWidget->setPalette(palette);

    // Ölçeklendirme modunu ayarlama
    videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);

//receiver->setStyleSheet("  background-color: rgba(50, 50, 50, 0);");
receiver1->setMedia(QUrl("gst-pipeline: udpsrc port=5001 address=239.0.0.1 ! capsfilter caps=\"application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97\" ! rtpopusdepay ! opusdec ! autoaudiosink"));
receiver1->play();
// Content will be shown in this widget.
videoWidget->show();
//videoWidget1->show();
    return app.exec();
}
//#include "main.moc" // moc dosyasını dahil edin
