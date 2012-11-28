#include "StdAfx.h"
#include "TestOpenCL.h"

#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>


namespace OpenNeuronCL
{


#pragma pack(push, 1)
struct NeuronDataPacked 
{
    cl_float Vm[2];
    cl_float Vahp;
	cl_float Iin;
    cl_int RefrCountSpiked;
};
#pragma pack(pop)

TestOpenCL::TestOpenCL(void)
{
}


TestOpenCL::~TestOpenCL(void)
{
}

void TestOpenCL::Run()
{
	//RunIDCheck();
	//RunFastSpikingNeurons();
	RunBufferTestNoStruct();
	//RunBufferTestWithStruct();
}

void TestOpenCL::RunIDCheck()
{
	string PROGRAM_FILE = "C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\ID_Check.cl";
	string KERNEL_FUNC = "ID_Check";

   std::vector<cl::Platform> platforms;
   std::vector<cl::Device> devices;
   int i;

   // Data
   cl::NDRange ndOffset(3,5);
   cl::NDRange ndGlobal(6,4);
   cl::NDRange ndLocal(3,2);

   float test[24];      

   try {

	   // Place the GPU devices of the first platform into a context
      cl::Platform::get(&platforms);
      platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
      cl::Context context(devices);
      
      // Create kernel
      std::ifstream programFile(PROGRAM_FILE);
      std::string programString(std::istreambuf_iterator<char>(programFile),
            (std::istreambuf_iterator<char>()));
      cl::Program::Sources source(1, std::make_pair(programString.c_str(),
            programString.length()+1));
      cl::Program program(context, source);

	  //std::cout << "Program kernel: " << std::endl << programString << std::endl;

	  try
	  {
		program.build(devices);
	  }
	  catch(cl::Error e)
	  {
	      std::cout << e.what() << ": Error code " << e.err() << std::endl;   
		  string buildlog;
		  program.getBuildInfo( devices[0], (cl_program_build_info)CL_PROGRAM_BUILD_LOG, &buildlog );
	      std::cout << "Error: " << buildlog << std::endl;   
		  throw e;
	  }

	  cl::Kernel kernel(program, KERNEL_FUNC.c_str());

      // Create buffers
      cl::Buffer test_buffer(context, CL_MEM_READ_WRITE, sizeof(test), NULL);

      // Set kernel arguments
      kernel.setArg(0, test_buffer);

      // Create queue and enqueue kernel-execution command
      cl::CommandQueue queue(context, devices[0]);
      queue.enqueueNDRangeKernel(kernel, ndOffset, ndGlobal, ndLocal);

      // Copy Buffer A to Buffer B
      queue.enqueueReadBuffer(test_buffer, CL_TRUE, 0, sizeof(test),  &test, NULL, NULL);


	   for(i=0; i<24; i+=6) {
		  printf("%.2f     %.2f     %.2f     %.2f     %.2f     %.2f\n", 
			 test[i], test[i+1], test[i+2], test[i+3], test[i+4], test[i+5]);
	   }

   }
   catch(cl::Error e) 
   {
      std::cout << e.what() << ": Error code " << e.err() << std::endl;   
   }
}


void TestOpenCL::RunFastSpikingNeurons()
{
   string PROGRAM_FILE = "C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\FastSpikingNeuron.cl";
   string OUTPUT_FILE = "C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\FastSpikingNeuron.dat";
   string KERNEL_FUNC = "FastSpikingNeuron";

   std::vector<cl::Platform> platforms;
   std::vector<cl::Device> devices;
   std::vector<float> aryData;
   int i;
   int DATA_SIZE = 1024;
   int LOCAL_SIZE = 1024;

   // Data
   cl::NDRange ndGlobal(DATA_SIZE);
   cl::NDRange ndLocal(LOCAL_SIZE);

   cl_float *aryVmIn, *aryVmOut;
   cl_float *aryVahp, *aryIinOn, *aryIinOff, *aryTestOut;
   cl_uchar *aryRefrCount, *arySpiked;

   // std::cout << "Neuron Count: " << DATA_SIZE << std::endl;   

   aryVmIn = new cl_float[DATA_SIZE];
   aryVmOut = new cl_float[DATA_SIZE];
   aryVahp = new cl_float[DATA_SIZE];
   aryIinOn = new cl_float[DATA_SIZE];
   aryIinOff = new cl_float[DATA_SIZE];
   aryRefrCount = new cl_uchar[DATA_SIZE];
   arySpiked = new cl_uchar[DATA_SIZE];
   aryTestOut = new cl_float[DATA_SIZE];

   try {
      // Initialize data
      for(i=0; i<DATA_SIZE; i++) {
         aryVmIn[i] = 0.0f; //i*0.1f;
		 aryVahp[i] = 0.0f;
		 aryIinOn[i] = 0.8f;
		 aryIinOff[i] = 0.0f;
		 aryRefrCount[i] = 0;
		 arySpiked[i] = 0;
      }

      // Place the GPU devices of the first platform into a context
      cl::Platform::get(&platforms);
      platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
      cl::Context context(devices);
      
      // Create kernel
      std::ifstream programFile(PROGRAM_FILE);
      std::string programString(std::istreambuf_iterator<char>(programFile),
            (std::istreambuf_iterator<char>()));
      cl::Program::Sources source(1, std::make_pair(programString.c_str(),
            programString.length()+1));
      cl::Program program(context, source);

	 //std::cout << "Program kernel: " << std::endl << programString << std::endl;

	  try
	  {
		program.build(devices);
	  }
	  catch(cl::Error e)
	  {
	      std::cout << e.what() << ": Error code " << e.err() << std::endl;   
		  string buildlog;
		  program.getBuildInfo( devices[0], (cl_program_build_info)CL_PROGRAM_BUILD_LOG, &buildlog );
	      std::cout << "Error: " << buildlog << std::endl;   
		  throw e;
	  }

	  cl::Kernel kernel(program, KERNEL_FUNC.c_str());

	  int iSize = sizeof(aryVmOut);

      // Create buffers
      cl::Buffer bufferVmIn(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryVmIn)*DATA_SIZE, aryVmIn);
      cl::Buffer bufferVmOut(context, CL_MEM_WRITE_ONLY, sizeof(aryVmOut)*DATA_SIZE, NULL);
      cl::Buffer bufferVahp(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(aryVahp)*DATA_SIZE, aryVahp);
      cl::Buffer bufferIinOn(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryIinOn)*DATA_SIZE, aryIinOn);
      cl::Buffer bufferIinOff(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryIinOff)*DATA_SIZE, aryIinOff);
      cl::Buffer bufferRefrCount(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(aryRefrCount)*DATA_SIZE, aryRefrCount);
      cl::Buffer bufferSpiked(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(arySpiked)*DATA_SIZE, arySpiked);
      cl::Buffer bufferTestOut(context, CL_MEM_WRITE_ONLY, sizeof(aryTestOut)*DATA_SIZE, NULL);

      // Set kernel arguments
      kernel.setArg(0, bufferVmIn);
      kernel.setArg(1, bufferVahp);
      kernel.setArg(2, bufferIinOn);
      kernel.setArg(3, bufferRefrCount);
      kernel.setArg(4, bufferSpiked);
      kernel.setArg(5, bufferVmOut);
      kernel.setArg(6, bufferTestOut);

      // Create queue and enqueue kernel-execution command
      cl::CommandQueue queue(context, devices[0]);
 
	  queue.enqueueWriteBuffer(bufferVmIn, CL_TRUE, 0, sizeof(aryVmIn)*DATA_SIZE,  aryVmIn, NULL, NULL);
	  queue.enqueueWriteBuffer(bufferVahp, CL_TRUE, 0, sizeof(aryVahp)*DATA_SIZE,  aryVahp, NULL, NULL);
	  queue.enqueueWriteBuffer(bufferIinOn, CL_TRUE, 0, sizeof(aryIinOn)*DATA_SIZE,  aryIinOn, NULL, NULL);
	  queue.enqueueWriteBuffer(bufferIinOff, CL_TRUE, 0, sizeof(aryIinOff)*DATA_SIZE,  aryIinOff, NULL, NULL);
	  queue.enqueueWriteBuffer(bufferRefrCount, CL_TRUE, 0, sizeof(aryRefrCount)*DATA_SIZE,  aryRefrCount, NULL, NULL);
	  queue.enqueueWriteBuffer(bufferSpiked, CL_TRUE, 0, sizeof(arySpiked)*DATA_SIZE,  arySpiked, NULL, NULL);

	  CStdTimer timeSim;
	  timeSim.StartTimer();

	  for(int iTimeSlice=0; iTimeSlice<1000; iTimeSlice++)
	  {
		  //printf("Iteration: %d\n", iTimeSlice);

		  if(iTimeSlice == 800)
			  queue.enqueueCopyBuffer(bufferIinOff, bufferIinOn, 0, 0, sizeof(aryIinOn)*DATA_SIZE, NULL, NULL);

		  queue.enqueueNDRangeKernel(kernel, NULL, ndGlobal, ndLocal);

		  //queue.enqueueReadBuffer(bufferVmOut, CL_TRUE, 0, sizeof(aryVmOut)*DATA_SIZE,  aryVmOut, NULL, NULL);
		  //queue.enqueueReadBuffer(bufferTestOut, CL_TRUE, 0, sizeof(aryTestOut)*DATA_SIZE,  aryTestOut, NULL, NULL);

		  //// Display updated buffer
		  //for(i=0; i<10; i++) 
		  //{
			 // printf("%6.5f, %6.5f", aryVmOut[i], aryVmIn[i]);
			 // printf("\n");
		  //} 
		  //printf("\n\n");

		  queue.enqueueCopyBuffer(bufferVmOut, bufferVmIn, 0, 0, sizeof(aryVmOut)*DATA_SIZE, NULL, NULL);

		  queue.enqueueReadBuffer(bufferVmIn, CL_TRUE, 0, sizeof(aryVmIn)*DATA_SIZE,  aryVmIn, NULL, NULL);

		  aryData.push_back(aryVmIn[DATA_SIZE-1]);
		  //// Display updated buffer
		  //for(i=0; i<1; i++) 
		  //{
			 // printf("%6.5f, %6.5f", aryVmIn[i], aryTestOut[i]);
			 // printf("\n");
		  //}
		  //printf("\n\n");


	  }

		double dblTotalTime = timeSim.StopTimer();
        std::cout << "Total Time: " << dblTotalTime << std::endl;   

		SaveOutput(OUTPUT_FILE, aryData);

		delete[] aryVmIn;
		delete[] aryVmOut;
		delete[] aryVahp;
		delete[] aryRefrCount;
		delete[] arySpiked;
		delete[] aryTestOut;
	}
   catch(cl::Error e) 
   {
      std::cout << e.what() << ": Error code " << e.err() << std::endl;   
   }
}


