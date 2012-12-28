#pragma once

namespace OpenNeuronCL
{
	namespace NeuralModels
	{
		class TestSynapseSummation : public NeuralModel
		{
		protected:
			shared_ptr<Kernel> m_aryFsNeuronKernel;
			shared_ptr<cl::CommandQueue> m_lpQueue;
			cl::NDRange ndGlobal;
			cl::NDRange ndLocal;
			unsigned int m_iSynapsesPerNeuron;
			unsigned int m_iNeuronCount;

			cl_float *m_arySynapseI, *m_aryNeuronIin;
			cl_uint *m_arySynapsePostNeuronIdx;

			cl_uint *arySynapseStartIdx;
			cl_uint *arySynapseCount;

			shared_ptr< cl::Buffer > m_bufferSynapseI, m_bufferSynapsePostNeuronIdx, m_bufferNeuronIin;
	
			shared_ptr< cl::Buffer > m_bufferSynapseStartIdx, m_bufferSynapseCount;
	
			virtual void SetupInitialMemory();

			virtual void SetupInitialAtomicAddMemory();
			virtual void SetupInitialAddSynapsePerNeuronMemory();

			virtual void StepAtomicAdd();
			virtual void StepAddSynapsePerNeuron();

			virtual void StepModel();

		public:
			TestSynapseSummation(INervousSystem *lpNS, double dblDT);
			virtual ~TestSynapseSummation(void);

			virtual void Initialize();

			static shared_ptr<INeuralModel> Create(INervousSystem *lpNS, double dblDT) 
			{
				shared_ptr<INeuralModel> lpModel(new TestSynapseSummation(lpNS, dblDT));
				return lpModel;
			};
		};

	}
}
