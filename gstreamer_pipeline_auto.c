/*
Reference:
http://gstreamer.freedesktop.org/data/doc/gstreamer/head/manual/html/chapter-helloworld.html
https://github.com/yaxu/screencast/blob/master/screensave.c
http://comments.gmane.org/gmane.comp.video.gstreamer.devel/30691
https://github.com/hackeron/gstreamer_experiments/blob/master/c/gst_dynamic_test.c
*/

#include <gst/gst.h>
#include <glib.h>

static gboolean
bus_call (GstBus     *bus,
          GstMessage *msg,
          gpointer    data)
{
  GMainLoop *loop = (GMainLoop *) data;

  switch (GST_MESSAGE_TYPE (msg)) {

    case GST_MESSAGE_EOS:
      g_print ("End of stream\n");
      g_main_loop_quit (loop);
      break;

    case GST_MESSAGE_ERROR: {
      gchar  *debug;
      GError *error;

      gst_message_parse_error (msg, &error, &debug);
      g_free (debug);

      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }

  return TRUE;
}


static void
on_pad_added (GstElement *element,
              GstPad     *pad,
              gpointer    data)
{
  GstPad *sinkpad;
  GstElement *decoder = (GstElement *) data;

  /* We can now link this pad with the vorbis-decoder sink pad */
  g_print ("Dynamic pad created, linking demuxer/decoder\n");

  sinkpad = gst_element_get_static_pad (decoder, "sink");

  gst_pad_link (pad, sinkpad);

  gst_object_unref (sinkpad);
}



int
main (int   argc,
      char *argv[])
{
  GMainLoop *loop;

  GstElement *pipeline, *filesrc;
  GstBus *bus;
  guint bus_watch_id;
  GError *error = NULL;

  /* Initialisation */
  gst_init (&argc, &argv);

  loop = g_main_loop_new (NULL, FALSE);


  /* Check input arguments */
  if (argc != 2) {
    g_printerr ("Usage: %s <h.264 filename>\n", argv[0]);
    return -1;
  }


  /* Create gstreamer elements */
  pipeline = gst_parse_launch("filesrc name=src ! decodebin name=decoder decoder. ! vspmfilter ! video/x-raw,width=800,height=480,format=NV12 ! waylandsink decoder. ! queue ! audioconvert ! audioresample ! alsasink", &error);

  if (!pipeline) {
    g_printerr ("pipeline element could not be created. Exiting.\n");
    return -1;
  }
  
  if (!error) {
    filesrc = gst_bin_get_by_name(GST_BIN(pipeline), "src");
    g_printerr("argv[1]=%s\n", argv[1]);
    g_object_set(filesrc, "location", argv[1], NULL);
  }

  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
  gst_object_unref (bus);


  /* Set the pipeline to "playing" state*/
  gst_element_set_state (pipeline, GST_STATE_PLAYING);


  /* Iterate */
  g_print ("Running...\n");
  g_main_loop_run (loop);


  /* Out of the main loop, clean up nicely */
  g_print ("Returned, stopping playback\n");
  gst_element_set_state (pipeline, GST_STATE_NULL);

  g_print ("Deleting pipeline\n");
  gst_object_unref (GST_OBJECT (pipeline));
  g_source_remove (bus_watch_id);
  g_main_loop_unref (loop);

  return 0;
}