void TestOpenCL::SaveOutput(string strFilename, vector<float> &aryData)
{
	ofstream oStream;
	oStream.open(strFilename.c_str());

	for(int iRow=0; iRow< (int) aryData.size(); iRow++)
		oStream << aryData[iRow] << "\n";

	oStream.close();
}

void TestOpenCL::RunBufferTestWithStruct()
{
	string PROGRAM_FILE = "C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\BufferTestWithStruct.cl";
	string KERNEL_FUNC = "BufferTestWithStruct";

	std::vector<cl::Platform> platforms;
	std::vector<cl::Device> devices;
	std::vector<float> aryData;
	int i;
	int DATA_SIZE = 32;
	int LOCAL_SIZE = 32;

	// Data
	cl::NDRange ndGlobal(DATA_SIZE);
	cl::NDRange ndLocal(LOCAL_SIZE);

	NeuronDataPacked *aryNeurons;
	cl_float *aryVmOut, *aryTestOut;
	
	// std::cout << "Neuron Count: " << DATA_SIZE << std::endl;   

	aryNeurons = new NeuronDataPacked[DATA_SIZE];
	aryVmOut = new cl_float[DATA_SIZE];
	aryTestOut = new cl_float[DATA_SIZE];

	try {
		// Initialize data
		for(i=0; i<DATA_SIZE; i++) {
		aryNeurons[i].Vm[0] = 0.1f;
		aryNeurons[i].Vm[1] = 0.11f;
		aryNeurons[i].Vahp = i+0.2f;
		aryNeurons[i].Iin = i+0.3f;
		aryNeurons[i].RefrCountSpiked = i;
	}

	// Place the GPU devices of the first platform into a context
	cl::Platform::get(&platforms);
	platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
	cl::Context context(devices);
      
	// Create kernel
	std::ifstream programFile(PROGRAM_FILE);
	std::string programString(std::istreambuf_iterator<char>(programFile),
	(std::istreambuf_iterator<char>()));
	cl::Program::Sources source(1, std::make_pair(programString.c_str(),
	programString.length()+1));
	cl::Program program(context, source);

	//std::cout << "Program kernel: " << std::endl << programString << std::endl;

	try
	{
		program.build(devices);
	}
	catch(cl::Error e)
	{
		std::cout << e.what() << ": Error code " << e.err() << std::endl;   
		string buildlog;
		program.getBuildInfo( devices[0], (cl_program_build_info)CL_PROGRAM_BUILD_LOG, &buildlog );
		std::cout << "Error: " << buildlog << std::endl;   
		throw e;
	}

	cl::Kernel kernel(program, KERNEL_FUNC.c_str());

	int iSize = sizeof(aryNeurons);

	// Create buffers
	cl::Buffer bufferNeurons(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryNeurons)*DATA_SIZE, aryNeurons);
	cl::Buffer bufferVmOut(context, CL_MEM_WRITE_ONLY, sizeof(aryVmOut)*DATA_SIZE, NULL);
	cl::Buffer bufferTestOut(context, CL_MEM_WRITE_ONLY, sizeof(aryTestOut)*DATA_SIZE, NULL);

	// Set kernel arguments
	kernel.setArg(0, bufferNeurons);
	kernel.setArg(1, sizeof(aryNeurons)*DATA_SIZE, NULL);
	kernel.setArg(2, bufferVmOut);
	kernel.setArg(3, bufferTestOut);

   cl::Event profileEvent;

	// Create queue and enqueue kernel-execution command
	cl::CommandQueue queue(context, devices[0], CL_QUEUE_PROFILING_ENABLE);
 
	queue.enqueueWriteBuffer(bufferNeurons, CL_TRUE, 0, sizeof(aryNeurons)*DATA_SIZE,  aryNeurons, NULL, NULL);

	queue.enqueueNDRangeKernel(kernel, NULL, ndGlobal, ndLocal, NULL, &profileEvent);

	queue.enqueueReadBuffer(bufferVmOut, CL_TRUE, 0, sizeof(aryVmOut)*DATA_SIZE,  aryVmOut, NULL, NULL);
	queue.enqueueReadBuffer(bufferTestOut, CL_TRUE, 0, sizeof(aryTestOut)*DATA_SIZE,  aryTestOut, NULL, NULL);

	// Configure event processing
	cl_ulong time_start, time_end;
	time_start = profileEvent.getProfilingInfo<CL_PROFILING_COMMAND_START>();
	time_end = profileEvent.getProfilingInfo<CL_PROFILING_COMMAND_END>();
	std::cout << "Start time: " << time_start << " ns." << std::endl;
	std::cout << "  End time: " << time_end << " ns." << std::endl;
	std::cout << "Elaps time: " << (time_end - time_start) << " ns." << std::endl;

	// Display updated buffer
	for(i=0; i<10; i++) 
	{
		 printf("%6.5f, %6.5f", aryVmOut[i], aryTestOut[i]);
		 printf("\n");
	} 
	printf("\n\n");

	delete[] aryNeurons;
	delete[] aryVmOut;
	delete[] aryTestOut;
	}
	catch(cl::Error e) 
	{
		std::cout << e.what() << ": Error code " << e.err() << std::endl;   
	}
}

