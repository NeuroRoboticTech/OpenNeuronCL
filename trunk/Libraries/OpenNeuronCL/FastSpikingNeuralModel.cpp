#include "StdAfx.h"
#include "NeuralModel.h"
#include "Kernel.h"
#include "FastSpikingNeuralModel.h"

#define REFR_COUNT_MASK 0x0000007F
#define SPIKED_MASK 0x00000080
#define SPIKED_SHIFT 3
#define DELAY_COUNT_MASK 0xFFFFFF00
#define DELAY_COUNT_SHIFT 8
#define DELAY_ADD_SPIKE 4
#define SYN_COUNT_MASK 0x0000FFFF
#define NEURON_TYPE_MASK 0x00FF0000
#define NEURON_TYPE_SHIFT 8

namespace OpenNeuronCL
{ 
	namespace NeuralModels
	{

FastSpikingNeuralModel::FastSpikingNeuralModel(INervousSystem *lpNS, double dblDT) : 
	NeuralModel(lpNS, dblDT)
{
	m_aryVm = NULL;
	m_aryVahp = NULL;
	m_aryIext = NULL;
	m_aryPostSynWeightDecay = NULL;
	m_aryTestOut = NULL;
	m_arySynapseStartIdx = NULL;
	m_aryVsyn = NULL;
	m_aryWeight = NULL;
	m_aryPreSynWeightDecay = NULL;
	m_arySynapseTypeID = NULL;
	m_aryPreSynNeuronIdx = NULL;
	m_aryNeuronData1 = NULL;
	m_aryNeuronData2 = NULL;
	m_iSeed = 12345;
	m_iNeuronCount = 0;
	m_iSynapseCount = 0;
	m_iSynapsesPerNeuron = 8;
}

FastSpikingNeuralModel::~FastSpikingNeuralModel(void) 
{
	if(m_aryVm) {delete[] m_aryVm; m_aryVm = NULL;}
	if(m_aryVahp){ delete[] m_aryVahp; m_aryVahp = NULL;}
	if(m_aryIext) {delete[] m_aryIext; m_aryIext = NULL;}
	if(m_aryPostSynWeightDecay) {delete[] m_aryPostSynWeightDecay; m_aryPostSynWeightDecay = NULL;}
	if(m_arySynapseStartIdx) {delete[] m_arySynapseStartIdx; m_arySynapseStartIdx = NULL;}
	if(m_aryNeuronData1) {delete[] m_aryNeuronData1;  m_aryNeuronData1= NULL;}
	if(m_aryNeuronData2) {delete[] m_aryNeuronData2;  m_aryNeuronData2= NULL;}
	if(m_aryVsyn) {delete[] m_aryVsyn; m_aryVsyn = NULL;}
	if(m_aryWeight) {delete[] m_aryWeight; m_aryWeight = NULL;}
	if(m_aryPreSynWeightDecay) {delete[] m_aryPreSynWeightDecay; m_aryPreSynWeightDecay = NULL;}
	if(m_arySynapseTypeID) {delete[] m_arySynapseTypeID; m_arySynapseTypeID = NULL;}
	if(m_aryPreSynNeuronIdx) {delete[] m_aryPreSynNeuronIdx; m_aryPreSynNeuronIdx = NULL;}
}

void FastSpikingNeuralModel::Initialize()
{
	m_aryFsNeuronKernel = dynamic_pointer_cast<Kernel>(AddKernel("C:\\Projects\\AnimatLabSDK\\OpenNeuronCL\\Libraries\\OpenNeuronCL\\Kernels\\FastSpikingNeuron.cl", "FastSpikingNeuron"));

	//m_iGlobalDataSize = 100;    
	//m_iGlobalDataSize = 32;    
	m_iGlobalDataSize = 1024;    //2^10
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
	//m_iLocalDataSize = 10;

	m_iNeuronCount = m_iGlobalDataSize;
	m_iSynapseCount = m_iGlobalDataSize*m_iSynapsesPerNeuron;

	InitializeKernels();
	SetupInitialMemory();
}

void FastSpikingNeuralModel::ExtractNeuronData1(unsigned int iNeuronData1, unsigned short &iRefrCount, unsigned char &iSpiked, unsigned int &iDelayCount)
{
	iRefrCount = (iNeuronData1 & REFR_COUNT_MASK);
	iSpiked = (iNeuronData1 & SPIKED_MASK) >> SPIKED_SHIFT;
	iDelayCount = (iNeuronData1 & DELAY_COUNT_MASK) >> DELAY_COUNT_SHIFT;
}

unsigned int FastSpikingNeuralModel::GenerateNeuronData1(unsigned short iRefrCount, unsigned char iSpiked, unsigned int iDelayCount)
{
	//set the delay bits and shift over
	iDelayCount = (iDelayCount << 1) | (((unsigned int) iSpiked) << DELAY_ADD_SPIKE);
	unsigned int iData = (iDelayCount << DELAY_COUNT_SHIFT) | (iSpiked << SPIKED_SHIFT) | iRefrCount;
	return iData;
}

void FastSpikingNeuralModel::ExtractNeuronData2(unsigned int iNeuronData2, unsigned short &iSynCount, unsigned char &iNeuronType)
{
	iSynCount = (iNeuronData2 & SYN_COUNT_MASK);
	iNeuronType = (iNeuronData2 & NEURON_TYPE_MASK) >> NEURON_TYPE_SHIFT;
}

unsigned int FastSpikingNeuralModel::GenerateNeuronData2(unsigned short iSynCount, unsigned char iNeuronType)
{
	unsigned int iData = iSynCount | (iNeuronType << NEURON_TYPE_SHIFT);
	return iData;
}

void FastSpikingNeuralModel::SetupInitialMemory()
{
	printf("Setting up memory.\n");

	m_FSN_Global = cl::NDRange(m_iNeuronCount);
	m_FSN_Local = cl::NDRange(m_iLocalDataSize);

	printf("Allocating memory.\n");

	//Neuron Data
	m_aryVm = new cl_float[m_iNeuronCount];
	m_aryVahp = new cl_float[m_iNeuronCount];
	m_aryIext = new cl_float[m_iNeuronCount];
	m_aryPostSynWeightDecay = new cl_float[m_iNeuronCount];
	m_arySynapseStartIdx = new cl_uint[m_iNeuronCount];
	m_aryTestOut = new cl_float[m_iNeuronCount];
	m_aryNeuronData1 = new cl_uint[m_iNeuronCount];
	m_aryNeuronData2 = new cl_uint[m_iNeuronCount];

	//Synapse Data
	m_aryVsyn = new cl_float[m_iSynapseCount];
	m_aryWeight = new cl_float[m_iSynapseCount];
	m_aryPreSynWeightDecay = new cl_float[m_iSynapseCount];
	m_arySynapseTypeID = new cl_uchar[m_iSynapseCount];
	m_aryPreSynNeuronIdx = new cl_uint[m_iSynapseCount];

	printf("Initialiazing memory.\n");

	// Initialize Neuron Data
    for(int i=0; i<m_iNeuronCount; i++) 
	{
        m_aryVm[i] = 0.0f; //i*0.1f;
		m_aryVahp[i] = 0.0f;
		m_aryIext[i] = 0.8f;
		m_aryPostSynWeightDecay[i] = 0;
		m_arySynapseStartIdx[i] = i*m_iSynapsesPerNeuron;
		m_aryNeuronData1[i] = 0;
		m_aryNeuronData2[i] = 0;
    }

	//Initialize Synapse Data
   for(int i=0; i<m_iSynapseCount; i++) 
	{
        m_aryVsyn[i] = 0.0f; //i*0.1f;
		m_aryWeight[i] = 0.0f;
		m_aryPreSynWeightDecay[i] = 0.0f; // 0.8f;
		m_arySynapseTypeID[i] = 0;
		m_aryPreSynNeuronIdx[i] = 0;
    }


//	long lTotaNeuronlSize = (sizeof(m_aryVm)*m_iNeuronCount*2) + 
//					  sizeof(m_aryVahp)*m_iNeuronCount + 
//					  sizeof(m_aryIext)*m_iNeuronCount +
//					  sizeof(m_aryPostSynWeightDecay)*m_iNeuronCount + 
////					  sizeof(m_arySpiked)*m_iGlobalDataSize +
//					  sizeof(m_aryTestOut)*m_iNeuronCount;
//	long lTotalSizeKb = lTotalSize/1024;
//	long lTotalSizeMb = lTotalSizeKb/1024;

	printf("Creating Buffers.\n");

	// Create Neuron Data Buffers
	m_bufVm = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(m_aryVm)*m_iNeuronCount, m_aryVm));
	m_bufVahp = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_aryVahp)*m_iNeuronCount, m_aryVahp));
	m_bufIext = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(m_aryIext)*m_iNeuronCount, m_aryIext));
	m_bufPostSynWeightDecay = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_aryPostSynWeightDecay)*m_iNeuronCount, m_aryPostSynWeightDecay));
	m_bufTestOut = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_WRITE_ONLY, sizeof(m_aryTestOut)*m_iNeuronCount, NULL));
	m_bufSynapseStartIdx = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_arySynapseStartIdx)*m_iNeuronCount, m_arySynapseStartIdx));
	m_bufNeuronData1 = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_aryNeuronData1)*m_iNeuronCount, m_aryNeuronData1));
	m_bufNeuronData2 = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_aryNeuronData2)*m_iNeuronCount, m_aryNeuronData2));

	// Create Synapse Data Buffers
	m_bufVsyn = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(m_aryVsyn)*m_iSynapseCount, m_aryVsyn));
	m_bufWeight = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_aryWeight)*m_iSynapseCount, m_aryWeight));
	m_bufPreSynWeightDecay = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_aryPreSynWeightDecay)*m_iSynapseCount, m_aryPreSynWeightDecay));
	m_bufSynapseTypeID = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_arySynapseTypeID)*m_iSynapseCount, m_arySynapseTypeID));
	m_bufPreSynNeuronIdx = shared_ptr<cl::Buffer>( new cl::Buffer(m_lpNervousSystem->ActiveContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(m_aryPreSynNeuronIdx)*m_iSynapseCount, m_aryPreSynNeuronIdx));

	printf("Setting kernel args.\n");
	try
	{
		// Set kernel arguments
		//m_lLocalTimeSlice =;
		cl::Kernel &kernel = m_aryFsNeuronKernel->CLKernel();
		kernel.setArg(0, m_lpNervousSystem->TimeSlice());
		kernel.setArg(1, m_iSeed);
		kernel.setArg(2, *(m_bufVm.get()));
		kernel.setArg(3, *(m_bufVahp.get()));
		kernel.setArg(4, *(m_bufIext.get()));
		kernel.setArg(5, *(m_bufPostSynWeightDecay.get()));
		kernel.setArg(6, *(m_bufSynapseStartIdx.get()));
		kernel.setArg(7, *(m_bufNeuronData1.get()));
		kernel.setArg(8, *(m_bufNeuronData2.get()));
		kernel.setArg(9, *(m_bufTestOut.get()));
	}
	catch(cl::Error e)
	{
		std::cout << e.what() << ": Error code " << e.err() << std::endl;   
		throw e;
	}

	printf("Starting buffer enqueuing.\n");
	// enqueue kernel-execution command 
	m_lpQueue = m_lpNervousSystem->QueueForDevice(0);
	printf("m_bufVm.\n");
	m_lpQueue->enqueueWriteBuffer(*(m_bufVm.get()), CL_TRUE, 0, sizeof(m_aryVm)*m_iNeuronCount,  m_aryVm, NULL, NULL);

	printf("m_bufVahp.\n");
	m_lpQueue->enqueueWriteBuffer(*(m_bufVahp.get()), CL_TRUE, 0, sizeof(m_aryVahp)*m_iNeuronCount,  m_aryVahp, NULL, NULL);

	printf("Starting buffer enqueuing.\n");
	m_lpQueue->enqueueWriteBuffer(*(m_bufIext.get()), CL_TRUE, 0, sizeof(m_aryIext)*m_iNeuronCount,  m_aryIext, NULL, NULL);

	printf("m_bufPostSynWeightDecay.\n");
	m_lpQueue->enqueueWriteBuffer(*(m_bufPostSynWeightDecay.get()), CL_TRUE, 0, sizeof(m_aryPostSynWeightDecay)*m_iNeuronCount,  m_aryPostSynWeightDecay, NULL, NULL);

	printf("m_bufSynapseStartIdx.\n");
	m_lpQueue->enqueueWriteBuffer(*(m_bufSynapseStartIdx.get()), CL_TRUE, 0, sizeof(m_arySynapseStartIdx)*m_iNeuronCount,  m_arySynapseStartIdx, NULL, NULL);

	printf("m_bufNeuronData1.\n");
	m_lpQueue->enqueueWriteBuffer(*(m_bufNeuronData1.get()), CL_TRUE, 0, sizeof(m_aryNeuronData1)*m_iNeuronCount,  m_aryNeuronData1, NULL, NULL);

	printf("m_bufNeuronData2.\n");
	m_lpQueue->enqueueWriteBuffer(*(m_bufNeuronData2.get()), CL_TRUE, 0, sizeof(m_aryNeuronData2)*m_iNeuronCount,  m_aryNeuronData2, NULL, NULL);

	printf("m_bufVsyn.\n");
	//m_lpQueue->enqueueWriteBuffer(*(m_bufVsyn.get()), CL_TRUE, 0, sizeof(m_aryVsyn)*m_iSynapseCount,  m_aryVsyn, NULL, NULL);

	printf("Ended buffer enqueuing.\n");
}


void FastSpikingNeuralModel::StepModel() 
{
	cl::Kernel &FSN_kernel = m_aryFsNeuronKernel->CLKernel();

	FSN_kernel.setArg(0, m_lpNervousSystem->TimeSlice());
	//printf("%d\n", m_lpNervousSystem->TimeSlice());

	m_lpQueue->enqueueNDRangeKernel(FSN_kernel, NULL, m_FSN_Global, m_FSN_Local);

	//m_lpQueue->enqueueReadBuffer(*(m_bufTestOut.get()), CL_TRUE, 0, sizeof(m_aryTestOut)*m_iNeuronCount,  m_aryTestOut, NULL, NULL);
	//m_lpQueue->enqueueReadBuffer(*(m_bufVm.get()), CL_TRUE, 0, sizeof(m_aryVm)*m_iNeuronCount,  m_aryVm, NULL, NULL);

	//m_aryData.push_back(m_aryVm[0]);
	//Display updated buffer
	//for(int i=0; i<10; i++) 
	//{
	//	printf("%6.5f, %6.5f", m_aryVm[i], m_aryTestOut[i]);
	//	printf("\n");
	//}
	//printf("\n\n");
}

	}
}