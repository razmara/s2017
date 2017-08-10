URL="http://redwood-data.org/indoor/data/"
FILES="livingroom1 livingroom2 office1 office2"
TYPES="-color.zip -depth-clean.zip -depth-simulated.zip -traj.txt"

#SETUP DIRS.


convertName(){
  #Arg 1 is type to move it to.
  #Assumes local
  NUM=`ls [0-9]*.* | wc -l` 
  for j in `seq 0 $((NUM-1))` ; do
    T=`printf "%05d\n" $j`
    mv $T.* Image$j.$1
  done 
  
}

for i in $FILES; do
  mkdir -p $i
  cd $i
  rm -rf  colourframes depthframes
  mkdir -p colourframes depthframes
  cd colourframes
  wget $URL$i-color.zip
  unzip *-color.zip -q
  convertName jpg
  cd ..
  cd depthframes
  wget $URL$i-depth-simulated.zip
  unzip *-depth-simulated.zip -q
  convertName png
  cd ..
  cd ..
done
