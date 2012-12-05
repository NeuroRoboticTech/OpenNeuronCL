#include "StdAfx.h"
#include "NeuralModel.h"
#include "Kernel.h"
#include "FastSpikingNeuralModel.h"

namespace OpenNeuronCL
{
	namespace NeuralModels
	{

FastSpikingNeuralModel::FastSpikingNeuralModel(INervousSystem *lpNS, double dblDT) : 
	NeuralModel(lpNS, dblDT)
{
	m_aryVmIn = NULL;
	m_aryVmOut = NULL;
	m_aryVahp = NULL;
	m_aryIinOn = NULL;
	m_aryIinOff = NULL;
	m_aryRefrCount = NULL;
	m_arySpiked = NULL;
	m_aryTestOut = NULL;
}

FastSpikingNeuralModel::~FastSpikingNeuralModel(void) 
{
	if(m_aryVmIn) delete[] m_aryVmIn;
	if(m_aryVahp) delete[] m_aryVahp;
	if(m_aryIinOn) delete[] m_aryIinOn;
	if(m_aryIinOff) delete[] m_aryIinOff;
	if(m_aryRefrCount) delete[] m_aryRefrCount;
	if(m_arySpiked) delete[] m_arySpiked;
	if(m_aryTestOut) delete[] m_aryTestOut;
}

void FastSpikingNeuralModel::Initialize()
{
	m_aryFsNeuronKernel = dynamic_pointer_cast<Kernel>(AddKernel("C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\FastSpikingNeuron.cl", "FastSpikingNeuron"));

	InitializeKernels();
	SetupInitialMemory();
}

void FastSpikingNeuralModel::SetupInitialMemory()
{
	ndGlobal = cl::NDRange(m_iGlobalDataSize);
	ndLocal = cl::NDRange(m_iLocalDataSize);

	m_aryVmIn = new cl_float[m_iGlobalDataSize];
	m_aryVmOut = new cl_float[m_iGlobalDataSize];
	m_aryVahp = new cl_float[m_iGlobalDataSize];
	m_aryIinOn = new cl_float[m_iGlobalDataSize];
	m_aryIinOff = new cl_float[m_iGlobalDataSize];
	m_aryRefrCount = new cl_uchar[m_iGlobalDataSize];
	m_arySpiked = new cl_uchar[m_iGlobalDataSize];
	m_aryTestOut = new cl_float[m_iGlobalDataSize];

    // Initialize data
    for(int i=0; i<m_iGlobalDataSize; i++) 
	{
        m_aryVmIn[i] = 0.0f; //i*0.1f;
		m_aryVahp[i] = 0.0f;
		m_aryIinOn[i] = 0.8f;
		m_aryIinOff[i] = 0.0f;
		m_aryRefrCount[i] = 0;
		m_arySpiked[i] = 0;
    }

	  int iSize = sizeof(m_aryVmOut);

      // Create buffers
      m_bufferVmIn = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(m_aryVmIn)*m_iGlobalDataSize, m_aryVmIn));
      m_bufferVmOut = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_WRITE_ONLY, sizeof(m_aryVmOut)*m_iGlobalDataSize, NULL));
      m_bufferVahp = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_aryVahp)*m_iGlobalDataSize, m_aryVahp));
      m_bufferIinOn = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(m_aryIinOn)*m_iGlobalDataSize, m_aryIinOn));
      m_bufferIinOff = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(m_aryIinOff)*m_iGlobalDataSize, m_aryIinOff));
      m_bufferRefrCount = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_aryRefrCount)*m_iGlobalDataSize, m_aryRefrCount));
      m_bufferSpiked = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_arySpiked)*m_iGlobalDataSize, m_arySpiked));
      m_bufferTestOut = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_WRITE_ONLY, sizeof(m_aryTestOut)*m_iGlobalDataSize, NULL));

      // Set kernel arguments
      m_aryFsNeuronKernel->SetArg(0, *(m_bufferVmIn.get()));
      m_aryFsNeuronKernel->SetArg(1, *(m_bufferVahp.get()));
      m_aryFsNeuronKernel->SetArg(2, *(m_bufferIinOn.get()));
      m_aryFsNeuronKernel->SetArg(3, *(m_bufferRefrCount.get()));
      m_aryFsNeuronKernel->SetArg(4, *(m_bufferSpiked.get()));
      m_aryFsNeuronKernel->SetArg(5, *(m_bufferVmOut.get()));
      m_aryFsNeuronKernel->SetArg(6, *(m_bufferTestOut.get()));

      // enqueue kernel-execution command 
	  m_lpQueue = m_lpNervousSystem->QueueForDevice(0);
	  m_lpQueue->enqueueWriteBuffer(*(m_bufferVmIn.get()), CL_TRUE, 0, sizeof(m_aryVmIn)*m_iGlobalDataSize,  m_aryVmIn, NULL, NULL);
	  m_lpQueue->enqueueWriteBuffer(*(m_bufferVahp.get()), CL_TRUE, 0, sizeof(m_aryVahp)*m_iGlobalDataSize,  m_aryVahp, NULL, NULL);
	  m_lpQueue->enqueueWriteBuffer(*(m_bufferIinOn.get()), CL_TRUE, 0, sizeof(m_aryIinOn)*m_iGlobalDataSize,  m_aryIinOn, NULL, NULL);
	  m_lpQueue->enqueueWriteBuffer(*(m_bufferIinOff.get()), CL_TRUE, 0, sizeof(m_aryIinOff)*m_iGlobalDataSize,  m_aryIinOff, NULL, NULL);
	  m_lpQueue->enqueueWriteBuffer(*(m_bufferRefrCount.get()), CL_TRUE, 0, sizeof(m_aryRefrCount)*m_iGlobalDataSize,  m_aryRefrCount, NULL, NULL);
	  m_lpQueue->enqueueWriteBuffer(*(m_bufferSpiked.get()), CL_TRUE, 0, sizeof(m_arySpiked)*m_iGlobalDataSize,  m_arySpiked, NULL, NULL);
}


