#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT INervousSystem : public ISimulationObject
	{
	public:

		INervousSystem(void) {}
		virtual ~INervousSystem(void) {};

		virtual void TimeSlice(unsigned long lSlice) = 0;
		virtual unsigned long TimeSlice() = 0;

		virtual float MinTimeStep() = 0;

		virtual void RecalculateMinTimeStep() = 0;

		virtual std::vector<shared_ptr<INeuralModel> > NeuralModels() = 0;
		virtual shared_ptr<INeuralModel> AddNeuralModel(string strType, double dblDT) = 0;
		virtual void RemoveNeuralModel(int iID) = 0;

		virtual void Initialize() = 0;
		virtual void StepSimulation() = 0;
		virtual double RunSimulation(float fltTime) = 0;
	};

}

