#include <iostream>

#include "er_helper.h"

int
main (int argc, char** argv)
{
  RGBDTrajectory traj;
  traj.LoadFromFile(argv[1]);
  
  RGBDTrajectory out;
  out.data_.push_back(traj.data_[0]);
   
  for(int i=1; i < traj.data_.size(); i++){
    out.data_.push_back(traj.data_[i]);
    out.data_[i].transformation_ = (out.data_[i-1].transformation_ * out.data_[i].transformation_ );

//    traj.data_[i].transformation_ = traj.data_[i].transformation_.inverse().eval();
  }

  out.SaveToFile(argv[2]);
}
