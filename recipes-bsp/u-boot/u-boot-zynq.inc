require recipes-bsp/u-boot/u-boot.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/u-boot-zynq-git:"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://README;beginline=1;endline=6;md5=157ab8408beab40cd8ce1dc69f702a6c"
SRCREV = "dda3f58af8eb86c649114fa87e35257947d22629"
PV = "z2015.2+git${SRCPV}"

SRC_URI = "git://github.com/Xilinx/u-boot-xlnx.git;branch=master \
	file://0001-Add-topic-miami-board-support.patch \
	file://0002-Add-topic_miamiplus-board.patch \
	"
S = "${WORKDIR}/git"

PACKAGE_ARCH = "${MACHINE_ARCH}"

# Workaround for borked SSL dependendy
DEPENDS += "openssl-native"
EXTRA_OEMAKE += 'HOSTCC="${BUILD_CC}" HOSTCFLAGS="${BUILD_CFLAGS}" HOSTLD="${BUILD_LD}" HOSTLDFLAGS="${BUILD_LDFLAGS}"'

# workaround non-existent gcc6 header
do_compile_prepend() {
    if [ ! -f "${S}/include/linux/compiler-gcc6.h" ]
    then
        ln -s compiler-gcc5.h "${S}/include/linux/compiler-gcc6.h"
    fi
}
