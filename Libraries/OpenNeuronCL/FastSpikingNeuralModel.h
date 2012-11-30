#pragma once

namespace OpenNeuronCL
{
	namespace NeuralModels
	{
		class FastSpikingNeuralModel : public NeuralModel
		{
		public:
			FastSpikingNeuralModel(void);
			virtual ~FastSpikingNeuralModel(void);

			virtual void Simulate(); 
			static INeuralModel *Create() {return new FastSpikingNeuralModel;};
			static IOpenNeuronCLBase *CreateBase() {return new FastSpikingNeuralModel;};
		};

	}
}