void FastSpikingNeuralModel::StepModel() 
{
	//if(iTimeSlice == 800)
	//	queue.enqueueCopyBuffer(bufferIinOff, bufferIinOn, 0, 0, sizeof(aryIinOn)*m_iGlobalDataSize, NULL, NULL);
	
	m_lpQueue->enqueueNDRangeKernel(m_aryFsNeuronKernel->CLKernel(), NULL, ndGlobal, ndLocal);

	//queue.enqueueReadBuffer(bufferVmOut, CL_TRUE, 0, sizeof(aryVmOut)*m_iGlobalDataSize,  aryVmOut, NULL, NULL);
	m_lpQueue->enqueueReadBuffer(*(m_bufferTestOut.get()), CL_TRUE, 0, sizeof(m_aryTestOut)*m_iGlobalDataSize,  m_aryTestOut, NULL, NULL);

	//// Display updated buffer
	//for(i=0; i<10; i++) 
	//{
	// printf("%6.5f, %6.5f", aryVmOut[i], aryVmIn[i]);
	// printf("\n");
	//} 
	//printf("\n\n");

	m_lpQueue->enqueueCopyBuffer(*(m_bufferVmOut.get()), *(m_bufferVmIn.get()), 0, 0, sizeof(m_aryVmOut)*m_iGlobalDataSize, NULL, NULL);

	m_lpQueue->enqueueReadBuffer(*(m_bufferVmIn.get()), CL_TRUE, 0, sizeof(m_aryVmIn)*m_iGlobalDataSize,  m_aryVmIn, NULL, NULL);

	m_aryData.push_back(m_aryVmIn[m_iGlobalDataSize-1]);
	// Display updated buffer
	for(int i=0; i<1; i++) 
	{
		printf("%6.5f, %6.5f", m_aryVmIn[i], m_aryTestOut[i]);
		printf("\n");
	}
	printf("\n\n");

}



