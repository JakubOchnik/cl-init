#include"clInit.h"

devInit::devInit() {
	this->selectedPlatform = 0;
	this->ctx = nullptr;
	this->cmd = nullptr;
}

devInit::~devInit() {

}

void devInit::loadPlatforms() {
	cl::Platform::get(&platforms);
}
const std::vector<cl::Platform> devInit::getPlatforms() const {
	return this->platforms;
}
cl::Platform* devInit::getPlatforms(int pNum) {
	if (pNum >= this->platforms.size())
		return nullptr;
	return &this->platforms[pNum];
}

void devInit::printBasicPlatformInfo() const {
	std::cout << "Number of available OpenCL platforms: " << this->platforms.size() << std::endl;
	std::string tmp;
	cl_uint count = 0;
	for (auto p : this->platforms) {
		p.getInfo((cl_platform_info)CL_PLATFORM_NAME, &tmp);
		std::cout << count << ". " << tmp << std::endl;

		std::string buf;
		p.getInfo((cl_platform_info)CL_PLATFORM_EXTENSIONS, &buf);
		char* tmpstr;
		tmpstr = strtok(&buf[0], " ");
		std::cout << "\tSupported extensions: " << std::endl;
		while (tmpstr != NULL) {
			std::cout << "\t\t" << tmpstr << std::endl;
			tmpstr = strtok(NULL, " ");
		}

		count++;
	}

}


void devInit::loadDevices(int pNum) {
	if (pNum >= platforms.size())
		return;
	this->selectedPlatform = pNum;
	this->platforms[pNum].getDevices(CL_DEVICE_TYPE_ALL, &devices);
}
const std::vector<cl::Device> devInit::getDevices() const {
	return this->devices;
}
cl::Device* devInit::getDevices(int dNum) {
	if (dNum >= this->devices.size())
		return nullptr;
	return &this->devices[dNum];
}

void devInit::printBasicDeviceInfo() const {
	cl_uint count = 0;
	std::string tmp;
	platforms[selectedPlatform].getInfo((cl_platform_info)CL_PLATFORM_NAME, &tmp);
	std::cout << "Number of " << tmp << "devices: " << devices.size() << std::endl;
	for (auto d : devices) {
		d.getInfo(CL_DEVICE_NAME, &tmp);
		std::cout << count << ". " << tmp << std::endl;
		count++;
		cl_device_type dev_type;
		d.getInfo(CL_DEVICE_TYPE, &dev_type);
		if (dev_type & CL_DEVICE_TYPE_GPU)
			std::cout << "\tDevice type: GPU\n";
		if (dev_type & CL_DEVICE_TYPE_CPU)
			std::cout << "\tDevice type: CPU\n";
		if (dev_type & CL_DEVICE_TYPE_ACCELERATOR)
			std::cout << "\tDevice type: FPGA\n";
		cl_uint i_tmp;
		d.getInfo(CL_DEVICE_MAX_COMPUTE_UNITS, &i_tmp);
		std::cout << "\tMaximum number of compute units: " << i_tmp << std::endl;
		cl_bool b_temp = false;
		d.getInfo(CL_DEVICE_IMAGE_SUPPORT, &b_temp);
		std::cout << "\tImage support: " << (b_temp ? "True" : "False") << std::endl;
		cl_device_fp_config dfpc_tmp;
		d.getInfo(CL_DEVICE_SINGLE_FP_CONFIG, &dfpc_tmp);
		std::cout << "\tSingle FP config: " << ((dfpc_tmp & CL_FP_DENORM) ? "denorms " : "") << ((dfpc_tmp & CL_FP_FMA) ? "FMA" : "") << std::endl;
	}
}

void devInit::createBasicContext(int pNum, cl_device_type dType) {
	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[pNum])(),0 };
	cl::Context context(dType, properties);
	this->ctx = &context;
}
cl::Context* devInit::getContext() {
	return this->ctx;
}

void devInit::createBasicCmdQueue(int dNum) {
	if (dNum > this->devices.size()) {
		std::cout << "Device id is larger than the available amount of devices" << std::endl;
		return;
	}
	cl::CommandQueue cq(*(this->ctx), devices[dNum], 0, NULL);
	this->cmd = &cq;
}
cl::CommandQueue* devInit::getCmdQueue() {
	return this->cmd;
}
