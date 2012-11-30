#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT INervousSystem : public IOpenNeuronCLBase
	{
	public:

		INervousSystem(void) {}
		virtual ~INervousSystem(void) {};

		virtual std::vector< boost::shared_ptr<INeuralModel> > NeuralModels() = 0;
		virtual boost::shared_ptr<INeuralModel> AddNeuralModel(string strType) = 0;
		virtual void RemoveNeuralModel(int iID) = 0;

		virtual void Initialize() = 0;
		virtual void StepSimulation() = 0;
		virtual void RunSimulation(double dblTime) = 0;
	};

}

