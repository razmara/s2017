#!/bin/bash

if [ ! -e setup_dirs.sh ] ; then
  echo "Please run it from local directory."
  exit
fi

cd ..

MASTERDIR=`pwd`

updateSub(){
  git submodule init ./
  git submodule update --remote ./
}

cd OpenNI2
updateSub
git checkout devmerge
cd aur
makepkg
sudo pacman -U *.pkg.tar.xz 

cd $MASTERDIR
cd libfreenect2
updateSub
cd aur
makepkg
sudo pacman -U *.pkg.tar.xz 

cd $MASTERDIR
cd setup/pcl
makepkg
sudo pacman -U *.pkg.tar.xz

cd $MASTERDIR
cd ER_port
mkdir build
cd build
cmake ../
make -j4

cd $MASTERDIR

echo "Idk, mostly setup, I think."
