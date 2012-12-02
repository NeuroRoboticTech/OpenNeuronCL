#include "StdAfx.h"
#include "NervousSystem.h"

namespace OpenNeuronCL
{

NervousSystem::NervousSystem(void)
{
}


NervousSystem::~NervousSystem(void)
{
	int i = 5;
}

shared_ptr<INeuralModel> NervousSystem::AddNeuralModel(string strType, double dblDT)
{
	//shared_ptr<INervousSystem> lpSys = shared_from_this();
	shared_ptr<INeuralModel> lpModel = ClassFactory::GetNeuralModelInstance(strType, shared_from_this(), dblDT);
	m_aryNeuralModels.push_back(lpModel);
	return lpModel;
}

void NervousSystem::RemoveNeuralModel(int iID) 
{
}

void NervousSystem::Initialize()
{
	//BOOST_FOREACH(shared_ptr<INeuralModel> lpModel, m_aryNeuralModels )
	//	lpModel->Initialize();
}

void NervousSystem::StepSimulation()
{
}

void NervousSystem::RunSimulation(double dblTime)
{
}


}