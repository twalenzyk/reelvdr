#!/bin/sh

service reelbox-control stop 

# exit, if any command returns non-zero
set -e

# Absolute path to this script
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in
SCRIPTPATH=$(dirname "$SCRIPT")
cd $SCRIPTPATH

# Make and install graphlcd-tools
cd libs/graphlcd-base 
#make clean install
cd $SCRIPTPATH

# Make and install Reelbox_Control
cd utils/reelbox-control 
make clean install
cd $SCRIPTPATH

# Make and install Reelfptcl
cd utils/reelfpctl
#make clean install
#make install
cd $SCRIPTPATH

# Copy Board detecion script
cp $SCRIPTPATH/sbin/dev_frontpanel.sh /sbin
#detect frontpanel
/sbin/dev_frontpanel.sh
if [ -e /dev/.have_frontpanel ] && [ -e /dev/.fpctl.avr ]; then 
    echo -n "Reelbox-AVR-Frontpanel successfully detected on " && cat /dev/.have_frontpanel
else
    echo "Reelbox-AVR-Frontpanel not found" 
    exit 1
fi

cp $SCRIPTPATH/etc/default/globals /etc/default
cp $SCRIPTPATH/etc/default/sysconfig /etc/default
cp $SCRIPTPATH/etc/init/fpleds.conf /etc/init
cp $SCRIPTPATH/etc/init/frontpanel-pre.conf /etc/init
cp $SCRIPTPATH/etc/init/reelbox-control.conf /etc/init
cp $SCRIPTPATH/etc/init.d/fpleds /etc/init.d
cp $SCRIPTPATH/etc/init.d/reelbox-control /etc/init.d

if [ ! -e /etc/reel ]; then mkdir /etc/reel/ ; fi
#cp $SCRIPTPATH/etc/reel/p.remote.conf /etc/reel/
if [ ! -e /etc/reel/images ]; then mkdir /etc/reel/images ; fi
cp -avr $SCRIPTPATH/archiv/images/* /etc/reel/images
# Register rules for udev

cp $SCRIPTPATH/etc/udev/rules.d/50-reel_frontpanel.rules /etc/udev/rules.d

echo "script finished" 
