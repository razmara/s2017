#include <iostream>

#include "er_helper.h"

int
main (int argc, char** argv)
{
  int start=0;
  int end=-1;

  if(argc >= 4){
    start = atoi(argv[3]);
    end = atoi(argv[4]);
  }

  RGBDTrajectory traj;
  traj.LoadFromFile(argv[1]);
  
  int i = start;
  RGBDTrajectory out;
  out.data_.push_back(traj.data_[i++]); //Push and inc.
   
  while( i < traj.data_.size() && (end != -1 || i < end)){
    out.data_.push_back(traj.data_[i]);
    out.data_[i].transformation_ = (out.data_[i-1].transformation_ * out.data_[i].transformation_ );
    i++;
  }

  out.SaveToFile(argv[2]);
}
