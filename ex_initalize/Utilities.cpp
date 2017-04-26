//
//

#include "Utilities.h"

bool initalizeOpenNI()
{
  if (OpenNI::initialize() != STATUS_OK) {
    cout << "Failed to Initialize OpenNI" << endl;
    cout << OpenNI::getExtendedError() << endl;
    return false;
  }
  return true;
}

void closeOpenNI()
{
  OpenNI::shutdown();
}



