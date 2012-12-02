#include "StdAfx.h"
#include "NeuralModel.h"
#include "FastSpikingNeuralModel.h"
#include "NervousSystem.h"

#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>

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
	//NeuralModelMap["FastSpikingNeuralModel"] = boost::bind(&FastSpikingNeuralModel::Create);
}

shared_ptr<INervousSystem> ClassFactory::GetNervousSystemInstance(string strType)
{
	ClassFactory factory;
	//shared_ptr<INervousSystem> lpNervousSys(NervousSystem::Create()); //factory.NervousSystemMap[strType]());
	return factory.NervousSystemMap[strType]();
}


void ClassFactory::Test()
{
	//shared_ptr<INervousSystem> lpNS(new NervousSystem);
	shared_ptr<INervousSystem> lpNS = GetNervousSystemInstance("NervousSystem");

	shared_ptr<INeuralModel> lpModel = lpNS->AddNeuralModel("FastSPikingNeuralModel", 0.02);

}


}
