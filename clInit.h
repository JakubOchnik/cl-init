#pragma once

#define __MAX_DEFAULT_VECTOR_SIZE 128

#if defined (__APPLE__) || defined (MACOSX)
#include <OpenCL/opencl.h>
#else
#include <CL/cl.hpp>
#endif

#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>

class devInit {
private:
	std::vector<cl::Platform> platforms;
	std::vector<cl::Device> devices;
	cl::Context* ctx;
	cl::CommandQueue* cmd;
	cl_uint selectedPlatform;
public:
	devInit();

	void loadPlatforms();
	cl::Platform* getPlatforms(int pNum);
	const std::vector<cl::Platform> getPlatforms() const;

	void printBasicPlatformInfo() const;

	void loadDevices(int pNum);
	cl::Device* getDevices(int dNum);
	const std::vector<cl::Device> getDevices() const;

	void devInit::printBasicDeviceInfo() const;

	cl::Context* getContext();
	void createBasicContext(int pNum, cl_device_type dType);

	void createBasicCmdQueue(int dNum);
	cl::CommandQueue* getCmdQueue();
	~devInit();
};
