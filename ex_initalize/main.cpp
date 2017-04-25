
//Simple opening of openNI2.

//Scott Saunders

#include <openni2/OpenNI.h>


int main(){
	auto r = openni::OpenNI::initialize();
	if (r != openni::STATUS_OK)
		printf("FAILED: \n%s\n",openni::OpenNI::getExtendedError());
	return 0;

}

