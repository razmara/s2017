#include <iostream>

#include "er_helper.h"
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>

int
main (int argc, char** argv)
{
  RGBDTrajectory traj;
  traj.LoadFromFile(argv[1]);
  
  RGBDTrajectory outTraj;
  
  int curFrag=0;
  int maxFrag=0;
  
  for(int i=0; i < traj.data_.size(); i++){
    maxFrag = (traj.data_[i].id1_ > maxFrag) ? traj.data_[i].id1_ : maxFrag;
    maxFrag = (traj.data_[i].id2_ > maxFrag) ? traj.data_[i].id2_ : maxFrag;
  }

  for(int looper=0; looper < maxFrag; looper++){
    std::cout << "Looking for: " << curFrag << endl;
    for(int i=0; i < traj.data_.size(); i++){
      if(traj.data_[i].id1_ == curFrag && traj.data_[i].id2_ == curFrag + 1){
        outTraj.data_.push_back(traj.data_[i]);
        curFrag = traj.data_[i].id2_;
        break;
      }
      if(traj.data_[i].id2_ == curFrag && traj.data_[i].id1_ == curFrag + 1){
        traj.data_[i].transformation_ = traj.data_[i].transformation_.inverse().eval();
        outTraj.data_.push_back(traj.data_[i]);
        curFrag = traj.data_[i].id1_;
        break;
      }
    }
  
   if(curFrag == maxFrag)
      break;
  
  }
  outTraj.SaveToFile(argv[2]);
}
