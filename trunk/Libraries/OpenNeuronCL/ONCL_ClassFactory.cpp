#include "StdAfx.h"
#include "NervousSystem.h"
#include "NeuralModel.h"
#include "Kernel.h"
#include "FastSpikingNeuralModel.h"

namespace OpenNeuronCL
{
	
ClassFactory::ClassFactory(void)
{
	//Fill in neuron base map
	//NeruonBaseMap["FastSpikingNeuralModel"] = boost::bind(&FastSpikingNeuralModel::CreateBase);
	//NeruonBaseMap["NervousSystem"] = boost::bind(&NervousSystem::CreateBase);

	//Fill in Nervous System map
	NervousSystemMap["NervousSystem"] = boost::bind(&NervousSystem::Create);

	//Fill in neural model map
	NeuralModelMap["FastSpikingNeuralModel"] = boost::bind(&FastSpikingNeuralModel::Create, _1, _2);

	//Fill in kernel map
	KernelMap["Kernel"] = boost::bind(&Kernel::Create, _1, _2, _3, _4);
}

shared_ptr<INervousSystem> ClassFactory::GetNervousSystemInstance(string strType)
{
	ClassFactory factory;
	return factory.NervousSystemMap[strType]();
}

shared_ptr<INeuralModel> ClassFactory::GetNeuralModelInstance(string strType, INervousSystem *lpNS, double dblDT)
{
	ClassFactory factory;
	shared_ptr<INeuralModel> lpModel(factory.NeuralModelMap[strType](lpNS, dblDT));
	return lpModel;
}

shared_ptr<IKernel> ClassFactory::GetKernelInstance(string strType, INervousSystem *lpNS, INeuralModel *lpModel, string strKernelSource, string strKernelName)
{
	ClassFactory factory;
	shared_ptr<IKernel> lpKernel(factory.KernelMap[strType](lpNS, lpModel, strKernelSource, strKernelName));
	return lpKernel;
}

//
//void ClassFactory::Test()
//{
//	//shared_ptr<INervousSystem> lpNS(new NervousSystem);
//	shared_ptr<INervousSystem> lpNS = GetNervousSystemInstance("NervousSystem");
//
//	shared_ptr<INeuralModel> lpModel = lpNS->AddNeuralModel("FastSPikingNeuralModel", 0.02);
//
//}


}
