/*****************************************************************************
*                                                                            *
*  OpenNI 1.x Alpha                                                          *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <XnOpenNI.h>
#include <XnLog.h>
#include <XnCppWrapper.h>
#include <XnFPSCalculator.h>

#include <iostream>

#include <opencv2/opencv.hpp>


//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------

bool erroring(XnStatus nRetVal){
    if (nRetVal != XN_STATUS_OK){
      std::cout << xnGetStatusString(nRetVal) << std::endl;
      return false;
    }  
    return true;
}

using namespace xn;

int main()
{
	XnStatus nRetVal = XN_STATUS_OK;

	Context context;
	ScriptNode scriptNode;
	EnumerationErrors errors;

  context.Init();
  
  xn::ImageGenerator imgGen;

  nRetVal = imgGen.Create(context);
  erroring(nRetVal);  

  nRetVal = imgGen.StartGenerating();
  erroring(nRetVal);  

  int i=0;
  while (true){
    nRetVal = context.WaitOneUpdateAll(imgGen);
    std::cout << i << std::endl;

    if(!erroring(nRetVal))
      break;

    
    XnMapOutputMode mode;
    imgGen.GetMapOutputMode(mode);
    

    int height = mode.nYRes;
    int width = mode.nXRes;
    int dataSize = imgGen.GetBytesPerPixel();
    
    std::cout << "Height: " << height << ", Width: " << width << ", Size: " << dataSize << std::endl;
    
    cv::Mat img = cv::Mat( height, width, CV_8UC3, (void *) imgGen.GetData());
//    cv::cvtColor(img,img, CV_RGB2BGR);
 
    cv::imwrite("img"+std::to_string(i)+".jpg", img);
    i++;
  }
	
  context.Release();

	return 0;
}