#pragma once

namespace OpenNeuronCL
{
	namespace NeuralModels
	{
		class FastSpikingNeuralModel : public INeuralModel
		{
		public:
			FastSpikingNeuralModel(void);
			virtual ~FastSpikingNeuralModel(void);

			virtual void Simulate(); 
			static INeuralModel *Create() {return new FastSpikingNeuralModel;};
		};

	}
}
