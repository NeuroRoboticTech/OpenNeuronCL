#pragma once

namespace OpenNeuronCL
{
	namespace NeuralModels
	{
		class FastSpikingNeuralModel : public NeuralModel
		{
		protected:
			shared_ptr<Kernel> m_aryFsNeuronKernel;
			shared_ptr<cl::CommandQueue> m_lpQueue;
			cl::NDRange ndGlobal;
			cl::NDRange ndLocal;
			unsigned char m_iActiveArray;
			int m_lLocalTimeSlice;

			vector< float > m_aryData;

			//Fast Spiking Data
			cl_float *m_aryVm, *m_aryVahp, *m_aryIinOn, *m_aryIinOff, *m_aryTestOut;
			cl_int *m_aryRefrCount; //, *m_arySpiked;

			shared_ptr< cl::Buffer > m_bufferVm, m_bufferVahp;
			shared_ptr< cl::Buffer > m_bufferIinOn, m_bufferIinOff, m_bufferRefrCount; 
			shared_ptr< cl::Buffer > m_bufferSpiked, m_bufferTestOut;

			virtual void SetupInitialMemory();
			virtual void StepModel();

		public:
			FastSpikingNeuralModel(INervousSystem *lpNS, double dblDT);
			virtual ~FastSpikingNeuralModel(void);

			virtual void Initialize();

			static shared_ptr<INeuralModel> Create(INervousSystem *lpNS, double dblDT) 
			{
				shared_ptr<INeuralModel> lpModel(new FastSpikingNeuralModel(lpNS, dblDT));
				return lpModel;
			};
		};

	}
}
