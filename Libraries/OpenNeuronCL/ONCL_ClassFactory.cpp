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
	NeruonBaseMap["FastSpikingNeuralModel"] = boost::bind(&FastSpikingNeuralModel::CreateBase);
	NeruonBaseMap["NervousSystem"] = boost::bind(&NervousSystem::CreateBase);

	//Fill in neural model map
	NeuralModelMap["FastSpikingNeuralModel"] = boost::bind(&FastSpikingNeuralModel::Create);

	//Fill in Nervous System map
	NervousSystemMap["NervousSystem"] = boost::bind(&NervousSystem::Create);
}

}
