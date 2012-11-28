#include "StdAfx.h"
#include "ONCL_ClassFactory.h"
#include "FastSpikingNeuralModel.h"

#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>

namespace OpenNeuronCL
{
	
ONCL_ClassFactory::ONCL_ClassFactory(void)
{
}


ONCL_ClassFactory::~ONCL_ClassFactory(void)
{
}

boost::shared_ptr<INeuralModel> ONCL_ClassFactory::CreateNeuralModel(string strType, BOOL bThrowError)
{
	boost::shared_ptr<INeuralModel> ptr;
	boost::to_upper(strType);

	if(strType == "FASTSPIKINGNEURALMODEL")
		ptr = boost::shared_ptr<INeuralModel>(new FastSpikingNeuralModel);
	else if(bThrowError)
		BOOST_THROW_EXCEPTION(InvalidNeuronModelTypeException("Neural Model Type", strType)); 
	
	return ptr;
}


}
