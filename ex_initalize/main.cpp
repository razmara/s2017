//
//

#include "Scanner.h"
#include "Utilities.h"

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
  
  scanner.stopScanning();
  
  closeOpenNI();
  return 0;
}
