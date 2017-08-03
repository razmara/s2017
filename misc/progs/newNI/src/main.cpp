///////////////////////////////////////////////////////////////////////////////
//
// Simple program that reads depth and color (RGB) images from Primensense
// camera using OpenNI2 and displays them using OpenCV.
//
// Ashwin Nanjappa
///////////////////////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <openni2/OpenNI.h>
#include "Scanner.h"

using namespace openni;
using namespace cv;
using namespace std;

bool initalizeOpenNI()
{
  if (openni::OpenNI::initialize() != STATUS_OK) {
    cout << "Failed to Initialize OpenNI" << endl;
    cout << openni::OpenNI::getExtendedError() << endl;
    return false;
  }
  return true;
}

void closeOpenNI()
{
  openni::OpenNI::shutdown();
}

int main(int argc, const char * argv[])
{
  // Required before any other OpenNI operations occur
  initalizeOpenNI();

  Scanner scanner(ANY_DEVICE);
  VideoFrameRef *frame = new VideoFrameRef();

  scanner.startScanning();

  scanner.getFrame(SENSOR_IR, frame);

  Grayscale16Pixel *data = (Grayscale16Pixel*)frame->getData();


  Mat mat = Mat(frame->getHeight(), frame->getWidth(), 1, data);

  imwrite("bacon.png",mat);

  scanner.stopScanning();

  closeOpenNI();
  //  sleep(999999999);
  return 0;
}
