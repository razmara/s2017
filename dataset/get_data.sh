#!/bin/bash

#As not all seqences have corrisponding models, download the model first, then get it's seqence.
for i in {00000..99999}; do
  wget "http://3dscan.stanford.edu/data/mesh/"$i".ply" &&\
  wget "http://3dscan.stanford.edu/data/seq/"$i".zip"
done

