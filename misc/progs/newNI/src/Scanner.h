//
//

#ifndef Scanner_h
#define Scanner_h

#include <iostream>
#include <stdio.h>
#include "openni2/OpenNI.h"

using namespace std;
using namespace openni;

class Scanner
{
protected:
  Device device;

  VideoStream infraRedStream;
  VideoStream depthStream;
  VideoStream colourStream;

public:

  Scanner(const char* uri);
  ~Scanner();

  void startScanning();
  void stopScanning();

  void getFrame(SensorType type, VideoFrameRef* frame);
};


#endif /* Scanner_h */
