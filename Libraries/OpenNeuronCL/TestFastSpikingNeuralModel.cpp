#include "StdAfx.h"
#include "ONCL_ClassFactory.H"
#include "NervousSystem.h"
#include "FastSpikingNeuralModel.h"
#include "TestFastSpikingNeuralModel.h"

#include <boost/test/unit_test.hpp>


namespace OpenNeuronCL
{
	namespace UnitTests
	{


TestFastSpikingNeuralModel::TestFastSpikingNeuralModel(void) : OpenNeuronCL::NeuralModels::FastSpikingNeuralModel(NULL, 0.2)
{
}


TestFastSpikingNeuralModel::~TestFastSpikingNeuralModel(void)
{
}


void TestFastSpikingNeuralModel::TestGenerateNeuronData1()
{
	shared_ptr<INervousSystem> lpNervousSystem = OpenNeuronCL::ClassFactory::GetNervousSystemInstance("NervousSystem");
	shared_ptr<INeuralModel> lpFastSpikingModel = lpNervousSystem->AddNeuralModel("FastSpikingNeuralModel", 0.0002);

	TestFastSpikingNeuralModel *lpFS = dynamic_cast<TestFastSpikingNeuralModel *>(lpFastSpikingModel.get());

	unsigned int iData = lpFS->GenerateNeuronData1(0, 1, 0);
	BOOST_REQUIRE(iData == 0x00000070);

}

	}
}


BOOST_AUTO_TEST_SUITE (TestFastSpikingNeuralModelSuite)

BOOST_AUTO_TEST_CASE (TestGenerateNeuronData1)
{
	OpenNeuronCL::UnitTests::TestFastSpikingNeuralModel::TestGenerateNeuronData1();
}

BOOST_AUTO_TEST_SUITE_END( )
