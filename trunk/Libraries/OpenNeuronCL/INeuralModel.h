#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT INeuralModel : public IOpenNeuronCLBase
	{
	public:
		INeuralModel(shared_ptr<INervousSystem> lpNS, double dblDT) {};
		virtual ~INeuralModel(void) {};

		virtual double TimeStep() = 0;
		virtual void TimeStep(double dblDt) = 0;

		virtual void Simulate() = 0;
	};

}
