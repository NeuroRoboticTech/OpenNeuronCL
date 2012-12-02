#pragma once

namespace OpenNeuronCL
{
	namespace NeuralModels
	{
		class FastSpikingNeuralModel : public NeuralModel
		{
		public:
			FastSpikingNeuralModel(shared_ptr<INervousSystem> lpNS, double dblDT);
			virtual ~FastSpikingNeuralModel(void);

			virtual void Simulate(); 
			static INeuralModel *Create(shared_ptr<INervousSystem> lpNS, double dblDT) {return new FastSpikingNeuralModel(lpNS, dblDT);};
		};

	}
}
