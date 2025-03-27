gstreamer
=========

gstreamer Nedir?
++++++++++++++++

gstreamer c++ video işlemleri yapabileceğimiz kütüphanedir.

mp4 Genel Yayın Yapma(ses-video)
--------------------------------

Server:
.......

gst-launch-1.0 filesrc location=a.mp4 ! decodebin ! videoconvert ! x264enc tune=zerolatency bitrate=1024 ! rtph264pay ! udpsink host=239.0.0.1 port=5000 filesrc location=a.mp4 ! decodebin ! audioconvert ! opusenc ! rtpopuspay ! udpsink host=239.0.0.1 port=5001


Client(video):
..............

gst-launch-1.0 udpsrc address=239.0.0.1 port=5000 ! application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96 ! rtph264depay ! avdec_h264 ! autovideosink

Client(ses):
............

gst-launch-1.0 udpsrc port=5001 address=239.0.0.1 ! capsfilter caps="application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97" ! rtpopusdepay ! opusdec ! autoaudiosink

Kamera Genel Yayın Yapma(ses-video)
-----------------------------------

Server(video):
.......

gst-launch-1.0 v4l2src device=/dev/video0 ! videoconvert ! x264enc tune=zerolatency ! rtph264pay config-interval=1 pt=96 ! udpsink host=239.0.0.1 port=5000

Server(ses):
.......

gst-launch-1.0  autoaudiosrc ! audioconvert ! opusenc ! rtpopuspay pt=97 ! udpsink host=239.0.0.1 port=5001

gst-launch-1.0 v4l2src device=/dev/video0 ! videoconvert ! x264enc tune=zerolatency ! rtph264pay config-interval=1 pt=96 ! udpsink host=239.0.0.1 port=5000 autoaudiosrc ! audioconvert ! opusenc ! rtpopuspay pt=97 ! udpsink host=239.0.0.1 port=5001


Client(video):
..............

gst-launch-1.0 udpsrc port=5000 address=239.0.0.1 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink

Client(ses):
..............

gst-launch-1.0 udpsrc port=5001 address=239.0.0.1 ! capsfilter caps=\"application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97\" ! rtpopusdepay ! opusdec ! autoaudiosink


Ekranı Genel Yayın Yapma(ses-video)
-----------------------------------

Server(video):
.......

gst-launch-1.0 ximagesrc xid=$(xdotool getactivewindow) ! video/x-raw,framerate=30/1 ! videoconvert ! x264enc tune=zerolatency bitrate=1024 ! rtph264pay ! udpsink host=239.0.0.1 port=5000

Server(ses):
.......

gst-launch-1.0  autoaudiosrc ! audioconvert ! opusenc ! rtpopuspay pt=97 ! udpsink host=239.0.0.1 port=5001


Client(video):
..............

st-launch-1.0 udpsrc port=5000 address=239.0.0.1 ! application/x-rtp, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink

Client(ses):
..............

gst-launch-1.0 udpsrc port=5001 address=239.0.0.1 ! capsfilter caps=\"application/x-rtp, media=(string)audio, clock-rate=(int)48000, encoding-name=(string)OPUS, payload=(int)97\" ! rtpopusdepay ! opusdec ! autoaudiosink

