#pragma once

namespace OpenNeuronCL
{

	class NervousSystem : public OpenNeuronCLBase, public INervousSystem
	{
	protected:
		unsigned long m_iTimeSlice;
		float m_fltMinTimeStep;
		double m_dblRunSimTime;

		OpenNeuronCL::Timer m_RunSimTimer;

		std::vector<cl::Platform> m_aryPlatforms;
		std::vector<cl::Device> m_aryDevices;
		shared_ptr<cl::Context> m_Context;
		std::map< int, shared_ptr<cl::CommandQueue> > m_aryQueues;

		std::vector<shared_ptr<INeuralModel> > m_aryNeuralModels;

		virtual void CreateContext();

	public:
		NervousSystem(void);
		virtual ~NervousSystem(void);

		virtual unsigned int ID() {return m_iID;};

		virtual void TimeSlice(unsigned int iSlice) {m_iTimeSlice = iSlice;};
		virtual unsigned int TimeSlice() {return m_iTimeSlice;};

		virtual float MinTimeStep() {return m_fltMinTimeStep;};

		virtual void RecalculateMinTimeStep();

		virtual std::vector<cl::Platform> ActivePlatforms(INeuralModel *lpModel) {return m_aryPlatforms;};
		virtual std::vector<cl::Device> ActiveDevices(INeuralModel *lpModel) {return m_aryDevices;};
		virtual cl::Context &ActiveContext() {return *(m_Context.get());};
		virtual shared_ptr< cl::CommandQueue > QueueForDevice(int iDeviceIdx);  

		virtual std::vector<shared_ptr<INeuralModel> > NeuralModels() {return m_aryNeuralModels;};
		virtual shared_ptr<INeuralModel> AddNeuralModel(string strType, double dblDT);
		virtual void RemoveNeuralModel(int iID);

		virtual void Initialize();
		virtual void StepSimulation();
		virtual double RunSimulation(float fltTime);

		static shared_ptr<INervousSystem>Create() 
		{
			shared_ptr<INervousSystem> lpNS(new NervousSystem);
			return lpNS;
		};
	};

}