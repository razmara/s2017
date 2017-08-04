#!/bin/bash

pacman -S base base-devel git cuda opencv cmake sudo openssh vim htop ccache

#Enables CCache for all users. (Helpfull for re-building pcl)
echo 'export PATH="/usr/lib/ccache/bin/:$PATH"' >> /etc/bash.bashrc

