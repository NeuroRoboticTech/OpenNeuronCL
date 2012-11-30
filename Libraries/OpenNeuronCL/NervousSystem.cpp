#include "StdAfx.h"
#include "NervousSystem.h"

namespace OpenNeuronCL
{

NervousSystem::NervousSystem(void)
{
}


NervousSystem::~NervousSystem(void)
{
}

boost::shared_ptr<INeuralModel> NervousSystem::AddNeuralModel(string strType)
{
	boost::shared_ptr<INeuralModel> lpModel = ClassFactory::GetNeuralModelInstance(strType);
	m_aryNeuralModels.push_back(lpModel);
	return lpModel;
}


}