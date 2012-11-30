#pragma once

namespace OpenNeuronCL
{



	class NervousSystem : public OpenNeuronCLBase, public INervousSystem
	{
	protected:
		std::map<cl::Platform> m_aryPlatforms;
		std::vector<cl::Device> m_aryDevices;

		std::vector< boost::shared_ptr<INeuralModel> > m_aryNeuralModels;

	public:
		NervousSystem(void);
		virtual ~NervousSystem(void);

		virtual unsigned int ID() {return m_iID;};

		virtual std::vector< boost::shared_ptr<INeuralModel> > NeuralModels() {return m_aryNeuralModels;};
		virtual boost::shared_ptr<INeuralModel> AddNeuralModel(string strType);
		virtual void RemoveNeuralModel(int iID) {};

		virtual void Initialize() = 0;
		virtual void StepSimulation() = 0;
		virtual void RunSimulation(double dblTime) = 0;



		static INervousSystem *Create() {return new NervousSystem;};
		static IOpenNeuronCLBase *CreateBase() {return new NervousSystem;};
	};

}