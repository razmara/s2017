//
//

#include "Scanner.h"

Scanner::Scanner(const char* uri)
{
  // Open the device
  if (device.open(ANY_DEVICE) != STATUS_OK) {
    cout << "Problem loading device" << endl;
  }
  else {

    // Open the InfraRed stream if availiable
    if (device.hasSensor(SENSOR_IR))
      if (infraRedStream.create(device, SENSOR_IR) != STATUS_OK)
        cout << "Problem creating the ifra red Stream" << endl;

    // Open the depth stream if availiable
    if (device.hasSensor(SENSOR_DEPTH))
      if (depthStream.create(device, SENSOR_DEPTH) != STATUS_OK)
        cout << "Problem creating the depth Stream" << endl;

    // Open the colour stream if availiable
    if (device.hasSensor(SENSOR_COLOR))
      if (colourStream.create(device, SENSOR_COLOR) != STATUS_OK)
        cout << "Problem creating the colour Stream" << endl;
  }
  
}

Scanner::~Scanner()
{
  infraRedStream.destroy();
  depthStream.destroy();
  colourStream.destroy();

  device.close();
}


void Scanner::startScanning()
{
  if(infraRedStream.isValid())
    infraRedStream.start();

  if(depthStream.isValid())
    depthStream.start();

  if(colourStream.isValid())
    colourStream.start();
}


void Scanner::stopScanning()
{
  if(infraRedStream.isValid())
    infraRedStream.stop();

  if(depthStream.isValid())
    depthStream.stop();

  if(colourStream.isValid())
    colourStream.stop();
}

void Scanner::getFrame(SensorType type, VideoFrameRef *frame)
{
  switch (type) {
    case SENSOR_IR:
      infraRedStream.readFrame(frame);
      break;

    case SENSOR_DEPTH:
      depthStream.readFrame(frame);
      break;

    case SENSOR_COLOR:
      colourStream.readFrame(frame);
      break;

    default:
      break;
  }
}
