#pragma once

namespace OpenNeuronCL
{
	class Kernel : public OpenNeuronCLBase, public IKernel
	{
	protected:
		NervousSystem *m_lpNervousSystem;
		NeuralModel *m_lpModel;
		shared_ptr<cl::Program> m_Program;
		shared_ptr<cl::Kernel> m_Kernel;

		vector<string> m_arySourceFiles;
		string m_strKernelName;

		virtual void Build();

	public:
		Kernel(INervousSystem *lpNS, INeuralModel *lpModel, string strKernelSource, string strKernelName);
		virtual ~Kernel(void);

		virtual unsigned int ID() {return m_iID;};

		virtual cl::Program &CLProgram() {return *(m_Program.get());};
		virtual cl::Kernel &CLKernel() {return *(m_Kernel.get());};

		virtual void SetArg(int iIdx, cl::Buffer &buf);

		virtual void Initialize();
		virtual void StepSimulation() {};

		static shared_ptr<IKernel> Create(INervousSystem *lpNS, INeuralModel *lpModel, string strKernelSource, string strKernelName) 
		{
			shared_ptr<IKernel> lpKernel(new Kernel(lpNS, lpModel, strKernelSource, strKernelName));
			return lpKernel;
		};
	};

}