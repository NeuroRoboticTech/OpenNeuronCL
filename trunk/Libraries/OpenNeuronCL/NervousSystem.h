#pragma once

namespace OpenNeuronCL
{

	class NervousSystem : public OpenNeuronCLBase, public INervousSystem
	{
	protected:
		std::vector<cl::Platform> m_aryPlatforms;
		std::vector<cl::Device> m_aryDevices;

		std::vector< boost::shared_ptr<INeuralModel> > m_aryNeuralModels;

	public:
		NervousSystem(void);
		virtual ~NervousSystem(void);

		virtual unsigned long ID() {return m_lID;};

		virtual std::vector< boost::shared_ptr<INeuralModel> > &NeuralModels() {return m_aryNeuralModels;};

		virtual boost::shared_ptr<INeuralModel> AddNeuralModel(string strType);

		static INervousSystem *Create() {return new NervousSystem;};
		static IOpenNeuronCLBase *CreateBase() {return new NervousSystem;};
	};

}