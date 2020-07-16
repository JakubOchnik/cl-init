# Quick OpenCL initialization
A simple C++ class which allows a user to quickly initalize devices, load platforms, create context and command queue.
Get rid of typing the same boilerplate code all over again!
## List of available methods
```
void loadPlatforms() // loads a list of available platforms
void printBasicPlatformInfo() // prints basic information about available platforms
cl::Platform* getPlatforms(int pNum) // getter method of a selected platform

void loadDevices(int pNum) // loads devices of a selected platform
cl::Device* getDevices(int dNum) // returns a selected device
const std::vector<cl::Device> getDevices() const // returns a vector of available devices
void printBasicDeviceInfo() // prints basic information about available devices

void createBasicContext(int pNum, cl_device_type dType) // creates a basic compute context of selected platform and device type
cl::Context* getContext() // getter method of a context

void createBasicCmdQueue(int dNum) // creates a basic command queue with a selected device
cl::CommandQueue* getCmdQueue() // getter method of a command queue
```