void TestOpenCL::RunBufferTestNoStruct()
{
	string PROGRAM_FILE = "C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\BufferTestNoStruct.cl";
	string KERNEL_FUNC = "BufferTestNoStruct";

	std::vector<cl::Platform> platforms;
	std::vector<cl::Device> devices;
	std::vector<float> aryData;
	int i;
	int DATA_SIZE = 32;
	int LOCAL_SIZE = 32;

	// Data
	cl::NDRange ndGlobal(DATA_SIZE);
	cl::NDRange ndLocal(LOCAL_SIZE);

	cl_float *aryVmIn, *aryVmOut;
	cl_float *aryVahp, *aryIinOn, *aryIinOff, *aryTestOut;
	cl_int *aryRefrCountSpiked;
	
	// std::cout << "Neuron Count: " << DATA_SIZE << std::endl;   

	aryVmIn = new cl_float[DATA_SIZE];
	aryVmOut = new cl_float[DATA_SIZE];
	aryVahp = new cl_float[DATA_SIZE];
	aryIinOn = new cl_float[DATA_SIZE];
	aryIinOff = new cl_float[DATA_SIZE];
	aryRefrCountSpiked = new cl_int[DATA_SIZE];
	aryTestOut = new cl_float[DATA_SIZE];

	try {
		// Initialize data
		for(i=0; i<DATA_SIZE; i++) {
		aryVmIn[i] = 0.1f;
		aryVahp[i] = i+0.2f;
		aryIinOn[i] = i+0.3f;
		aryIinOff[i] = i+0.4f;
		aryRefrCountSpiked[i] = i;
	}

	// Place the GPU devices of the first platform into a context
	cl::Platform::get(&platforms);
	platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
	cl::Context context(devices);
      
	// Create kernel
	std::ifstream programFile(PROGRAM_FILE);
	std::string programString(std::istreambuf_iterator<char>(programFile),
	(std::istreambuf_iterator<char>()));
	cl::Program::Sources source(1, std::make_pair(programString.c_str(),
	programString.length()+1));
	cl::Program program(context, source);

	//std::cout << "Program kernel: " << std::endl << programString << std::endl;

	try
	{
		program.build(devices);
	}
	catch(cl::Error e)
	{
		std::cout << e.what() << ": Error code " << e.err() << std::endl;   
		string buildlog;
		program.getBuildInfo( devices[0], (cl_program_build_info)CL_PROGRAM_BUILD_LOG, &buildlog );
		std::cout << "Error: " << buildlog << std::endl;   
		throw e;
	}

	cl::Kernel kernel(program, KERNEL_FUNC.c_str());

	int iSize = sizeof(aryVmOut);

	// Create buffers
	cl::Buffer bufferVmIn(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryVmIn)*DATA_SIZE, aryVmIn);
	cl::Buffer bufferVmOut(context, CL_MEM_WRITE_ONLY, sizeof(aryVmOut)*DATA_SIZE, NULL);
	cl::Buffer bufferVahp(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(aryVahp)*DATA_SIZE, aryVahp);
	cl::Buffer bufferIinOn(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryIinOn)*DATA_SIZE, aryIinOn);
	cl::Buffer bufferIinOff(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryIinOff)*DATA_SIZE, aryIinOff);
	cl::Buffer bufferRefrCount(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(aryRefrCountSpiked)*DATA_SIZE, aryRefrCountSpiked);
	cl::Buffer bufferTestOut(context, CL_MEM_WRITE_ONLY, sizeof(aryTestOut)*DATA_SIZE, NULL);

	// Set kernel arguments
	kernel.setArg(0, bufferVmIn);
	kernel.setArg(1, bufferVahp);
	kernel.setArg(2, bufferIinOn);
	kernel.setArg(3, bufferRefrCount);
	kernel.setArg(4, sizeof(aryVmIn)*DATA_SIZE, NULL);
	kernel.setArg(5, sizeof(aryVahp)*DATA_SIZE, NULL);
	kernel.setArg(6, sizeof(aryIinOn)*DATA_SIZE, NULL);
	kernel.setArg(7, sizeof(aryRefrCountSpiked)*DATA_SIZE, NULL);
	kernel.setArg(8, bufferVmOut);
	kernel.setArg(9, bufferTestOut);

   cl::Event profileEvent;

	// Create queue and enqueue kernel-execution command
	cl::CommandQueue queue(context, devices[0], CL_QUEUE_PROFILING_ENABLE);
 
	queue.enqueueWriteBuffer(bufferVmIn, CL_TRUE, 0, sizeof(aryVmIn)*DATA_SIZE,  aryVmIn, NULL, NULL);
	queue.enqueueWriteBuffer(bufferVahp, CL_TRUE, 0, sizeof(aryVahp)*DATA_SIZE,  aryVahp, NULL, NULL);
	queue.enqueueWriteBuffer(bufferIinOn, CL_TRUE, 0, sizeof(aryIinOn)*DATA_SIZE,  aryIinOn, NULL, NULL);
	queue.enqueueWriteBuffer(bufferIinOff, CL_TRUE, 0, sizeof(aryIinOff)*DATA_SIZE,  aryIinOff, NULL, NULL);
	queue.enqueueWriteBuffer(bufferRefrCount, CL_TRUE, 0, sizeof(aryRefrCountSpiked)*DATA_SIZE,  aryRefrCountSpiked, NULL, NULL);

	queue.enqueueNDRangeKernel(kernel, NULL, ndGlobal, ndLocal, NULL, &profileEvent);

	queue.enqueueReadBuffer(bufferVmOut, CL_TRUE, 0, sizeof(aryVmOut)*DATA_SIZE,  aryVmOut, NULL, NULL);
	queue.enqueueReadBuffer(bufferTestOut, CL_TRUE, 0, sizeof(aryTestOut)*DATA_SIZE,  aryTestOut, NULL, NULL);

	// Configure event processing
	cl_ulong time_start, time_end;
	time_start = profileEvent.getProfilingInfo<CL_PROFILING_COMMAND_START>();
	time_end = profileEvent.getProfilingInfo<CL_PROFILING_COMMAND_END>();
	std::cout << "Start time: " << time_start << " ns." << std::endl;
	std::cout << "  End time: " << time_end << " ns." << std::endl;
	std::cout << "Elaps time: " << (time_end - time_start) << " ns." << std::endl;

	// Display updated buffer
	for(i=0; i<10; i++) 
	{
		 printf("%6.5f, %6.5f", aryVmOut[i], aryTestOut[i]);
		 printf("\n");
	} 
	printf("\n\n");

	delete[] aryVmIn;
	delete[] aryVmOut;
	delete[] aryVahp;
	delete[] aryRefrCountSpiked;
	delete[] aryTestOut;
	}
	catch(cl::Error e) 
	{
		std::cout << e.what() << ": Error code " << e.err() << std::endl;   
	}
}


}