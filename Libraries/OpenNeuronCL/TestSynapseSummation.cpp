#include "StdAfx.h"
#include "NeuralModel.h"
#include "Kernel.h"
#include "TestSynapseSummation.h"

namespace OpenNeuronCL
{
	namespace NeuralModels
	{

TestSynapseSummation::TestSynapseSummation(INervousSystem *lpNS, double dblDT) : 
	NeuralModel(lpNS, dblDT)
{
	m_arySynapseI = NULL;
	m_aryNeuronIin = NULL;
	m_arySynapsePostNeuronIdx = NULL;
	arySynapseStartIdx = NULL;
	arySynapseCount = NULL;

	m_iSynapsesPerNeuron = 10;
	m_iNeuronCount = 0;
}

TestSynapseSummation::~TestSynapseSummation(void) 
{
	if(m_arySynapseI) delete[] m_arySynapseI;
	if(m_aryNeuronIin) delete[] m_aryNeuronIin;
	if(m_arySynapsePostNeuronIdx) delete[] m_arySynapsePostNeuronIdx;

	if(arySynapseStartIdx) delete[] arySynapseStartIdx;
	if(arySynapseCount) delete[] arySynapseCount;
}

void TestSynapseSummation::Initialize()
{
	m_aryFsNeuronKernel = dynamic_pointer_cast<Kernel>(AddKernel("C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\TestAtomicAdd.cl", "TestAtomicAdd"));
	//m_aryFsNeuronKernel = dynamic_pointer_cast<Kernel>(AddKernel("C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\TestAddSynapsePerNeuron.cl", "TestAddSynapsePerNeuron"));
	//m_aryFsNeuronKernel = dynamic_pointer_cast<Kernel>(AddKernel("C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\TestAddSynapsePerNeuron.cl", "TestAddSynapsePerNeuronStrided"));

	m_iGlobalDataSize = 100;    
	//m_iGlobalDataSize = 32;    
	//m_iGlobalDataSize = 1024;    //2^10
	//m_iGlobalDataSize = 2048;    //2^11
	//m_iGlobalDataSize = 4096;    //2^12
	//m_iGlobalDataSize = 8192;   //2^13
	//m_iGlobalDataSize = 16384;   //2^14
	//m_iGlobalDataSize = 32768;   //2^15
	//m_iGlobalDataSize = 65536;   //2^16
	//m_iGlobalDataSize = 131072;  //2^17
	//m_iGlobalDataSize = 262144;    //2^18
	//m_iGlobalDataSize = 524288;    //2^19
	//m_iGlobalDataSize = 1048576;    //2^20
	//m_iGlobalDataSize = 8388608;    //2^23
	//m_iGlobalDataSize = 16777216;    //2^24
	m_iLocalDataSize = 10;

	InitializeKernels();
	SetupInitialMemory();
}

void TestSynapseSummation::SetupInitialAtomicAddMemory()
{
	ndGlobal = cl::NDRange(m_iGlobalDataSize);
	ndLocal = cl::NDRange(m_iLocalDataSize);

	m_arySynapseI = new cl_float[m_iGlobalDataSize];
	m_arySynapsePostNeuronIdx = new cl_uint[m_iGlobalDataSize];

    // Initialize data
	m_iNeuronCount = 0;
	unsigned int iNeuronIdxCounter = 0;
    for(int i=0; i<m_iGlobalDataSize; i++) 
	{
        m_arySynapseI[i] = m_iNeuronCount;
		m_arySynapsePostNeuronIdx[i] = m_iNeuronCount;
		iNeuronIdxCounter++;
		if(iNeuronIdxCounter>=m_iSynapsesPerNeuron)
		{
			iNeuronIdxCounter = 0;
			m_iNeuronCount++;
		}
    }

	m_aryNeuronIin = new cl_float[m_iNeuronCount];
    for(int i=0; i<m_iNeuronCount; i++) 
		m_aryNeuronIin[i] = 0.0f;

	// Create buffers
	m_bufferSynapseI = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_arySynapseI)*m_iGlobalDataSize, m_arySynapseI));
	m_bufferSynapsePostNeuronIdx = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(m_arySynapsePostNeuronIdx)*m_iGlobalDataSize, m_arySynapsePostNeuronIdx));
	m_bufferNeuronIin = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(m_aryNeuronIin)*m_iNeuronCount, m_aryNeuronIin));

	try
	{
		// Set kernel arguments
		//m_lLocalTimeSlice =;
		cl::Kernel &kernel = m_aryFsNeuronKernel->CLKernel();
		kernel.setArg(0, *(m_bufferSynapseI.get()));
		kernel.setArg(1, *(m_bufferSynapsePostNeuronIdx.get()));
		kernel.setArg(2, *(m_bufferNeuronIin.get()));
	}
	catch(cl::Error e)
	{
		std::cout << e.what() << ": Error code " << e.err() << std::endl;   
		throw e;
	}

	// enqueue kernel-execution command 
	m_lpQueue = m_lpNervousSystem->QueueForDevice(0);
	m_lpQueue->enqueueWriteBuffer(*(m_bufferSynapseI.get()), CL_TRUE, 0, sizeof(m_arySynapseI)*m_iGlobalDataSize,  m_arySynapseI, NULL, NULL);
	m_lpQueue->enqueueWriteBuffer(*(m_bufferSynapsePostNeuronIdx.get()), CL_TRUE, 0, sizeof(m_arySynapsePostNeuronIdx)*m_iGlobalDataSize, m_arySynapsePostNeuronIdx, NULL, NULL);
	m_lpQueue->enqueueWriteBuffer(*(m_bufferNeuronIin.get()), CL_TRUE, 0, sizeof(m_aryNeuronIin)*m_iNeuronCount,  m_aryNeuronIin, NULL, NULL);
}

