#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT INervousSystem
	{
	public:

		INervousSystem(void) {}
		virtual ~INervousSystem(void) {};

		virtual std::vector< boost::shared_ptr<INeuralModel> > &NeuralModels() = 0;
		virtual boost::shared_ptr<INeuralModel> AddNeuralModel(string strType) = 0;

	};

}

