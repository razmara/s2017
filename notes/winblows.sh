#!/bin/bash

echo "THIS SCRIPT ISNT TESTED, AND IS MORE OF A LOG OF WHAT I DID, KINDA SCRIPTING IT, BUT NOT QUITE."
exit

SOURCEDIR="/d/source"

#Note Boost is done as they said on their site.

#Note: Eigen was built very basically with cmake, it seemed to work.

#FLANN:

  #Needs: hdf5
    cd SOURCEDIR
    #DL hdf5
    wget "https://support.hdfgroup.org/ftp/HDF5/current18/src/hdf5-1.8.18.zip"
    unzip.exe /hdf5-1.8.18.zip
    cd hdf5-1.8.18
    mkdir cmake
    cd cmake
    
    #Not 100% sure about these
    HDF5ARGS="-DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_EXECS=ON"

    cmake ../ $HDF5ARGS

    echo "You now need to run VSSTUDIO as admin, and build_all, and then build the INSTALL thing... and hopefully life works out for you."
    read

  #
  FLANNARGS=$FLANNARGS" -DHDF5_DIR=C:/Program\ Files\ (x86)/HDF_Group/HDF5/1.8.18/cmake"


  #Needs: Octave (or matlab...)
    #Also wants older windows, and java...
    #-DOCD_CMD=C:/Octave/Octave-4.2.1/bin/octave-cli.exe
  #Attempt1: installer
  # -seemed to work.

  #I then attempted to see if flan found HDF5, and it didn't, so I installed it without it as apprently that's possible...