void TestSynapseSummation::StepAtomicAdd()
{
	cl::Kernel &kernel = m_aryFsNeuronKernel->CLKernel();

	cl::Event profileEvent;
	m_lpQueue->enqueueNDRangeKernel(kernel, NULL, ndGlobal, ndLocal, NULL, &profileEvent);

	m_lpQueue->enqueueReadBuffer(*(m_bufferNeuronIin.get()), CL_TRUE, 0, sizeof(m_aryNeuronIin)*m_iNeuronCount,  m_aryNeuronIin, NULL, NULL);

	double start = profileEvent.getProfilingInfo<CL_PROFILING_COMMAND_START>();
	double end = profileEvent.getProfilingInfo<CL_PROFILING_COMMAND_END>();
	std::cout << "Elapsed time: " << (end-start) << " ns." << std::endl;

	//m_aryData.push_back(m_aryVm[0]);
	//Display updated buffer
	//for(int i=0; i<m_iNeuronCount; i++) 
	for(int i=0; i<5; i++) 
	{
		printf("%6.5f", m_aryNeuronIin[i]);
		printf("\n");
	}
	printf("\n\n");
}

void TestSynapseSummation::SetupInitialAddSynapsePerNeuronMemory()
{
	ndGlobal = cl::NDRange(m_iGlobalDataSize);
	ndLocal = cl::NDRange(m_iLocalDataSize);

	m_iNeuronCount = m_iGlobalDataSize;
	unsigned int iSynapseCount = m_iGlobalDataSize*m_iSynapsesPerNeuron;
	m_arySynapseI = new cl_float[iSynapseCount];

    // Initialize data
    for(int i=0; i<iSynapseCount; i++) 
        m_arySynapseI[i] = i+1;

	m_aryNeuronIin = new cl_float[m_iNeuronCount];
	arySynapseStartIdx = new cl_uint[m_iNeuronCount];
	arySynapseCount = new cl_uint[m_iNeuronCount];
    for(int i=0; i<m_iNeuronCount; i++) 
	{
		m_aryNeuronIin[i] = 0.0f;

		//arySynapseStartIdx[i] = i*m_iSynapsesPerNeuron; //NoneStrided
		arySynapseStartIdx[i] = i;  //Strided

		arySynapseCount[i] = m_iSynapsesPerNeuron;
	}

	// Create buffers
	m_bufferSynapseI = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_arySynapseI)*iSynapseCount, m_arySynapseI));
	m_bufferSynapseStartIdx = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(arySynapseStartIdx)*m_iNeuronCount, arySynapseStartIdx));
	m_bufferSynapseCount = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(arySynapseCount)*m_iNeuronCount, arySynapseCount));
	m_bufferNeuronIin = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(m_aryNeuronIin)*m_iNeuronCount, m_aryNeuronIin));

	try
	{
		// Set kernel arguments
		//m_lLocalTimeSlice =;
		cl::Kernel &kernel = m_aryFsNeuronKernel->CLKernel();
		kernel.setArg(0, *(m_bufferSynapseI.get()));
		kernel.setArg(1, *(m_bufferSynapseStartIdx.get()));
		kernel.setArg(2, *(m_bufferSynapseCount.get()));
		kernel.setArg(3, *(m_bufferNeuronIin.get()));
		kernel.setArg(4, m_iSynapsesPerNeuron);
	}
	catch(cl::Error e)
	{
		std::cout << e.what() << ": Error code " << e.err() << std::endl;   
		throw e;
	}

	// enqueue kernel-execution command 
	m_lpQueue = m_lpNervousSystem->QueueForDevice(0);
	m_lpQueue->enqueueWriteBuffer(*(m_bufferSynapseI.get()), CL_TRUE, 0, sizeof(m_arySynapseI)*iSynapseCount,  m_arySynapseI, NULL, NULL);
	m_lpQueue->enqueueWriteBuffer(*(m_bufferSynapseStartIdx.get()), CL_TRUE, 0, sizeof(arySynapseStartIdx)*m_iNeuronCount, arySynapseStartIdx, NULL, NULL);
	m_lpQueue->enqueueWriteBuffer(*(m_bufferSynapseCount.get()), CL_TRUE, 0, sizeof(arySynapseCount)*m_iNeuronCount, arySynapseCount, NULL, NULL);
	m_lpQueue->enqueueWriteBuffer(*(m_bufferNeuronIin.get()), CL_TRUE, 0, sizeof(m_aryNeuronIin)*m_iNeuronCount,  m_aryNeuronIin, NULL, NULL);
}

