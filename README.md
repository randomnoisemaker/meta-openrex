# meta-openrex
FEDEVEL Yocto Project for OpenRex
 
# How to compile & use software for OpenRex 
 
Here you will find some basic info about how to start with YOCTO and OpenRex. If you follow the steps below, you should be able to compile the source code. 
 
 
In case you would like to know more about YOCTO & How To Use It, for example how to create, modify, compile and use meta-openrex or how to create your own custom layer, have a look at OpenRex website: http://www.imx6rex.com/open-rex/software/
 
### 1) Install the repo utility
    mkdir ~/bin
    curl http://commondatastorage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
    chmod a+x ~/bin/repo
 
### 2) Get the YOCTO project
    cd
    mkdir fsl-community-bsp
    cd fsl-community-bsp
    PATH=${PATH}:~/bin
    repo init -u https://github.com/Freescale/fsl-community-bsp-platform -b dunfell
 
### 3) Add openrex support - create manifest 
    cd ~/fsl-community-bsp/
    mkdir -pv .repo/local_manifests/
 
Copy and paste this into your Linux host machine 
 
    cat > .repo/local_manifests/imx6openrex.xml << EOF
    <?xml version="1.0" encoding="UTF-8"?>
    <manifest>
     
      <remote fetch="git://github.com/randomnoisemaker" name="randomnoisemaker"/>
     
      <project remote="randomnoisemaker" revision="dunfell" name="meta-openrex" path="sources/meta-openrex">
        <copyfile src="openrex-setup.sh" dest="openrex-setup.sh"/>
      </project>
    </manifest>
    EOF
 
### 4) Sync repositories
    repo sync
 
### 5) ~~Add OpenRex meta layer into BSP~~
    ~~source openrex-setup.sh~~
 
# Building images
    cd ~/fsl-community-bsp/
 
### Currently Supported machines <machine name>
Here is a list of 'machine names' which you can use to build OpenRex images. Use the 'machine name' based on the board you have:
 
    imx6s-openrex
    imx6q-openrex
     
### Setup and Build Console image
    export CROSS_COMPILE=arm-linux-gnueabihf-
    export ARCH=arm
    cd ~/fsl-community-bsp-openrex/sources/poky
    source oe-init-build-env build-openrex
    

### Include compiling vars in local.conf
Paste the follwing vars into the file

    nano ~/fsl-community-bsp-openrex/sources/poky/build-openrex/conf/local.conf
    MACHINE ??= "imx6q-openrex"
    PREFERRED_PROVIDER_virtual/kernel = "linux-openrex"
    PREFERRED_VERSION_linux-fslc = "5.4"
    PREFERRED_PROVIDER_u-boot = "u-boot-openrex"
    PREFERRED_PROVIDER_virtual/bootloader = "u-boot-openrex"

### Add OpenRex meta layer
Edit the following file and include these line in BBLAYERS
    
    nano ~/fsl-community-bsp-openrex/sources/poky/build-openrex/conf/bblayers.conf
      /home/fernando/fsl-community-bsp-openrex/sources/meta-openrex \
      /home/fernando/fsl-community-bsp-openrex/sources/meta-freescale \

### Proceed to compile 
    cd ~/fsl-community-bsp-openrex/sources/poky/build-openrex/
    bitbake core-image-base
 
# Creating SD card
Output directories and file names depend on what you build. Following example is based on running 'bitbake core-image-base':
 
 
    umount /dev/sdb?
    gunzip -c ~/fsl-community-bsp/build-openrex/tmp/deploy/images/imx6q-openrex/core-image-base-imx6q-openrex.sdcard.gz > ~/fsl-community-bsp/build-openrex/tmp/deploy/images/imx6q-openrex/core-image-base-imx6q-openrex.sdcard
    sudo dd if=~/fsl-community-bsp/build-openrex/tmp/deploy/images/imx6q-openrex/core-image-base-imx6q-openrex.sdcard of=/dev/sdb
    umount /dev/sdb?
     
# Testing it on OpenRex (initial uBoot runs from SPI)
To test your uBoot on SD card, plug in the card which you have just created into an OpenRex board. Reset the OpenRex board (press "Reset" button), interrupt the uBoot countdown (press "Spacebar" or the "Enter" key) and run following command:
 
    mw.l 0x020d8040 0x2840; mw.l 0x020d8044 0x10000000; reset
 
# Updating OpenRex
TO
