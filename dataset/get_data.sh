#!/bin/bash

WGET_ARGS="--continue "
ADIR=`pwd`
DLDIR=$ADIR/dl


mkdir -p $DLDIR

for i in {00000..99999}; do
  cd $DLDIR

  #As not all seqences have corrisponding models, download the model first, then get it's seqence.
  wget "http://3dscan.stanford.edu/data/mesh/"$i".ply" $WGET_ARGS &&\
  wget "http://3dscan.stanford.edu/data/seq/"$i".zip" $WGET_ARGS || \
  continue

#Comment this out to prevent automatic extraction.
  cd $ADIR

  mkdir $i
  cd $i
  unzip $DLDIR/$i.zip
  ln -s $DLDIR/$i.ply ./
  cd $ADIR

done

