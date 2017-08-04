#!/bin/bash

MASTERDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../"

updateSub(){
  git submodule init ./
  git submodule update --remote ./
}

echo "Apacman"
sudo pacman -S --needed --asdeps jshon
cd /tmp
curl -O "https://raw.githubusercontent.com/oshazard/apacman/master/apacman"
sudo bash ./apacman -S apacman --noconfirm
apacman -S apacman-deps --noconfirm

echo "OpenNI2"
cd $MASTERDIR
cd OpenNI2
updateSub
git checkout devmerge
cd aur
makepkg -s -i -f

echo "LibFreenect2"
cd $MASTERDIR
cd libfreenect2
updateSub
cd aur
makepkg -s -i -f



echo "PCL"
cd $MASTERDIR
cd setup/pcl
apacman -S flann --noconfirm
makepkg -s -i -f

echo "ER"
cd $MASTERDIR
cd ER_port
mkdir build
cd build
cmake ../
make -j4

cd $MASTERDIR

echo "Idk, mostly setup, I think."
