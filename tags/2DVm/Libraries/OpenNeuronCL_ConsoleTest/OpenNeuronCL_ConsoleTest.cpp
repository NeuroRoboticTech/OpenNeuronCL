// OpenNeuronCL_ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void Test()
{
	//OpenNeuronCL::ClassFactory::Test();

	shared_ptr<INervousSystem> lpNervousSystem = OpenNeuronCL::ClassFactory::GetNervousSystemInstance("NervousSystem");

	shared_ptr<INeuralModel> lpFastSpikingModel = lpNervousSystem->AddNeuralModel("FastSpikingNeuralModel", 0.0002);

	lpNervousSystem->Initialize();

	//for(int i=0; i<10; i++)
	//	lpNervousSystem->StepSimulation();

	lpNervousSystem->RunSimulation(0.2f);

}

int _tmain(int argc, _TCHAR* argv[])
{
	Test();
	int t = 6;

	return 0;
}

