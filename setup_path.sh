#!/bin/bash

OLDDIR=$DIR
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo $DIR
PATH=$DIR/ER_myfork/bin:$PATH
#PATH=$DIR/ER_port/bin:$PATH
PATH=$DIR/pcl/build/bin:$PATH
PATH=$DIR/3d-re/bin:$PATH
PATH=$DIR/oni_stuff/ni2Recorder/build:$PATH
PATH=$DIR/oni_stuff/ni1Recorder/build:$PATH
PATH=$DIR/oni_stuff/simpleReader1/build:$PATH
PATH=$DIR/oni_stuff/simpleReader2/build:$PATH
PATH=$DIR/utils/build:$PATH
PATH=$DIR/openCV_Traj:$PATH

source $DIR/pipeline.sh

DIR=OLDDIR