//
//void FastSpikingNeuralModel::Simulate()
//{
//  string PROGRAM_FILE = "C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\FastSpikingNeuron.cl";
//   string OUTPUT_FILE = "C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\FastSpikingNeuron.dat";
//   string KERNEL_FUNC = "FastSpikingNeuron";
//
//   std::vector<cl::Platform> platforms;
//   std::vector<cl::Device> devices;
//   std::vector<float> aryData;
//   int i;
//   int m_iGlobalDataSize = 1024;
//   int LOCAL_SIZE = 32;
//
//   // Data
//   cl::NDRange ndGlobal(m_iGlobalDataSize);
//   cl::NDRange ndLocal(LOCAL_SIZE);
//
//   cl_float *aryVmIn, *aryVmOut;
//   cl_float *aryVahp, *aryIinOn, *aryIinOff, *aryTestOut;
//   cl_uchar *aryRefrCount, *arySpiked;
//
//   // std::cout << "Neuron Count: " << m_iGlobalDataSize << std::endl;   
//
//   aryVmIn = new cl_float[m_iGlobalDataSize];
//   aryVmOut = new cl_float[m_iGlobalDataSize];
//   aryVahp = new cl_float[m_iGlobalDataSize];
//   aryIinOn = new cl_float[m_iGlobalDataSize];
//   aryIinOff = new cl_float[m_iGlobalDataSize];
//   aryRefrCount = new cl_uchar[m_iGlobalDataSize];
//   arySpiked = new cl_uchar[m_iGlobalDataSize];
//   aryTestOut = new cl_float[m_iGlobalDataSize];
//
//   try {
//      // Initialize data
//      for(i=0; i<m_iGlobalDataSize; i++) {
//         aryVmIn[i] = 0.0f; //i*0.1f;
//		 aryVahp[i] = 0.0f;
//		 aryIinOn[i] = 0.8f;
//		 aryIinOff[i] = 0.0f;
//		 aryRefrCount[i] = 0;
//		 arySpiked[i] = 0;
//      }
//
//      // Place the GPU devices of the first platform into a context
//      cl::Platform::get(&platforms);
//      platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
//      cl::Context context(devices);
//      
//      // Create kernel
//      std::ifstream programFile(PROGRAM_FILE);
//      std::string programString(std::istreambuf_iterator<char>(programFile),
//            (std::istreambuf_iterator<char>()));
//      cl::Program::Sources source(1, std::make_pair(programString.c_str(),
//            programString.length()+1));
//      cl::Program program(context, source);
//
//	 //std::cout << "Program kernel: " << std::endl << programString << std::endl;
//
//	  try
//	  {
//		program.build(devices);
//	  }
//	  catch(cl::Error e)
//	  {
//	      std::cout << e.what() << ": Error code " << e.err() << std::endl;   
//		  string buildlog;
//		  program.getBuildInfo( devices[0], (cl_program_build_info)CL_PROGRAM_BUILD_LOG, &buildlog );
//	      std::cout << "Error: " << buildlog << std::endl;   
//		  throw e;
//	  }
//
//	  cl::Kernel kernel(program, KERNEL_FUNC.c_str());
//
//	  int iSize = sizeof(aryVmOut);
//
//      // Create buffers
//      cl::Buffer bufferVmIn(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryVmIn)*m_iGlobalDataSize, aryVmIn);
//      cl::Buffer bufferVmOut(context, CL_MEM_WRITE_ONLY, sizeof(aryVmOut)*m_iGlobalDataSize, NULL);
//      cl::Buffer bufferVahp(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(aryVahp)*m_iGlobalDataSize, aryVahp);
//      cl::Buffer bufferIinOn(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryIinOn)*m_iGlobalDataSize, aryIinOn);
//      cl::Buffer bufferIinOff(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(aryIinOff)*m_iGlobalDataSize, aryIinOff);
//      cl::Buffer bufferRefrCount(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(aryRefrCount)*m_iGlobalDataSize, aryRefrCount);
//      cl::Buffer bufferSpiked(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(arySpiked)*m_iGlobalDataSize, arySpiked);
//      cl::Buffer bufferTestOut(context, CL_MEM_WRITE_ONLY, sizeof(aryTestOut)*m_iGlobalDataSize, NULL);
//
//      // Set kernel arguments
//      kernel.setArg(0, bufferVmIn);
//      kernel.setArg(1, bufferVahp);
//      kernel.setArg(2, bufferIinOn);
//      kernel.setArg(3, bufferRefrCount);
//      kernel.setArg(4, bufferSpiked);
//      kernel.setArg(5, bufferVmOut);
//      kernel.setArg(6, bufferTestOut);
//
//      // Create queue and enqueue kernel-execution command
//      cl::CommandQueue queue(context, devices[0]);
// 
//	  queue.enqueueWriteBuffer(bufferVmIn, CL_TRUE, 0, sizeof(aryVmIn)*m_iGlobalDataSize,  aryVmIn, NULL, NULL);
//	  queue.enqueueWriteBuffer(bufferVahp, CL_TRUE, 0, sizeof(aryVahp)*m_iGlobalDataSize,  aryVahp, NULL, NULL);
//	  queue.enqueueWriteBuffer(bufferIinOn, CL_TRUE, 0, sizeof(aryIinOn)*m_iGlobalDataSize,  aryIinOn, NULL, NULL);
//	  queue.enqueueWriteBuffer(bufferIinOff, CL_TRUE, 0, sizeof(aryIinOff)*m_iGlobalDataSize,  aryIinOff, NULL, NULL);
//	  queue.enqueueWriteBuffer(bufferRefrCount, CL_TRUE, 0, sizeof(aryRefrCount)*m_iGlobalDataSize,  aryRefrCount, NULL, NULL);
//	  queue.enqueueWriteBuffer(bufferSpiked, CL_TRUE, 0, sizeof(arySpiked)*m_iGlobalDataSize,  arySpiked, NULL, NULL);
//
//	  CStdTimer timeSim;
//	  timeSim.StartTimer();
//
//	  for(int iTimeSlice=0; iTimeSlice<1000; iTimeSlice++)
//	  {
//		  //printf("Iteration: %d\n", iTimeSlice);
//
//		  if(iTimeSlice == 800)
//			  queue.enqueueCopyBuffer(bufferIinOff, bufferIinOn, 0, 0, sizeof(aryIinOn)*m_iGlobalDataSize, NULL, NULL);
//
//		  queue.enqueueNDRangeKernel(kernel, NULL, ndGlobal, ndLocal);
//
//		  //queue.enqueueReadBuffer(bufferVmOut, CL_TRUE, 0, sizeof(aryVmOut)*m_iGlobalDataSize,  aryVmOut, NULL, NULL);
//		  //queue.enqueueReadBuffer(bufferTestOut, CL_TRUE, 0, sizeof(aryTestOut)*m_iGlobalDataSize,  aryTestOut, NULL, NULL);
//
//		  //// Display updated buffer
//		  //for(i=0; i<10; i++) 
//		  //{
//			 // printf("%6.5f, %6.5f", aryVmOut[i], aryVmIn[i]);
//			 // printf("\n");
//		  //} 
//		  //printf("\n\n");
//
//		  queue.enqueueCopyBuffer(bufferVmOut, bufferVmIn, 0, 0, sizeof(aryVmOut)*m_iGlobalDataSize, NULL, NULL);
//
//		  queue.enqueueReadBuffer(bufferVmIn, CL_TRUE, 0, sizeof(aryVmIn)*m_iGlobalDataSize,  aryVmIn, NULL, NULL);
//
//		  aryData.push_back(aryVmIn[m_iGlobalDataSize-1]);
//		  // Display updated buffer
//		  for(i=0; i<1; i++) 
//		  {
//			  printf("%6.5f, %6.5f", aryVmIn[i], aryTestOut[i]);
//			  printf("\n");
//		  }
//		  printf("\n\n");
//
//
//	  }
//
//		double dblTotalTime = timeSim.StopTimer();
//        std::cout << "Total Time: " << dblTotalTime << std::endl;   
//
//		//SaveOutput(OUTPUT_FILE, aryData);
//
//		delete[] aryVmIn;
//		delete[] aryVmOut;
//		delete[] aryVahp;
//		delete[] aryRefrCount;
//		delete[] arySpiked;
//		delete[] aryTestOut;
//	}
//   catch(cl::Error e) 
//   {
//      std::cout << e.what() << ": Error code " << e.err() << std::endl;   
//   }
//}

	}
}