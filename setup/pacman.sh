#!/bin/bash

pacman -Syu --needed base base-devel git cuda opencv cmake sudo openssh vim htop ccache jshon qt5

#Enables CCache for all users. (Helpfull for re-building pcl)
echo 'export PATH="/usr/lib/ccache/bin/:$PATH"' >> /etc/bash.bashrc
export  PATH="/usr/lib/ccache/bin/:$PATH"
