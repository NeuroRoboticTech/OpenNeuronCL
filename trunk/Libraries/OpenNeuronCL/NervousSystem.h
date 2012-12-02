#pragma once

namespace OpenNeuronCL
{



	class NervousSystem : public OpenNeuronCLBase, public INervousSystem
	{
	protected:
		//std::map<cl::Platform> m_aryPlatforms;
		//std::vector<cl::Device> m_aryDevices;

		std::vector<shared_ptr<INeuralModel> > m_aryNeuralModels;

		shared_ptr<NervousSystem> shared_from_this()
		{
			return static_pointer_cast<NervousSystem>(INervousSystem::shared_from_this());
		}

	public:
		NervousSystem(void);
		virtual ~NervousSystem(void);

		virtual unsigned int ID() {return m_iID;};

		virtual std::vector<shared_ptr<INeuralModel> > NeuralModels() {return m_aryNeuralModels;};
		virtual shared_ptr<INeuralModel> AddNeuralModel(string strType, double dblDT);
		virtual void RemoveNeuralModel(int iID);

		virtual void Initialize();
		virtual void StepSimulation();
		virtual void RunSimulation(double dblTime);

		static shared_ptr<INervousSystem>Create() 
		{
			shared_ptr<INervousSystem> lpNS(new NervousSystem);
			return lpNS;
		};

		static IOpenNeuronCLBase *CreateBase() {return new NervousSystem;};
	};

}