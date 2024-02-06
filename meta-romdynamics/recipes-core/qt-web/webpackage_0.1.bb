SUMMARY = "QT WebBrowser"
LICENSE = "GPL-3.0"

LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=1ebbd3e34237af26da5dc08a4e440464"

SRC_URI = "file://v1.0.tar.gz"
##SRC_URI[sha256sum] = "3972dc9744f6499f0f9b2dbf76696f2ae7ad8af9b23dde66d6af86c9dfb36986"
SRC_URI[sha256sum] = "23d9b4f07659735ac4dcb6c598fa5d39bd6294b12da2da2c2340a73908a8d068"

S = "${WORKDIR}/git"

do_unpack() {
    # Unpack the downloaded source code archive
    tar xf ${WORKDIR}/$(basename ${SRC_URI}) -C ${S}
}


do_compile() {
    cmake .
    oe_runmake
}

do_install() {
    oe_runmake install
}
