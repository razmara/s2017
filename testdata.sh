FILES="livingroom1 livingroom2 office1 office2"
URL="http://redwood-data.org/indoor/data/"

FRAGS="-fragments-pcd.zip"
EVALS="-evaluation.zip"
ONIS=".oni.zip"
TRAJ="-traj.txt"

TYPES=$FRAGS" "$EVALS" "$ONIS" "$TRAJ

CURDIR=`pwd`
DIR="./tmp2/"
TESTDATADIR="/home/scott/gd/metaoptima/3D Imaging Project/test_data/"

SAMPLES=50

for FILE in $FILES; do
  for TYPE in $TYPES; do
      cd $CURDIR
      cd $DIR
      mkdir -p dl
      cd dl
    if [ ! -e $FILE$TYPE ] ; then
      wget $URL$FILE$TYPE
      cd ..
      mkdir -p $FILE
      cd $FILE
      ln -s ../dl/$FILE$TYPE ./
    fi;
  done
  cd $CURDIR 
  cd $DIR
  cd $FILE

  if [ ! -e unzip_done ]; then

  rm -rf fragments evaluation oni traj
  mkdir -p fragments evaluation oni traj
  
  cd fragments
  unzip ../$FILE$FRAGS &
  cd ..
  
  cd evaluation
  unzip ../$FILE$EVALS &
  cd ..
  
  cd oni
  unzip ../$FILE$ONIS &
  cd ..

  cd traj
  unzip ../$FILE$TRAJ &
  cd ..
  
  touch unzip_done
  
  fi
  
done 


wait

echo "Downloaded all files"

##FILES ALL SETUP AN UNZIPPED

#COPY THE ONIS:

for FILE in $FILES; do
  if [[ ! -e "$TESTDATADIR/0_oni_files/$FILE.tar.xz" ]] ; then
    cd $CURDIR
    cd $DIR
    cd $FILE
    echo "Copying " $FILE "'s oni into google drive..."
    #tar -c oni | xz -9 -T8 > $TESTDATADIR/0_oni_files/$FILE.tar.xz &
  fi
done

wait
#Wait for all the oni files to copy

#PCL_KINFU!

PCL_KINFU_BIN="/home/scott/pcl_merging/pcl_copyin_funcs/build/bin/pcl_kinfu_largeScale"

for FILE in $FILES; do
  cd $CURDIR
  cd $DIR
  cd $FILE
  if [ ! -e $FILE_kinfu.tar.xz ]; then
    mkdir -p kinfu
    cd kinfu
    (
    $PCL_KINFU_BIN -r -ic -sd 10 -oni ../oni/*.oni -vs 4 --fragment $SAMPLES --rgbd_odometry --record_log ./100-0.log &
    PID=$!
    sleep $((20*60*60))
    kill $PID
    #TODO: Add camera param(?)
    wait
    cd ..
    tar -c kinfu | xz -9 -T8 > $FILE_kinfu.tar.xz
#    cp $FILE_kinfu.tar.xz $TESTDATADIR/1_kinfu_results/ &
    ) &
  fi
done

wait;

echo "PCL KINFU RUN ON ALL DA THINGS"


#exit

#TODO

GR_BIN="/home/scott/s2017/ER_port/bin/GlobalRegistration"

for FILE in $FILES; do
  cd $CURDIR
  cd $DIR
  cd $FILE
  if [ ! -e GR.tar.xz ]; then
    rm -rf ./globalregistration
    mkdir -p ./globalregistration
    cd ./globalregistration/
    ln -s ../kinfu ./
    (
    $GR_BIN  ./kinfu/ ./kinfu/100-0.log 50 &> GR_RUN_LOG.txt && \
    cd .. && \
    tar -c ./globalregistration | xz -9 -T8 > GR.tar.xz
    ) &
  fi
done  


wait
