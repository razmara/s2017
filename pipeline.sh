
PCL_KINFU(){
  ONI = $1
  SAMPLES = $2
  PCL_KINFU_BIN="~/pcl_merging/pcl_copyin_funcs/build/bin/pcl_kinfu_largeScale"
  PCL_ARGS=" -r -ic -sd 10 -oni "$1" -vs 4 --fragment "$SAMPLES" --rgbd_odometry --record_log ./100-0.log "
  $PCL_KINFU_BIN $PCL_ARGS
}

Pipeline() {
  ONI = $1
  SAMPLES = $2
  CURDIR = `pwd`
  DIR = $CURDIR/ER_$1
  mkdir -p $DIR
  cd $DIR
  
  if [ ! -e $ONI ]; then
    echo "$ONI is not an absolute path (or doesn't exist)"
    exit
  fi

  if [ ! -e kinfu_$ONI.tar.xz ]; then
   mkdir -p kinfu
   cd kinfu
   PCL_KINFU $ONI $SAMPELS
    

  fi
}


Pipeline $1 $2
