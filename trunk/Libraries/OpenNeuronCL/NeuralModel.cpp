#include "StdAfx.h"
#include "NeuralModel.h"

namespace OpenNeuronCL
{

NeuralModel::NeuralModel(INervousSystem *lpNS, double dblDT) : INeuralModel(lpNS, dblDT)
{
	m_lpNervousSystem = dynamic_cast<OpenNeuronCL::NervousSystem*>(lpNS);

	if(!m_lpNervousSystem)
		BOOST_THROW_EXCEPTION(BasePtrNotInitException("NeuralModel", "NervousSystem"));

	m_iTimeStepInterval = 0;
	m_iTimeStepCount = 0;
	TimeStep(dblDT);

	m_iGlobalDataSize = 1024;
	m_iLocalDataSize = 32;
}

NeuralModel::~NeuralModel(void)
{		
	int i = 5;
}

short NeuralModel::TimeStepInterval()
{return m_iTimeStepInterval;}

void NeuralModel::TimeStepInterval(short iVal)
{
	if(iVal == 0) iVal = 1;

	if(iVal <= 0)
		BOOST_THROW_EXCEPTION(InvalidParamValueException("NeuralModel", "TimeStepInterval", boost::lexical_cast<std::string>(iVal), "must be greater than zero."));

	Std_IsAboveMin((int) 0, (int) iVal, TRUE, "TimeStepInterval");
	m_iTimeStepInterval = iVal;
}

void NeuralModel::TimeStep(float fltVal)
{
	if(fltVal <= 0)
		BOOST_THROW_EXCEPTION(InvalidParamValueException("NeuralModel", "TimeStep", boost::lexical_cast<std::string>(fltVal), "must be greater than zero."));

	//Set it so that it will be taken into consideration when finding min value.
	m_fltTimeStep = fltVal;

	m_lpNervousSystem->RecalculateMinTimeStep();

	//Find min time step.
	float fltMin = m_lpNervousSystem->MinTimeStep();

	//Division
	int iDiv = (int) ((fltVal / fltMin) + 0.5f);

	//Find the number of timeslices that need to occur before this module is updated
	TimeStepInterval(iDiv);

	//Now recaculate the time step using the minimum time step as the base.
	m_fltTimeStep = m_lpNervousSystem->MinTimeStep() * m_iTimeStepInterval;

	m_lpNervousSystem->RecalculateMinTimeStep();
}


shared_ptr<IKernel> NeuralModel::AddKernel(string strKernelSource, string strKernelName)
{
	shared_ptr<IKernel> lpKernel = OpenNeuronCL::ClassFactory::GetKernelInstance("Kernel", m_lpNervousSystem, this, strKernelSource, strKernelName);
	m_aryKernels.push_back(lpKernel);
	return lpKernel;
}

void NeuralModel::RemoveKernel(int iID)
{
	BOOST_THROW_EXCEPTION(MethodNotImplementedException("NeuralModel", "RemoveKernel"));
}

void NeuralModel::InitializeKernels()
{
	BOOST_FOREACH(shared_ptr<IKernel> lpKernel, m_aryKernels )
		lpKernel->Initialize();
}

bool NeuralModel::NeedToStep(bool bIncrement)
{
	if(bIncrement)
		m_iTimeStepCount++;

	if(m_iTimeStepInterval == m_iTimeStepCount)
		return TRUE;
	else
		return FALSE;
}

void NeuralModel::ResetStepCounter()
{
	m_iTimeStepCount = 0;
}

void NeuralModel::StepSimulation() 
{
	if(NeedToStep(true))
	{
		StepModel();
		ResetStepCounter();
	}
}


}