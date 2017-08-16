#!/bin/bash

#This is to let me run various programs, sequentally, by simply adding them to a queue.


QUEUE="/tmp/myque"

#This is the server.
QServer(){
  cd /tmp

  qi=0;
  while true ; do
    if [ -e $QUEUE ] && [ -s $QUEUE ] ; then
      echo $(head -n 1 $QUEUE) 2>&1 | tee queue_$qi.log
      eval $(head -n 1 $QUEUE) 2>&1 | tee -a queue_$qi.log 
      tail -n +2 $QUEUE > $QUEUE.tmp
      mv $QUEUE.tmp $QUEUE
      let qi++
    else
      sleep 5;
    fi
   
    if [ -e $QUEUE.add ]; then 
      mv $QUEUE.add $QUEUE.tmp
      cat $QUEUE.tmp >> $QUEUE
      rm $QUEUE.tmp
    fi
  done > /tmp/queue.log

}

#Add to queue
QAdd(){
  echo " cd \"`pwd`\" ; $@" >> $QUEUE.add
}

#Remove from queue
#QRem(){
#  
#}
