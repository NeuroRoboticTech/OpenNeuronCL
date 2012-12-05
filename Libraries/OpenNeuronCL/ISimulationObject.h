#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT ISimulationObject : public IOpenNeuronCLBase
	{
	public:
		ISimulationObject(void) {}
		virtual ~ISimulationObject(void) {}

		virtual void Initialize() = 0;
		virtual void StepSimulation() = 0;
	};

}