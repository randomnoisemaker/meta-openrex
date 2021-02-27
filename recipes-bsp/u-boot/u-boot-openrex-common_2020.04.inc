# Copyright (C) 2012-2019 O.S. Systems Software LTDA.
# Released under the MIT license (see COPYING.MIT for the terms)

inherit fsl-u-boot-localversion

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/README;md5=30503fd321432fc713238f582193b78e"

DEPENDS += "bison-native"

SRC_URI = "git://github.com/randomnoisemaker/openrex-uboot.git;branch=${SRCBRANCH}"

SRCREV = "c3931878c1d63f2dd49b2572a6430fd1ae4e9a4d"
SRCBRANCH = "dunfell"

PV = "v2020.04+git${SRCPV}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"
