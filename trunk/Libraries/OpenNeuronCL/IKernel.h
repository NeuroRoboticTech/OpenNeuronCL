#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT IKernel : public ISimulationObject
	{
	public:
		IKernel(INervousSystem *lpNS, INeuralModel *lpModel, string strKernelSource, string strKernelName) {}
		virtual ~IKernel(void) {}
	};

}
