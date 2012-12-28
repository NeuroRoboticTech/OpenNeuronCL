#pragma once

namespace OpenNeuronCL
{
	namespace UnitTests
	{
		class TestFastSpikingNeuralModel : public OpenNeuronCL::NeuralModels::FastSpikingNeuralModel
		{
		public:
			TestFastSpikingNeuralModel();
			virtual ~TestFastSpikingNeuralModel(void);

			static void TestGenerateNeuronData1();
		};

	}
}