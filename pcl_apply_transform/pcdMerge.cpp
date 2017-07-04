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
  std::cout << "Usage: " << program_name << " input_cloud_filename.[pcd|ply]  input2_cloud_filename.[pcd|ply]  output_cloud_filename.pcd " << std::endl;
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

  // Fetch point cloud filename in arguments | Works with PCD and PLY files
  std::vector<int> filenames;
  bool file_is_pcd = false;


  filenames = pcl::console::parse_file_extension_argument (argc, argv, ".pcd");

    if (filenames.size () != 3) {
      showHelp (argv[0]);
      return -1;
    } else {
      file_is_pcd = true;
    }

  std::vector<pcl::PointCloud<pointType>::Ptr> source_clouds; // (new pcl::PointCloud<pointType> ());
  for(int i=0; i <  filenames.size() -1 ; i++){ //Last one is the output.
  // Load file | Works with PCD and PLY filesV
 
    pcl::PointCloud<pointType>::Ptr source_cloud  (new pcl::PointCloud<pointType> ());
    source_clouds.push_back(source_cloud);  
  

    if (file_is_pcd) {
      if (pcl::io::loadPCDFile (argv[filenames[i]], *source_cloud) < 0)  {
        std::cout << "Error loading point cloud " << argv[filenames[i]] << std::endl << std::endl;
        return -1;
      }
    } else {
      if (pcl::io::loadPLYFile (argv[filenames[i]], *source_cloud) < 0)  {
        std::cout << "Error loading point cloud " << argv[filenames[i]] << std::endl << std::endl;
        return -1;
      }
    }
    
    
  }

  pcl::PointCloud<pointType>::Ptr result (new pcl::PointCloud<pointType> ());
    
  for(int i=0; i < source_clouds.size() ; i++){
    *result += *source_clouds[i];
  }


  pcl::io::savePCDFile("fun.pcd", *result);
  return 0;
}

