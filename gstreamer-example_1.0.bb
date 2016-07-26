SUMMARY = "gstreamer h.264 file decode/streaming example"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d41d8cd98f00b204e9800998ecf8427e"

DEPENDS = "gstreamer"

CFLAGS += "-pthread"
CFLAGS += "-I${STAGING_INCDIR}/gstreamer-1.0"
CFLAGS += "-I${STAGING_INCDIR}/glib-2.0"
CFLAGS += "-I${STAGING_LIBDIR}/glib-2.0/include"
CFLAGS += "-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0"

S = "${WORKDIR}/gstreamer_example"

do_src() {
    cp -rfp ${TOPDIR}/../source/gstreamer_example ${WORKDIR}/
}

addtask do_src before do_patch after do_unpack

do_compile () {
        oe_runmake
}

do_install_append() {
        rm -rf ${S}/patches
        install -d ${D}${sbindir}
        install -m 0755 ${S}/gstreamer_pipeline_manually ${D}${sbindir}
        install -m 0755 ${S}/gstreamer_pipeline_auto ${D}${sbindir}
}
