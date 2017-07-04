#include <iostream>

#include "er_helper.h"
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>

//Allows setting the pointtype
typedef pcl::PointXYZRGBNormal pointType;

// This function displays the help
void
showHelp(char * program_name)
{
  std::cout << std::endl;
  std::cout << "Usage: " << program_name << " cloud_filename.pcd RGBDTrajectoryFile outFile id1 id2 frame" << std::endl;
  std::cout << "Note: results will also be output into a local folder: transforms" << std::endl;
  std::cout << "-h:  Show this help." << std::endl;
}

// This is the main function
int
main (int argc, char** argv)
{

  // Show help
  if (pcl::console::find_switch (argc, argv, "-h") || pcl::console::find_switch (argc, argv, "--help")) {
    showHelp (argv[0]);
    return 0;
  }

  //load-in PCD
  pcl::PointCloud<pointType>::Ptr source_cloud (new pcl::PointCloud<pointType> ());

  if (pcl::io::loadPCDFile (argv[0], *source_cloud) < 0)  {
    std::cout << "Error loading point cloud " << argv[0] << std::endl << std::endl;
    showHelp (argv[0]);
    return -1;
  }


  //Load-in matrixes /log file.
  RGBDTrajectory traj;
  traj.LoadFromFile(argv[1]);
  
  //Find/get transformation matrix:
  Eigen::Matrix4d *transformation_ = NULL; 

  if(traj.data_.size() == 1){
    transformation_ = &(traj.data_[0].transformation_);
  }else{
    if(argc < 5){
      std::cout << "You need to specify the transfomration, as there are more than 1!" << std::endl;
      return -1;
    }
    for(int i=0; i < traj.data_.size(); i++){
      #define data traj.data_[i]
      if(data.id1_ == atoi(argv[3]) &&  data.id2_ == atoi(argv[4]) &&  data.frame_ == atoi(argv[5])){
        transformation_ = &(data.transformation_);
        break;
      }
      #undef data
    }
  }

  if(transformation_ == NULL){
    std::cout << " Transformation matrix is null, aborting!" << endl;
    return -1;
  }
  
  //Apply transformation.
  // Executing the transformation
  pcl::PointCloud<pointType>::Ptr transformed_cloud (new pcl::PointCloud<pointType> ());
  pcl::transformPointCloudWithNormals<pointType> (*source_cloud, *transformed_cloud, *transformation_,true);

  pcl::io::savePCDFile(argv[3], *transformed_cloud);

  return 0;
}

