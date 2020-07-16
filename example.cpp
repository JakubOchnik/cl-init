#include "clInit.h"
#include <iostream>

int main() {
	devInit x;
	x.loadPlatforms();
	x.printBasicPlatformInfo();
	x.loadDevices(0);
	x.printBasicDeviceInfo();
	x.createBasicContext(0, CL_DEVICE_TYPE_GPU);
	x.createBasicCmdQueue();
	std::cin.get();
	return 0;
}