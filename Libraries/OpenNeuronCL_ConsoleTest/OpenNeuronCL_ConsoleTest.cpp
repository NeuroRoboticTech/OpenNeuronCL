// OpenNeuronCL_ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//boost::shared_ptr<ONCL_ClassFactory> factory(ONCL_ClassFactory::GetInstance());

	//INeuralModel *lpNeuralModel = ONCL_ClassFactory::GetInstance("FastSpikingNeuralModel");
	boost::shared_ptr<INeuralModel> lpNeuralModel( OpenNeuronCL::ClassFactory::GetInstance("FastSpikingNeuralModel") );
	lpNeuralModel->Simulate();

	//factory<INeuralModel*()> factory;
	//InitializeClassFactory(factory);

	////std::auto_ptr<INeuralModel> a1( factory["FastSpikingNeuralModel"]() );

	//boost::shared_ptr<INeuralModel> lpNeuralModel( factory["FastSpikingNeuralModel"] );
	//lpNeuralModel->Simulate();

	//OpenNeuronCL::TestOpenCL test;

	//test.Run();
	 
	return 0;
}

