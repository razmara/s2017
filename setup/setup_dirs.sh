#!/bin/bash

MASTERDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../"

updateSub(){
  git submodule init ./
  git submodule update --remote ./
}

echo "OpenNI2"
cd $MASTERDIR
cd OpenNI2
updateSub
git checkout devmerge
cd aur
makepkg
sudo pacman -U *.pkg.tar.xz 

echo "LibFreenect2"
cd $MASTERDIR
cd libfreenect2
updateSub
cd aur
makepkg
sudo pacman -U *.pkg.tar.xz 

echo "PCL"
cd $MASTERDIR
cd setup/pcl
makepkg
sudo pacman -U *.pkg.tar.xz

echo "ER"
cd $MASTERDIR
cd ER_port
mkdir build
cd build
cmake ../
make -j4

cd $MASTERDIR

echo "Idk, mostly setup, I think."
