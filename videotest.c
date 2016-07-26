/*
Packages versions:
 # equery list '*gst*' | grep '[-]1'
media-libs/gst-plugins-bad-1.2.0
media-libs/gst-plugins-base-1.2.0
media-libs/gst-plugins-good-1.2.0
media-libs/gst-plugins-ugly-1.2.0
media-libs/gstreamer-1.2.0
media-plugins/gst-plugins-a52dec-1.0.5
media-plugins/gst-plugins-cdparanoia-1.0.5
media-plugins/gst-plugins-dts-1.0.5
media-plugins/gst-plugins-dvdread-1.0.5
media-plugins/gst-plugins-faad-1.0.5
media-plugins/gst-plugins-flac-1.0.5
media-plugins/gst-plugins-libav-1.2.0
media-plugins/gst-plugins-mad-1.0.5
media-plugins/gst-plugins-meta-1.0-r1
media-plugins/gst-plugins-mpeg2dec-1.0.5
media-plugins/gst-plugins-resindvd-1.0.5
media-plugins/gst-plugins-x264-1.2.0
This source file is derived from "Hello world" of Gstreamer Application Development Manual.
The application freezes, see its output below.
./gstreamer_test ~/Downloads/big_buck_bunny_720p_h264.mov bbb_reenc.ts
Now playing: /home/krieger/Downloads/big_buck_bunny_720p_h264.mov
Running...
pad name 'video_0'
Dynamic pad created, linking demuxer/decoder
pad name 'audio_0'
Dynamic pad created, linking demuxer/decoder
<hangs there. Output file is 0 bytes length>
GDB backtraces:
(gdb) thread apply all bt
Thread 6 (Thread 0x7fe20d30d700 (LWP 22426)):
#0  0x00007fe2135205ec in pthread_cond_wait () from /lib64/libpthread.so.0
#1  0x00007fe2137b97af in g_cond_wait () from /usr/lib64/libglib-2.0.so.0
#2  0x00007fe2119afc33 in gst_collect_pads_chain (pad=0x1a6a490, parent=0x1a6e0c0, buffer=0x7fe208003d80)
    at gstcollectpads.c:2056
#3  0x00007fe213d20c51 in gst_pad_chain_data_unchecked (pad=0x1a6a490, type=4112, data=0x7fe208003d80) at gstpad.c:3711
#4  0x00007fe213d21714 in gst_pad_push_data (pad=0x19eb860, type=4112, data=0x7fe208003d80) at gstpad.c:3941
#5  0x00007fe213d21c65 in gst_pad_push (pad=0x19eb860, buffer=0x7fe208003d80) at gstpad.c:4044
#6  0x00007fe2112c2de8 in gst_audio_encoder_finish_frame (enc=0x1a5a370, buf=0x7fe208003d80, samples=1152)
    at gstaudioencoder.c:856
#7  0x00007fe2102f69d4 in gst_ffmpegaudenc_encode_audio () from /usr/lib64/gstreamer-1.0/libgstlibav.so
#8  0x00007fe2102f6fa3 in gst_ffmpegaudenc_handle_frame () from /usr/lib64/gstreamer-1.0/libgstlibav.so
#9  0x00007fe2112c35ab in gst_audio_encoder_push_buffers (enc=0x1a5a370, force=0) at gstaudioencoder.c:976
#10 0x00007fe2112c50ba in gst_audio_encoder_chain (pad=0x19eb630, parent=0x1a5a370, buffer=0x7fe208003830)
    at gstaudioencoder.c:1195
#11 0x00007fe213d20c51 in gst_pad_chain_data_unchecked (pad=0x19eb630, type=4112, data=0x7fe208003830) at gstpad.c:3711
#12 0x00007fe213d21714 in gst_pad_push_data (pad=0x19eafa0, type=4112, data=0x7fe208003830) at gstpad.c:3941
#13 0x00007fe213d21c65 in gst_pad_push (pad=0x19eafa0, buffer=0x7fe208003830) at gstpad.c:4044
#14 0x00007fe2119a2946 in gst_base_transform_chain (pad=0x19ead70, parent=0x1a51000, buffer=0x7fe208003940)
    at gstbasetransform.c:2237
#15 0x00007fe213d20c51 in gst_pad_chain_data_unchecked (pad=0x19ead70, type=4112, data=0x7fe208003940) at gstpad.c:3711
#16 0x00007fe213d21714 in gst_pad_push_data (pad=0x19ea6e0, type=4112, data=0x7fe208003940) at gstpad.c:3941
#17 0x00007fe213d21c65 in gst_pad_push (pad=0x19ea6e0, buffer=0x7fe208003940) at gstpad.c:4044
#18 0x00007fe2112b7963 in gst_audio_decoder_push_forward (dec=0x1a43110, buf=0x7fe208003940) at gstaudiodecoder.c:876
#19 0x00007fe2112b8163 in gst_audio_decoder_output (dec=0x1a43110, buf=0x7fe208003940) at gstaudiodecoder.c:952
#20 0x00007fe2112b9215 in gst_audio_decoder_finish_frame (dec=0x1a43110, buf=0x7fe208003940, frames=0)
    at gstaudiodecoder.c:1156
#21 0x00007fe2102fb4c5 in gst_ffmpegauddec_handle_frame () from /usr/lib64/gstreamer-1.0/libgstlibav.so
#22 0x00007fe2112b97cb in gst_audio_decoder_handle_frame (dec=0x1a43110, klass=0x1a41c90, buffer=0x7fe208003830)
    at gstaudiodecoder.c:1203
#23 0x00007fe2112b9c5d in gst_audio_decoder_push_buffers (dec=0x1a43110, force=0) at gstaudiodecoder.c:1301
#24 0x00007fe2112ba196 in gst_audio_decoder_chain_forward (dec=0x1a43110, buffer=0x0) at gstaudiodecoder.c:1404
#25 0x00007fe2112bba36 in gst_audio_decoder_chain (pad=0x19ea4b0, parent=0x1a43110, buffer=0x7fe208003830)
    at gstaudiodecoder.c:1672
#26 0x00007fe213d20c51 in gst_pad_chain_data_unchecked (pad=0x19ea4b0, type=4112, data=0x7fe208003830) at gstpad.c:3711
#27 0x00007fe213d21714 in gst_pad_push_data (pad=0x1a6af80, type=4112, data=0x7fe208003830) at gstpad.c:3941
#28 0x00007fe213d21c65 in gst_pad_push (pad=0x1a6af80, buffer=0x7fe208003830) at gstpad.c:4044
#29 0x00007fe211716f23 in gst_qtdemux_decorate_and_push_buffer (qtdemux=0x19f8240, stream=<optimized out>,
    buf=0x7fe208003830, dts=21333333, pts=21333333, duration=21333333, keyframe=1, position=21333333,
    byte_position=<optimized out>) at qtdemux.c:4109
#30 0x00007fe211727dd4 in gst_qtdemux_loop_state_movie (qtdemux=0x19f8240) at qtdemux.c:4246
#31 gst_qtdemux_loop (pad=0x19ea280) at qtdemux.c:4323
#32 0x00007fe213d54d64 in gst_task_func (task=0x1a86000) at gsttask.c:316
#33 0x00007fe213d55e5f in default_func (tdata=0x1a75520, pool=0x1898840) at gsttaskpool.c:70
---Type <return> to continue, or q <return> to quit---
#34 0x00007fe21379fbf8 in g_thread_pool_thread_proxy () from /usr/lib64/libglib-2.0.so.0
#35 0x00007fe21379f325 in g_thread_proxy () from /usr/lib64/libglib-2.0.so.0
#36 0x00007fe21351bda6 in start_thread () from /lib64/libpthread.so.0
#37 0x00007fe213254abd in clone () from /lib64/libc.so.6
Thread 5 (Thread 0x7fe20ca31700 (LWP 22427)):
#0  0x00007fe2135205ec in pthread_cond_wait () from /lib64/libpthread.so.0
#1  0x00007fe20f60c88b in frame_worker_thread () from /usr/lib64/libavcodec.so.54
#2  0x00007fe21351bda6 in start_thread () from /lib64/libpthread.so.0
#3  0x00007fe213254abd in clone () from /lib64/libc.so.6
Thread 4 (Thread 0x7fe207fff700 (LWP 22428)):
#0  0x00007fe2135205ec in pthread_cond_wait () from /lib64/libpthread.so.0
#1  0x00007fe20f60c88b in frame_worker_thread () from /usr/lib64/libavcodec.so.54
#2  0x00007fe21351bda6 in start_thread () from /lib64/libpthread.so.0
#3  0x00007fe213254abd in clone () from /lib64/libc.so.6
Thread 3 (Thread 0x7fe2077fe700 (LWP 22429)):
#0  0x00007fe2135205ec in pthread_cond_wait () from /lib64/libpthread.so.0
#1  0x00007fe20f60c88b in frame_worker_thread () from /usr/lib64/libavcodec.so.54
#2  0x00007fe21351bda6 in start_thread () from /lib64/libpthread.so.0
#3  0x00007fe213254abd in clone () from /lib64/libc.so.6
Thread 2 (Thread 0x7fe206ffd700 (LWP 22430)):
#0  0x00007fe2135205ec in pthread_cond_wait () from /lib64/libpthread.so.0
#1  0x00007fe20f60c88b in frame_worker_thread () from /usr/lib64/libavcodec.so.54
#2  0x00007fe21351bda6 in start_thread () from /lib64/libpthread.so.0
#3  0x00007fe213254abd in clone () from /lib64/libc.so.6
Thread 1 (Thread 0x7fe2141bb700 (LWP 22425)):
#0  0x00007fe21324bb73 in poll () from /lib64/libc.so.6
#1  0x00007fe21377b8d6 in g_main_context_iterate.clone.6 () from /usr/lib64/libglib-2.0.so.0
#2  0x00007fe21377bd2a in g_main_loop_run () from /usr/lib64/libglib-2.0.so.0
#3  0x0000000000401764 in main (argc=3, argv=0x7fff3f0f3728) at main.c:157
*/


