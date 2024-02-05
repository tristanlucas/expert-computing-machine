## For QT Environment Collections.

QT_DEBUG_PLUGINS
DISPLAY DRIVER - 
INIT SCRIPT SAMPLE FOR  qt app.  



## NGINX DEPLOYMENT.
/etc/nginx/conf.d/*.conf
/etc/nginx/site-enabled/*/
**IPV6 PROTOCOL MUST BE CLOSE SCRIPT.**
# WebPage Deployment.
/var/www/nginx/html/index.html



## FOR CUSTOM LAYERS.
1. OS NAME 
2. HOST NAME
4. WIRELESS LAYER
5. SSH NGINX CURL
6. DISPLAY BACKND
7. QT LAYER
8. QT APP
9. SQL




## BITBAKE CHEAT SHEET

bitbake world -c cleanall --continue

## CROSS DEVELOPMENTS
. /home/db/yocto_raspi/rpi_build/tmp/deploy/sdk/qt5_sdk-rpi4/environment-setup-cortexa72-poky-linux


## For QT Environment Collections.

QT_DEBUG_PLUGINS
DISPLAY DRIVER - 

INIT SCRIPT SAMPLE FOR  qt app.  



## NGINX DEPLOYMENT.
/etc/nginx/conf.d/*.conf
/etc/nginx/site-enabled/*/
**IPV6 PROTOCOL MUST BE CLOSE SCRIPT.**
# WebPage Deployment.
/var/www/nginx/html/index.html



## FOR CUSTOM LAYERS.
1. OS NAME 
2. HOST NAME
4. WIRELESS LAYER
5. SSH NGINX CURL
6. DISPLAY BACKND
7. QT LAYER
8. QT APP
9. SQL


## VNC SERVER
x11vnc

## BITBAKE CHEAT SHEET

bitbake world -c cleanall --continue

### #################################################
#### ############### ############# ############## ###
INHERIT += "rm_work"
BB_NUMBER_THREADS = "7" 
# Also, make can be passed flags so it run parallel threads e.g.: 
PARALLEL_MAKE = "-j 7" 
IMAGE_FSTYPES = "rpi-sdimg"
IMAGE_ROOTFS_EXTRA_SPACE = "10485760"
ENABLE_UART = "1"
DISTRO_FEATURES:append = " x11"
## ##############################################################################
## ##############################################################################
## ##############################################################################
## APPLICATION DEPENDENCIES

IMAGE_INSTALL:append = " strace nginx curl x11vnc make cmake openssh-sftp-server rsync" 

## ###############################################################
## QT DEPENDENCIES

IMAGE_INSTALL:append = " $ sudo apt-get install qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5qtbase-tools qtbase qtdeclarative qtimageformats qtmultimedia qtquickcontrols2 qtquickcontrols qtbase-plugins cinematicexperience liberation-fonts"
PACKAGECONFIG_FONTS:append_pn-qtbase = " fontconfig"

## #########################################################################
## SOUND DEPENDENCIES

IMAGE_INSTALL:append = " gstreamer1.0-plugins-good gstreamer1.0-plugins-base gstreamer1.0-plugins-ugly"
LICENSE_FLAGS_ACCEPTED = " commercial commercial_gstreamer1.0-plugins-ugly commercial_gstreamer1.0-plugins-ugly synaptics-killswitch"
PACKAGECONFIG:append_pn-qtmultimedia = " gstreamer alsa" 

## PULSE AUDIO DEPENDENCIES

DISTRO_FEATURES:append = " pulseaudio"
IMAGE_INSTALL:append = " pulseaudio pulseaudio-module-dbus-protocol pulseaudio-server pulseaudio-module-bluetooth-discover pulseaudio-module-bluetooth-policy pulseaudio-module-bluez5-device pulseaudio-module-bluez5-discover alsa-utils alsa-plugins"

## #######################################################################################
## Bluetooth, Wifi, firewall, Driver and Dependencies
MACHINE_FEATURES += " bluetooth"
DISTRO_FEATURES:append = " pi-bluetooth bluez5 bluetooth linux-firmware-bcm43430 linux-firmware-brcmfmac43430"
IMAGE_INSTALL:append = " pi-bluetooth bluez5 bluez5-testtools linux-firmware-bcm43430 i2c-tools hostapd udev-rules-rpi iptables linux-firmware-ralink linux-firmware-rtl8192ce linux-firmware-rtl8192cu linux-firmware-rtl8192su linux-firmware-rpidistro-bcm43430"

## ####################################
## 3.5 inches LCD Display (rpi-base.inc)
overlays/vc4-kms-dsi-waveshare-panel.dtbo \