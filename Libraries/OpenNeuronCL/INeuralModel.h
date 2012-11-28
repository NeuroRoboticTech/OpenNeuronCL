#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT INeuralModel
	{
	public:
		INeuralModel(void) {};
		virtual ~INeuralModel(void) {};

		virtual void Simulate() = 0;
	};

}
