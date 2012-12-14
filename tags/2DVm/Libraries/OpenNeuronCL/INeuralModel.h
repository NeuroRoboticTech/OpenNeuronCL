#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT INeuralModel : public ISimulationObject
	{
	public:
		INeuralModel(INervousSystem *lpNS, double dblDT) {};
		virtual ~INeuralModel(void) {};
		
		virtual void TimeStepInterval(short iVal) = 0;
		virtual short TimeStepInterval() = 0;

		virtual short TimeStepCount() = 0;
		virtual void ResetStepCounter() = 0;

		virtual float TimeStep() = 0;
		virtual void TimeStep(float fltDt) = 0;

		virtual std::vector< shared_ptr<IKernel> > Kernels() = 0;
		virtual shared_ptr<IKernel> AddKernel(string strKernelSource, string strKernelName) = 0;
		virtual void RemoveKernel(int iID) = 0;

		virtual bool NeedToStep(bool bIncrement) = 0;
	};

}