void TestSynapseSummation::StepAddSynapsePerNeuron()
{
	cl::Kernel &kernel = m_aryFsNeuronKernel->CLKernel();

	cl::Event profileEvent;
	m_lpQueue->enqueueNDRangeKernel(kernel, NULL, ndGlobal, ndLocal, NULL, &profileEvent);

	m_lpQueue->enqueueReadBuffer(*(m_bufferNeuronIin.get()), CL_TRUE, 0, sizeof(m_aryNeuronIin)*m_iNeuronCount,  m_aryNeuronIin, NULL, NULL);

	double start = profileEvent.getProfilingInfo<CL_PROFILING_COMMAND_START>();
	double end = profileEvent.getProfilingInfo<CL_PROFILING_COMMAND_END>();
	std::cout << "Elapsed time: " << (end-start) << " ns." << std::endl;

	//m_aryData.push_back(m_aryVm[0]);
	//Display updated buffer
	//for(int i=0; i<m_iNeuronCount; i++) 
	for(int i=0; i<5; i++) 
	{
		printf("%6.5f", m_aryNeuronIin[i]);
		printf("\n");
	}
	printf("\n\n");
}


void TestSynapseSummation::SetupInitialMemory()
{
	SetupInitialAtomicAddMemory();
	//SetupInitialAddSynapsePerNeuronMemory();
}

void TestSynapseSummation::StepModel() 
{
	StepAtomicAdd();
	//StepAddSynapsePerNeuron();
}

	}
}