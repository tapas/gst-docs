#include <gst/gst.h>

int
main (int argc, char *argv[])
{
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;
  

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Build the pipeline, gst_parse_launch is automatically building pipeline from string, not so configurable */
  pipeline =
      gst_parse_launch
      ("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm",      
      NULL);

      //Below not working for above
  //("playbin uri=rtspsrc location=rtsp://admin:Admin.embd5!324@192.168.19.100 latency=0 ! decodebin ! videoconvert ! appsink sync=false max-buffers=1 drop=true"
  //below working
  //("playbin uri=file:///home/surveillance6/Videos/2017-09-25_17_30.mp4",      
  /* Start playing */

  //gst has PLAYING state like DVD PLAY button
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  /* Wait until error or EOS(End Of Stream) */
  bus = gst_element_get_bus (pipeline);
  msg =
      gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
      GST_MESSAGE_ERROR | GST_MESSAGE_EOS);//wait until error or end of stream

  /* Free resources */
  if (msg != NULL)
    gst_message_unref (msg);
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  return 0;
}
