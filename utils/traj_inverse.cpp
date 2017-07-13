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
  
  for(int i=0; i < traj.data_.size(); i++){
    traj.data_[i].transformation_ = traj.data_[i].transformation_.inverse().eval();
  }  

  traj.SaveToFile(argv[2]);
}
