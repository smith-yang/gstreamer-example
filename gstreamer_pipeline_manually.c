#include <stdio.h>
#include <gst/gst.h>
#include <glib.h>

// Moved to global vars
// Because too lazy to make up an app context struct
// to pass to event callback procedure

GMainLoop *loop;
GstElement *pipeline, *source, *typefind, *demuxer, *audio_decoder, *video_decoder, *audio_conv, *video_conv, *video_filter, *audio_encoder, *video_encoder, *muxer, *sink, *q1, *audio_queue, *video_queue, *audio_sink, *video_sink, *tee, *surf_queue;
GstPad *blockpad;
GstBus *bus;
guint bus_watch_id;


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
on_demuxer_pad_added (GstElement *element,
                      GstPad     *pad,
                      gpointer    data)
{
	GstPad *sinkpad;
	GstElement *decoder = NULL;
	gchar *name = gst_pad_get_name(pad);
	fprintf(stderr, "pad name '%s'\n", name);
	if (!strncmp(name, "video", 5)) {
		//decoder = video_decoder;
		decoder = video_queue;
	} else if (!strncmp(name, "audio", 5)) {
		//decoder = audio_decoder;
		decoder = audio_queue;
	} else {
		return;  // We don't need other media types
	}

	g_print ("Dynamic pad created, linking demuxer/queue\n");

	sinkpad = gst_element_get_static_pad (decoder, "sink");

	gst_pad_link (pad, sinkpad);

	gst_object_unref (sinkpad);
}

static void
on_decoder_pad_added (GstElement *element,
                      GstPad     *pad,
                      gpointer    data)
{
	GstPad *sinkpad;
	GstElement *converter = (GstElement *) data;
	gchar *name = gst_pad_get_name(pad);
	fprintf(stderr, "pad name '%s'\n", name);

	g_print ("Dynamic pad created, linking decoderbin/converter\n");

	sinkpad = gst_element_get_static_pad (converter, "sink");

	gst_pad_link (pad, sinkpad);

	gst_object_unref (sinkpad);
}

static void
cb_typefound (GstElement *tfind,
	      guint       probability,
	      GstCaps    *caps,
	      gpointer    data)
{
  gchar *type;

  type = gst_caps_to_string (caps);
  g_print ("Media type %s found, probability %d%%\n", type, probability);
  g_free (type);

  demuxer        = gst_element_factory_make ("qtdemux", "demuxer");
  gst_element_set_state (demuxer, GST_STATE_PAUSED);
  gst_bin_add (GST_BIN (pipeline), demuxer);
  gst_element_link (q1, demuxer);
  g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_demuxer_pad_added), NULL);
  gst_element_link (typefind, q1);

  gst_element_set_state (pipeline, GST_STATE_PLAYING);

}

int
main (int   argc,
      char *argv[])
{

	GstCaps *filtercaps;
	/* Initialisation */
	gst_init (&argc, &argv);

	loop = g_main_loop_new (NULL, FALSE);


	/* Check input arguments */
	//if (argc != 3) {
	if (argc != 2) {
		g_printerr ("Usage: %s <quicktime format input file name> <mpegts format output file name>\n", argv[0]);
		return -1;
	}


	/* Create gstreamer elements */
	pipeline       = gst_pipeline_new ("audio-player");
	source         = gst_element_factory_make ("filesrc", "file-source");
	typefind       = gst_element_factory_make ("typefind", "typefinder");
	q1             = gst_element_factory_make ("queue", "q1");
	blockpad       = gst_element_get_static_pad (q1, "src");
	//demuxer        = gst_element_factory_make ("qtdemux", "demuxer");
	audio_queue    = gst_element_factory_make ("queue", "audio-queue");
	video_queue    = gst_element_factory_make ("queue", "video-queue");
	audio_decoder  = gst_element_factory_make ("decodebin", "audio-decoder");
	video_decoder  = gst_element_factory_make ("decodebin", "video-decoder");
	audio_conv     = gst_element_factory_make ("audioconvert", "audio-converter");
	audio_sink     = gst_element_factory_make ("alsasink", "audio-output");

	video_conv   = gst_element_factory_make ("vspfilter", "video-converter");

	video_filter = gst_element_factory_make ("capsfilter", NULL);

	surf_queue   = gst_element_factory_make ("queue", "surf-queue");

	video_sink   = gst_element_factory_make ("waylandsink", "video-output");


	if (!pipeline || !source || !typefind || !q1 || !blockpad /*|| !demuxer*/ || !audio_queue || !video_queue || !audio_decoder || !video_decoder ||
	    !audio_conv || !video_conv || !video_filter || !audio_sink || !video_sink) {
		g_printerr ("One element could not be created. Exiting.\n");
		return -1;
	}

	/* Set up the pipeline */

	/* we set the input filename to the source element */
	g_object_set (G_OBJECT (source), "location", argv[1], NULL);

	filtercaps = gst_caps_new_simple ("video/x-raw",
	                                  "format", G_TYPE_STRING, "NV12",
	                                  "width", G_TYPE_INT, 800,
	                                  "height", G_TYPE_INT, 480,
	                                  NULL);
	g_object_set (G_OBJECT (video_filter), "caps", filtercaps, NULL);
	gst_caps_unref (filtercaps);

	/* we add a message handler */
	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
	gst_object_unref (bus);

	/* we add all elements into the pipeline */
	gst_bin_add_many (GST_BIN (pipeline),
	                  source, typefind, q1, /*demuxer, */audio_queue, video_queue, audio_decoder, video_decoder,
	                  audio_conv, video_conv, video_filter, audio_sink,
	                  video_sink, surf_queue, NULL);

	/* we link the elements together */
	gst_element_link (source, typefind);
	//gst_element_link (q1, demuxer);
	gst_element_link_many (audio_queue, audio_decoder, NULL);
	gst_element_link_many (video_queue, video_decoder, NULL);
	gst_element_link_many (audio_conv, audio_sink, NULL);
	gst_element_link_many (video_conv, video_filter, surf_queue, video_sink, NULL);

	g_signal_connect (typefind, "have-type", G_CALLBACK (cb_typefound), NULL);
	//g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_demuxer_pad_added), NULL);
	g_signal_connect (audio_decoder, "pad-added", G_CALLBACK (on_decoder_pad_added), audio_conv);
	g_signal_connect (video_decoder, "pad-added", G_CALLBACK (on_decoder_pad_added), video_conv);

	/* Set the pipeline to "playing" state*/
	g_print ("Now playing: %s\n", argv[1]);
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

