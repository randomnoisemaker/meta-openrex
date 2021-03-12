# Copyright (C) 2012-2019 O.S. Systems Software LTDA.
# Released under the MIT license (see COPYING.MIT for the terms)

inherit fsl-u-boot-localversion

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/README;md5=30503fd321432fc713238f582193b78e"

DEPENDS += "bison-native"

SRC_URI = "git://github.com/randomnoisemaker/openrex-uboot.git;branch=${SRCBRANCH}"

SRCREV = "5ecf4eadfb3e8382ee2e4c566b01f7afab361b47"
SRCBRANCH = "dunfell"

PV = "v2020.04+git${SRCPV}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"
