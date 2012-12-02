#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT INervousSystem : public IOpenNeuronCLBase, public enable_shared_from_this<INervousSystem>
	{
	public:

		INervousSystem(void) {}
		virtual ~INervousSystem(void) {};

		virtual std::vector<shared_ptr<INeuralModel> > NeuralModels() = 0;
		virtual shared_ptr<INeuralModel> AddNeuralModel(string strType, double dblDT) = 0;
		virtual void RemoveNeuralModel(int iID) = 0;

		virtual void Initialize() = 0;
		virtual void StepSimulation() = 0;
		virtual void RunSimulation(double dblTime) = 0;
	};

}

