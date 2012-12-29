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

	unsigned short iRefrCount = 0;
	unsigned int iDelay = 0;
	unsigned char iSpiked = 0;

	unsigned int iData = lpFS->GenerateNeuronData1(0, 1, 0);
	BOOST_REQUIRE(iData == 0x00000180);

	lpFS->ExtractNeuronData1(iData, iRefrCount, iSpiked, iDelay);
	BOOST_REQUIRE(iRefrCount == 0);
	BOOST_REQUIRE(iSpiked == 1);
	BOOST_REQUIRE(iDelay == 0x000001);


	iData = lpFS->GenerateNeuronData1(127, 1, 0xFFFFFF);
	BOOST_REQUIRE(iData == 0xFFFFFFFF);

	lpFS->ExtractNeuronData1(iData, iRefrCount, iSpiked, iDelay);
	BOOST_REQUIRE(iRefrCount == 127);
	BOOST_REQUIRE(iSpiked == 1);
	BOOST_REQUIRE(iDelay == 0xFFFFFF);


	iData = lpFS->GenerateNeuronData1(127, 0, 0xFFFFFF);
	BOOST_REQUIRE(iData == 0xFFFFFE7F);

	lpFS->ExtractNeuronData1(iData, iRefrCount, iSpiked, iDelay);
	BOOST_REQUIRE(iRefrCount == 127);
	BOOST_REQUIRE(iSpiked == 0);
	BOOST_REQUIRE(iDelay == 0xFFFFFE);


	iData = lpFS->GenerateNeuronData1(1, 1, 1);
	BOOST_REQUIRE(iData == 0x00000381);

	lpFS->ExtractNeuronData1(iData, iRefrCount, iSpiked, iDelay);
	BOOST_REQUIRE(iRefrCount == 1);
	BOOST_REQUIRE(iSpiked == 1);
	BOOST_REQUIRE(iDelay == 000003);


	iData = lpFS->GenerateNeuronData1(1, 0, 1);
	BOOST_REQUIRE(iData == 0x00000201);
	
	lpFS->ExtractNeuronData1(iData, iRefrCount, iSpiked, iDelay);
	BOOST_REQUIRE(iRefrCount == 1);
	BOOST_REQUIRE(iSpiked == 0);
	BOOST_REQUIRE(iDelay == 0x000002);

	
	iData = lpFS->GenerateNeuronData1(0x0100, 0, 0x080000);
	BOOST_REQUIRE(iData == 0x10000000);
	
	//lpFS->ExtractNeuronData1(iData, iRefrCount, iSpiked, iDelay);
	//BOOST_REQUIRE(iRefrCount == 1);
	//BOOST_REQUIRE(iSpiked == 0);
	//BOOST_REQUIRE(iDelay == 0x000002);

	iRefrCount = 0; iSpiked = 1; iDelay = 0;
	for(int iIdx=0; iIdx<25; iIdx++)
	{
		iData = lpFS->GenerateNeuronData1(iRefrCount, iSpiked, iDelay);
		lpFS->ExtractNeuronData1(iData, iRefrCount, iSpiked, iDelay);
		iSpiked = 0;
	}

}



void TestFastSpikingNeuralModel::TestGenerateNeuronData2()
{
	shared_ptr<INervousSystem> lpNervousSystem = OpenNeuronCL::ClassFactory::GetNervousSystemInstance("NervousSystem");
	shared_ptr<INeuralModel> lpFastSpikingModel = lpNervousSystem->AddNeuralModel("FastSpikingNeuralModel", 0.0002);

	TestFastSpikingNeuralModel *lpFS = dynamic_cast<TestFastSpikingNeuralModel *>(lpFastSpikingModel.get());

	unsigned short iSynCount = 0;
	unsigned char iNeuronType = 0;

	unsigned int iData = lpFS->GenerateNeuronData2(0, 1);
	BOOST_REQUIRE(iData == 0x00010000);

	lpFS->ExtractNeuronData2(iData, iSynCount, iNeuronType);
	BOOST_REQUIRE(iSynCount == 0);
	BOOST_REQUIRE(iNeuronType == 1);


	iData = lpFS->GenerateNeuronData2(0xFFFF, 0x00);
	BOOST_REQUIRE(iData == 0x0000FFFF);

	lpFS->ExtractNeuronData2(iData, iSynCount, iNeuronType);
	BOOST_REQUIRE(iSynCount == 0xFFFF);
	BOOST_REQUIRE(iNeuronType == 0);


	iData = lpFS->GenerateNeuronData2(0x0000, 0xFF);
	BOOST_REQUIRE(iData == 0x00FF0000);

	lpFS->ExtractNeuronData2(iData, iSynCount, iNeuronType);
	BOOST_REQUIRE(iSynCount == 0);
	BOOST_REQUIRE(iNeuronType == 0xFF);
}


	}
}


BOOST_AUTO_TEST_SUITE (TestFastSpikingNeuralModelSuite)

BOOST_AUTO_TEST_CASE (TestGenerateNeuronData1)
{
	OpenNeuronCL::UnitTests::TestFastSpikingNeuralModel::TestGenerateNeuronData1();
}

BOOST_AUTO_TEST_CASE (TestGenerateNeuronData2)
{
	OpenNeuronCL::UnitTests::TestFastSpikingNeuralModel::TestGenerateNeuronData2();
}

BOOST_AUTO_TEST_SUITE_END( )
