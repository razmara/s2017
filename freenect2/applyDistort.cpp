//Hacked togeather libfreenect2 transformation applyer. 
//TODO: make it use saved parameters, instead of present kinect ones.

#include <iostream>

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

#include <opencv2/opencv.hpp>

/*
cv::Mat frameToMat(libfreenect2::Frame frame){
  cv::Mat ret(frame.height,frame.width, CV_8UC3, frame.data);
}

libfreenect2::Frame matToFrame(cv::Mat mat){
  libFreenect2::Frame ret;
  ret.width = mat.cols;
  ret.height = mat.rows;
  ret.bytes_per_pixel = sizeof(char)*3;
  ret.data = mat.at(0,0);
  ret.status = 0;
}

*/
int main(int argc, char * argv[]){

  //Idk, freenect stuff
  libfreenect2::Freenect2 freenect2;
  libfreenect2::Freenect2Device *dev = 0;
  libfreenect2::PacketPipeline *pipeline = 0;

  std::string serial;

  if(freenect2.enumerateDevices() == 0)
  {
    std::cout << "no device connected!" << std::endl;
    return -1;
  }
  serial = freenect2.getDefaultDeviceSerialNumber();
  dev = freenect2.openDevice(serial);

  libfreenect2::Registration* registration = new libfreenect2::Registration(dev->getIrCameraParams(), dev->getColorCameraParams());

  cv::Mat cin,din,cout;
  
  cin = cv::imread(argv[1]);
  din = cv::imread(argv[2]);  
  
  float cx = 0;
  float cy = 0;

  cv::resize(cin, cin, cv::Size(512, 424));
  cv::resize(din, din, cv::Size(512, 424));

  for(int x=0; x < cin.cols; x++){
    for(int y=0; y < cin.rows; y++){
    std::cout << (float) din.at<uchar>(x,y)*100 << std::endl;
    registration->apply(x,y,(float) din.at<uchar>(x,y)*100,cx,cy);
    std::cout << cx << " : " << cy << std::endl;
    }
  }

}
