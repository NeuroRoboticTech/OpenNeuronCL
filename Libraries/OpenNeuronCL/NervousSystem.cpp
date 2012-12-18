#include "StdAfx.h"
#include "NervousSystem.h"

namespace OpenNeuronCL
{

NervousSystem::NervousSystem(void)
{
	m_lTimeSlice = 0;
	m_fltMinTimeStep = 0;
	m_dblRunSimTime = 0;
}


NervousSystem::~NervousSystem(void)
{
	int i = 5;
}

void NervousSystem::RecalculateMinTimeStep()
{
	float fltMin = -1;
	BOOST_FOREACH(shared_ptr<INeuralModel> lpModel, m_aryNeuralModels )
	{
		if(lpModel->TimeStep() < fltMin || fltMin < 0)
			fltMin = lpModel->TimeStep();
	}

	m_fltMinTimeStep = fltMin;
}

shared_ptr<cl::CommandQueue> NervousSystem::QueueForDevice(int iDeviceIdx)
{
	map<int, shared_ptr<cl::CommandQueue> >::iterator itQueue = m_aryQueues.find(iDeviceIdx);

	if(itQueue != m_aryQueues.end())
		return itQueue->second;
	else
		BOOST_THROW_EXCEPTION(QueueForDeviceNotFoundException(m_aryDevices[iDeviceIdx].vendor(), m_aryDevices[iDeviceIdx].name(), m_aryDevices[iDeviceIdx].driver_version()));
}

shared_ptr<INeuralModel> NervousSystem::AddNeuralModel(string strType, double dblDT)
{
	shared_ptr<INeuralModel> lpModel = ClassFactory::GetNeuralModelInstance(strType, this, dblDT);
	m_aryNeuralModels.push_back(lpModel);
	RecalculateMinTimeStep();
	return lpModel;
}

void NervousSystem::RemoveNeuralModel(int iID) 
{
	BOOST_THROW_EXCEPTION(MethodNotImplementedException("NervousSystem", "RemoveNeuralModel"));
}

void NervousSystem::Initialize()
{
	CreateContext();
	
	BOOST_FOREACH(shared_ptr<INeuralModel> lpModel, m_aryNeuralModels )
		lpModel->Initialize();
}

void NervousSystem::CreateContext()
{
	//First lets get the platform and device info
    //Place the GPU devices of the first platform into a context.
	//For now just use the first device. Later on lets add some control over this. 	
	cl::Platform::get(&m_aryPlatforms);
	m_aryPlatforms[0].getDevices(CL_DEVICE_TYPE_GPU, &m_aryDevices);
	cl::Context context(m_aryDevices);
      
	m_Context = shared_ptr<cl::Context>(new cl::Context(m_aryDevices));

	shared_ptr< cl::CommandQueue> lpQueue(new cl::CommandQueue(ActiveContext(), m_aryDevices[0]));
	m_aryQueues.insert(make_pair(0, lpQueue));
}


void NervousSystem::StepSimulation()
{
	BOOST_FOREACH(shared_ptr<INeuralModel> lpModel, m_aryNeuralModels )
		lpModel->StepSimulation();
	m_lTimeSlice++;
}

double NervousSystem::RunSimulation(float fltTime)
{
	int iTimeSlices = (int) ((fltTime / MinTimeStep()) + 0.5f);

	m_RunSimTimer.StartTimer();

	for(int iSlice=0; iSlice<iTimeSlices; iSlice++)
		StepSimulation();

	m_dblRunSimTime = m_RunSimTimer.StopTimer();
	std::cout << "Run Sim Total Time: " << m_dblRunSimTime << std::endl;   

	return m_dblRunSimTime;
}


}