#include <stdio.h>
#include <gst/gst.h>
#include <glib.h>

// Moved to global vars
// Because too lazy to make up an app context struct
// to pass to event callback procedure

GMainLoop *loop;
GstElement *pipeline, *source, *typefind, *demuxer, *audio_decoder, *video_decoder, *audio_conv, *video_conv_1, *video_conv_2, *video_filter_1, *video_filter_2, *audio_encoder, *video_encoder, *muxer, *sink, *q1, *audio_queue, *video_queue, *audio_sink, *video_sink_1, *video_sink_2, *tee, *surf_queue_1, *surf_queue_2;
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
	typefind       = gst_element_factory_make ("typefind", "typefinder-1");
	q1             = gst_element_factory_make ("queue", "q1");
	blockpad       = gst_element_get_static_pad (q1, "src");
	//demuxer        = gst_element_factory_make ("qtdemux", "demuxer");
	audio_queue    = gst_element_factory_make ("queue", "audio-queue");
	video_queue    = gst_element_factory_make ("queue", "video-queue");
	audio_decoder  = gst_element_factory_make ("decodebin", "audio-decoder");
	video_decoder  = gst_element_factory_make ("decodebin", "video-decoder");
	audio_conv     = gst_element_factory_make ("audioconvert", "audio-converter");
	audio_sink     = gst_element_factory_make ("alsasink", "audio-output");
	tee            = gst_element_factory_make ("tee", "video-tee");
	video_conv_1   = gst_element_factory_make ("vspmfilter", "video-converter-1");
	video_conv_2   = gst_element_factory_make ("vspmfilter", "video-converter-2");
	video_filter_1 = gst_element_factory_make ("capsfilter", NULL);
	video_filter_2 = gst_element_factory_make ("capsfilter", NULL);
	surf_queue_1   = gst_element_factory_make ("queue", "surf-queue-1");
	surf_queue_2   = gst_element_factory_make ("queue", "surf-queue-2");
	video_sink_1   = gst_element_factory_make ("waylandsink", "video-output-1");
	video_sink_2   = gst_element_factory_make ("waylandsink", "video-output-2");

	if (!pipeline || !source || !typefind || !q1 || !blockpad /*|| !demuxer*/ || !audio_queue || !video_queue || !audio_decoder || !video_decoder ||
	    !audio_conv || !video_conv_1 || !video_conv_2 || !video_filter_1 || !video_filter_2 || !audio_sink || !video_sink_1 || !video_sink_2) {
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
	g_object_set (G_OBJECT (video_filter_1), "caps", filtercaps, NULL);
	gst_caps_unref (filtercaps);

	filtercaps = gst_caps_new_simple ("video/x-raw",
	                                  "format", G_TYPE_STRING, "NV12",
	                                  "width", G_TYPE_INT, 720,
	                                  "height", G_TYPE_INT, 480,
	                                  NULL);
	g_object_set (G_OBJECT (video_filter_2), "caps", filtercaps, NULL);
	gst_caps_unref (filtercaps);

	g_object_set (G_OBJECT (video_sink_1), "surface_id", 4194305, NULL);
	g_object_set (G_OBJECT (video_sink_2), "surface_id", 8388609, NULL);

	/* we add a message handler */
	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
	gst_object_unref (bus);

	/* we add all elements into the pipeline */
	gst_bin_add_many (GST_BIN (pipeline),
	                  source, typefind, q1, /*demuxer, */audio_queue, video_queue, audio_decoder, video_decoder,
	                  audio_conv, video_conv_1, video_conv_2, video_filter_1, video_filter_2, audio_sink,
	                  video_sink_1, video_sink_2, tee, surf_queue_1, surf_queue_2, NULL);

	/* we link the elements together */
	gst_element_link (source, typefind);
	//gst_element_link (q1, demuxer);
	gst_element_link_many (audio_queue, audio_decoder, NULL);
	gst_element_link_many (video_queue, video_decoder, NULL);
	gst_element_link_many (audio_conv, audio_sink, NULL);
	gst_element_link_many (video_conv_1, video_filter_1, surf_queue_1, video_sink_1, NULL);
	gst_element_link_many (video_conv_2, video_filter_2, surf_queue_2, video_sink_2, NULL);

	/* tee part start */
	GstPadTemplate *tee_src_pad_template;
	GstPad *tee_q1_pad, *tee_q2_pad;
	GstPad *q1_pad, *q2_pad;

	/* Manually link the Tee, which has "Request" pads */
	if ( !(tee_src_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (tee), "src_%u"))) {
		gst_object_unref (pipeline);
		g_critical ("Unable to get pad template");
		return -1;
	}

	/* Obtaining request pads for the tee elements*/
	tee_q1_pad = gst_element_request_pad (tee, tee_src_pad_template, NULL, NULL);
	g_print ("Obtained request pad %s for q1 branch.\n", gst_pad_get_name (tee_q1_pad));
	q1_pad = gst_element_get_static_pad (video_conv_1, "sink");

	tee_q2_pad = gst_element_request_pad (tee, tee_src_pad_template, NULL, NULL);
	g_print ("Obtained request pad %s for q2 branch.\n", gst_pad_get_name (tee_q2_pad));
	q2_pad = gst_element_get_static_pad (video_conv_2, "sink");

	/* Link the tee to the queue 1 */
	if (gst_pad_link (tee_q1_pad, q1_pad) != GST_PAD_LINK_OK ) {

		g_critical ("Tee for q1 could not be linked.\n");
		gst_object_unref (pipeline);
		return -1;

	}

	/* Link the tee to the queue 2 */
	if (gst_pad_link (tee_q2_pad, q2_pad) != GST_PAD_LINK_OK) {

		g_critical ("Tee for q2 could not be linked.\n");
		gst_object_unref (pipeline);
		return -1;
	}

	gst_object_unref (q1_pad);
	gst_object_unref (q2_pad);
	/* tee part end */

	g_signal_connect (typefind, "have-type", G_CALLBACK (cb_typefound), NULL);
	//g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_demuxer_pad_added), NULL);
	g_signal_connect (audio_decoder, "pad-added", G_CALLBACK (on_decoder_pad_added), audio_conv);
	g_signal_connect (video_decoder, "pad-added", G_CALLBACK (on_decoder_pad_added), tee);

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

