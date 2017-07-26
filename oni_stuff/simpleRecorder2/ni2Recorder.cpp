#include <openni2/OpenNI.h>
#include <opencv2/opencv.hpp>
#include <iostream>

#include <boost/filesystem.hpp>


bool imageReg = true;
bool imageSync = true;
bool OpenNIDebug = false;
void parseArgs(int argc,char *argv[]){
  for(int i = 0; i < argc; i++){
    if (std::string(argv[i]) == "-noReg" || (std::string(argv[i]) == "-noreg" )) {
        imageReg = false;
        break;
    }else if (std::string(argv[i]) == "-reg" || std::string(argv[i]) == "-Reg"){
        imageReg = true;
        break;
    }else if (std::string(argv[i]) == "-sync"){
        imageSync = true;
    }else if (std::string(argv[i]) == "-nosync"){
        imageSync = false;
    }else if (std::string(argv[i]) == "-d"){
        OpenNIDebug = true;
    }else if (std::string(argv[i]) == "-noD"){
        OpenNIDebug = false;
    }
  }
}    

int main(int argc, char *argv[])
{
  std::cout << "we" << std::endl;
  parseArgs(argc,argv);

  openni::OpenNI::initialize();


  //MAX DEBUG
  if(OpenNIDebug){
    openni::OpenNI::setLogConsoleOutput (TRUE);
    openni::OpenNI::setLogMinSeverity(0);
  }
  
  openni::Status r;

  openni::Device device;
  r = device.open(openni::ANY_DEVICE);
  if (r != openni::STATUS_OK){
    if(openni::OpenNI::getExtendedError() != ""){
      std::cout << "OpenNi2 open failed: " <<  openni::OpenNI::getExtendedError() << std::endl;
    }else
      std::cout << "OpenNi2 open failed, for an unknown reason. (maybe a empty file?)" << std::endl;
//    return XN_STATUS_DEVICE_NOT_CONNECTED;
  }

  openni::VideoStream image,depth;

  r = image.create(device, openni::SENSOR_COLOR);
  if (r != openni::STATUS_OK){
    std::cout << "OpenNi2 create stream failed: " <<  openni::OpenNI::getExtendedError() << std::endl;
//    return XN_STATUS_DEVICE_NOT_CONNECTED;
  }
  
  r = depth.create(device, openni::SENSOR_DEPTH);
  if (r != openni::STATUS_OK){
    std::cout << "OpenNi2 create stream failed: " <<  openni::OpenNI::getExtendedError() << std::endl;
//    return XN_STATUS_DEVICE_NOT_CONNECTED;
  }


  if(imageReg){
    r = device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
    if (r != openni::STATUS_OK)
      std::cout << "OpenNi2 Image Registration failed: " <<  openni::OpenNI::getExtendedError() << std::endl;
  }
  if(imageSync){
    r = device.setDepthColorSyncEnabled(true);
    if (r != openni::STATUS_OK)
      std::cout << "OpenNi2 Depth Color Sync  failed: " << r << " : " <<  openni::OpenNI::getExtendedError() << std::endl;
  }


  r = image.start();
  if (r != openni::STATUS_OK){
    std::cout << "OpenNi2 start stream  failed: " <<  openni::OpenNI::getExtendedError() << std::endl;
//    return XN_STATUS_DEVICE_NOT_CONNECTED;
  }

  r = depth.start();
  if (r != openni::STATUS_OK){
    std::cout << "OpenNi2 start stream  failed: " <<  openni::OpenNI::getExtendedError() << std::endl;
//    return XN_STATUS_DEVICE_NOT_CONNECTED;
  }



  openni::VideoFrameRef dFrame, iFrame;
  cv::Mat iMat, dMat;  
  int cnt=0;


  boost::filesystem::create_directory("colourframes");
  boost::filesystem::create_directory("depthframes");

  while(true){
    
    depth.readFrame(&dFrame);
    image.readFrame(&iFrame);

    int iH = iFrame.getHeight();
    int iW = iFrame.getWidth();
    
    iMat = cv::Mat(iH, iW, CV_8UC3, (openni::RGB888Pixel*) iFrame.getData());
    cv::cvtColor(iMat, iMat, CV_RGB2BGR);
    imwrite("./colourframes/Image" + std::to_string(cnt) + ".jpg",iMat);

    int dH = dFrame.getHeight();
    int dW = dFrame.getWidth();
    
    dMat = cv::Mat(dH, dW, CV_16U, (openni::DepthPixel*) dFrame.getData());
    imwrite("./depthframes/Image" + std::to_string(cnt) + ".png",dMat);
    
    if(! (cnt%50))
      std::cout << "Frame: " << cnt << std::endl;
    cnt++;
  }

  openni::OpenNI::shutdown();
  return 0;
}


