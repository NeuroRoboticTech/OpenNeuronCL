#pragma once

namespace OpenNeuronCL
{
	class NeuralModel : public OpenNeuronCLBase, public INeuralModel
	{
	protected:
		NervousSystem *m_lpNervousSystem;
		short m_iTimeStepInterval;
		short m_iTimeStepCount;
		float m_fltTimeStep;
		vector< shared_ptr<IKernel> > m_aryKernels;

		int m_iGlobalDataSize;
		int m_iLocalDataSize;

		virtual void InitializeKernels();
		virtual void SetupInitialMemory() = 0;

		virtual void StepModel() = 0;

	public:
		NeuralModel(INervousSystem *lpNS, double dblDT);
		virtual ~NeuralModel(void);

		virtual unsigned int ID() {return m_iID;};

		virtual NervousSystem *NervousSystem() {return m_lpNervousSystem;}; 

		virtual void TimeStepInterval(short iVal);
		virtual short TimeStepInterval();

		virtual short TimeStepCount() {return m_iTimeStepCount;};
		virtual void ResetStepCounter();

		virtual float TimeStep() {return m_fltTimeStep;};
		virtual void TimeStep(float fltDt);

		virtual std::vector< shared_ptr<IKernel> > Kernels() {return m_aryKernels;};
		virtual shared_ptr<IKernel> AddKernel(string strKernelSource, string strKernelName);
		virtual void RemoveKernel(int iID);

		virtual bool NeedToStep(bool bIncrement);
		virtual void StepSimulation();
	};

}
