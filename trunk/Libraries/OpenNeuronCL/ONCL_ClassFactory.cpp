#include "StdAfx.h"
#include "ONCL_ClassFactory.h"
#include "FastSpikingNeuralModel.h"

#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>

namespace OpenNeuronCL
{
	
ClassFactory::ClassFactory(void)
{
	map["FastSpikingNeuralModel"] = boost::bind(&FastSpikingNeuralModel::Create);
}

}
