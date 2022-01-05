cmake_minimum_required(VERSION 3.5)

project(gstreamer_example LANGUAGES C)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTLIBS REQUIRED
        gobject-2.0
        glib-2.0
        gstreamer-check-1.0)

pkg_search_module(GLIB REQUIRED glib-2.0) 
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-video-1.0)



include_directories(${GSTREAMER_INCLUDE_DIRS})
link_directories(${GSTREAMER_LIBRARIES})


add_executable(gstreamer_pipeline_auto gstreamer_pipeline_auto.c)

add_executable(gstreamer_pipeline_manually gstreamer_pipeline_manually.c)

target_link_libraries(gstreamer_pipeline_auto ${GSTREAMER_LIBRARIES})

target_link_libraries(gstreamer_pipeline_manually ${GSTREAMER_LIBRARIES})

