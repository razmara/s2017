#!/bin/bash

MASTERDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../"

updateSub(){
  cd $MASTERDIR
  cd $1
  git submodule init ./
  git submodule update --remote ./
}

updateSub ElasticReconstructionRelease
updateSub er
updateSub libfreenect2
updateSub pcl
updateSub spcl
updateSub openCV_Traj
updateSub OpenNI2
updateSub SeperateKinfu
updateSub 3d-re
updateSub GraphOptimizerTest
