SUMMARY = "Qt Web Browser Application"
DESCRIPTION = "A Qt-based web browser application."

LICENSE = "GPL-3.0"
LIC_FILES_CHKSUM = "file://../QWebBrowser/LICENSE;md5=1ebbd3e34237af26da5dc08a4e440464"

SRC_URI = "file://../QWebBrowser/*"

S = "${WORKDIR}/QWebBrowser"

inherit cmake

do_configure() {
    mkdir -p ${B}/build
    cd ${B}/build
    cmake ${S} -DCMAKE_INSTALL_PREFIX=${D}${prefix}
}

do_compile() {
    oe_runmake -C ${B}/build
}

do_install() {
    oe_runmake -C ${B}/build install
}

FILES_${PN} += "${bindir}/*"
