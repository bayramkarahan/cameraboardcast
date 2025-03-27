#include "bd.h"

Bd::Bd(QWidget *parent)
    : QWidget{parent}
{
    gst_init(nullptr, nullptr);
    pipeline = gst_pipeline_new("my-pipeline");
    source = gst_element_factory_make("v4l2src", "source"); // Örnek kaynak
    //pipeline = gst_pipeline_new("udp-player");
    source = gst_element_factory_make("udpsrc", "source");
    //depay = gst_element_factory_make("rtph264depay", "depay");
    //capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
    depay = gst_element_factory_make("rtph264depay", "depay");
    // g_object_set(G_OBJECT(depay), "payload-type", 96, nullptr); // Yük türünü ayarlayın
    decoder = gst_element_factory_make("avdec_h264", "decoder");
    sink = gst_element_factory_make("appsink", "sink");
    g_object_set(sink, "emit-signals", TRUE, NULL);
    g_object_set(sink, "sync", FALSE, NULL);
    gst_bin_add_many(GST_BIN(pipeline), source, sink, NULL);
    gst_element_link(source, sink);
      g_signal_connect(sink, "new-sample", G_CALLBACK(on_new_sample),this);
    gst_bin_add_many(GST_BIN(pipeline), source, depay, decoder, sink, nullptr);
    gst_element_link_many(source, depay, decoder, sink, nullptr);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    //gst_element_set_state(pipeline, GST_STATE_PLAYING);
    std::cout << "Alıcı başladı (Ctrl+C ile durdurun)..." << std::endl;

    // Alıcı devam ederken (Ctrl+C ile durdurulana kadar) bekleyin
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    // Pipeline'ları durdur ve temizle
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

}
GstFlowReturn Bd::on_new_sample(GstElement *sink, gpointer data) {
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
