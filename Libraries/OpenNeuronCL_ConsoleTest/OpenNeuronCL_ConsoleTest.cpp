// OpenNeuronCL_ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void Test()
{
	boost::shared_ptr<INervousSystem> lpNervousSystem = OpenNeuronCL::ClassFactory::GetNervousSystemInstance("NervousSystem");

	boost::shared_ptr<INeuralModel> lpFastSpikingModel = lpNervousSystem->AddNeuralModel("FastSpikingNeuralModel");

	lpFastSpikingModel->TimeStep(0.02);

	lpNervousSystem->Initialize();

	lpNervousSystem->Simulate();

}

int _tmain(int argc, _TCHAR* argv[])
{
	Test();
	int t = 6;

	return 0;
}

