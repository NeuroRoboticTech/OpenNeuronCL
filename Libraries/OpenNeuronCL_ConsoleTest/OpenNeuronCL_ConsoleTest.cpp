// OpenNeuronCL_ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void Test()
{
	boost::shared_ptr<INeuralModel> lpNeuralModel = OpenNeuronCL::ClassFactory::GetNeuralModelInstance("FastSpikingNeuralModel");
	lpNeuralModel->Simulate();

}

int _tmain(int argc, _TCHAR* argv[])
{
	Test();
	int t = 6;

	return 0;
}

