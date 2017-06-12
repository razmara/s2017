FILES="livingroom1 livingroom2 office1 office2"
URL="http://redwood-data.org/indoor/data/"


#Prior versions: None - no version, first set.
#Version1.1 - New meshes, samples=50. pcl commit: 04130735f180f8839a37ba9ff0acd88d562bc0c9

VERSION="1.1"


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
    (
    if [ ! -e $FILE.tar.xz ] ; then 
      tar -c oni | xz -9 -T8 > $FILE.tar.xz
    fi
#    if [ $GD ] ; then
      cp $FILE.$VERSION.oni.tar.xz $TESTDATADIR/0_oni_files/
#    fi
    )&
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
  if [ ! -e $FILE.kinfu.$VERSION.tar.xz ]; then
    mkdir -p kinfu
    cd kinfu
    (
    $PCL_KINFU_BIN -r -ic -sd 10 -oni ../oni/*.oni -vs 4 --fragment $SAMPLES --rgbd_odometry --record_log ./100-0.log &
    PID=$!
    sleep $((10*60*60))
    kill $PID
    #TODO: Add camera param(?)
    wait
    cd ..
    tar -c kinfu | xz -9 -T8 > $FILE.kinfu.$VERSION.tar.xz
    cp $FILE.kinfu.$VERSION.tar.xz $TESTDATADIR/1_kinfu_results/ &
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
  if [ ! -e GR.$FILE.$VERSION.tar.xz ]; then
    rm -rf ./globalregistration
    mkdir -p ./globalregistration
    cd ./globalregistration/
    ln -s ../kinfu ./
    (
    $GR_BIN  ./kinfu/ ./kinfu/100-0.log 50 &> GR_RUN_LOG.txt && \
    cd .. && \
    tar -c ./globalregistration | xz -9 -T8 > GR.$FILE.$VERSION.tar.xz
    cp GR.$FILE.$VERSION.tar.xz $TESTDATADIR/2_global_registration_results/ &
    ) &
  fi
done  

wait
echo "Global Registration done!"


#GraphOptimizer

GO_BIN="/home/scott/s2017/ER_port/bin/GraphOptimizer"

for FILE in $FILES; do
  cd $CURDIR
  cd $DIR
  cd $FILE
  if [ ! -e go.$FILE.$VERSION.tar.xz ] ; then
    rm -rf ./go
    mkdir -p ./go
    cd ./go
    ln -s ../globalregistration ./
    (
    # --keep ../sandbox/keep.log --refine ../sandbox/pcds/reg_refine_all.log
    $GO_BIN -w 100  --odometry ./globalregistration/odometry.log --odometryinfo globalregistration/odometry.info --loop ./globalregistration/result.txt --loopinfo ./globalregistration/result.info --pose ../globalregistration/pose.log &> go.run.log.txt && \
    cd .. && \
    tar -c ./go | xz -9 -T8 >  go.$FILE.$VERSION.tar.xz && \
    cp go.$FILE.$VERSION.tar.xz $TESTDATADIR/3_go/ &
    ) &
  fi
done

wait

echo "Graph Optmizer done."


#BuildCorrispondence

BC_BIN="/home/scott/s2017/ER_port/bin/BuildCorrespondence"

for FILE in $FILES; do
  cd $CURDIR
  cd $DIR
  cd $FILE
  if [ ! -e bc.$FILE.$VERSION.tar.xz ] ; then
    rm -rf ./bc
    mkdir -p ./bc
    cd ./bc
    ln -s ../go ./
    (
    # --reg_traj ../sandbox/pcds/reg_refine_all.log
    $BC_BIN --registration --reg_dist 0.05 --reg_ratio 0.25 --reg_num 0 --save_xyzn &> bc.run.log.txt && \
    cd .. && \
    tar -c ./bc | xz -9 -T8 >  bc.$FILE.$VERSION.tar.xz && \
    cp bc.$FILE.$VERSION.tar.xz $TESTDATADIR/4_bc/ &
    ) &
  fi
done

wait

echo "Done BuildCorrispondence"

#FragmentOptmizer


FO_BIN="/home/scott/s2017/ER_port/bin/FragmentOptimizer"

for FILE in $FILES; do
  cd $CURDIR
  cd $DIR
  cd $FILE
  if [ ! -e fo.$FILE.$VERSION.tar.xz ] ; then
    rm -rf ./fo
    mkdir -p ./fo
    cd ./fo
    ln -s ../bc ./
    (
    NUMPCDS=$(ls -l ./bc/go/globalregistration/kinfu/cloud_bin_*.pcd | wc -l | tr -d ' ')
    #--registration ../sandbox/reg_output.log 
    $FO_BIN --slac --rgbdslam ./bc/go/globalregistration/init.log --dir ./bc/go/globalregistration/kinfu/ --num $NUMPCDS --resolution 12 --iteration 10 --length 4.0 --write_xyzn_sample 10 &>fo.run.log.txt && \
    cd .. && \
    tar -c ./fo | xz -9 -T8 >  fo.$FILE.$VERSION.tar.xz && \
    cp fo.$FILE.$VERSION.tar.xz $TESTDATADIR/5_fo/ &
    ) &
  fi
done

wait

echo "Done FragmentOptimizer"
