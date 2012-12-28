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
			int m_iSeed;
			
			unsigned int m_iNeuronCount;
			unsigned int m_iSynapseCount;
			unsigned short m_iSynapsesPerNeuron;

			vector< float > m_aryData;

			cl::NDRange m_FSN_Global;
			cl::NDRange m_FSN_Local;

			//Neuron Fast Spiking Data
			cl_float *m_aryVm, *m_aryVahp, *m_aryIext;
			cl_float *m_aryPostSynWeightDecay, *m_aryTestOut;
			cl_uint *m_arySynapseStartIdx;

			//This contains Refractory count (bits 0-6), Spike (bit 7), delay ring (bits 8-31)
			cl_uint *m_aryNeuronData1;

			//This contains Synapse Count (bits 0-15), Neuron Type (bits 16-23), future use (bits 24-31)
			cl_uint *m_aryNeuronData2; 

			shared_ptr< cl::Buffer > m_bufVm, m_bufVahp, m_bufIext; 
			shared_ptr< cl::Buffer > m_bufPostSynWeightDecay, m_bufTestOut;
			shared_ptr< cl::Buffer > m_bufSynapseStartIdx, m_bufNeuronData1, m_bufNeuronData2;
			//shared_ptr< cl::Buffer > m_bufSynapseCount, m_bufNeuronTypeID;

			//shared_ptr< cl::Buffer > m_bufTest;

			//Synapse Fast Spiking Data
			cl_float *m_aryVsyn, *m_aryWeight, *m_aryPreSynWeightDecay;
			cl_uchar *m_arySynapseTypeID; 
			cl_uint *m_aryPreSynNeuronIdx;

			shared_ptr< cl::Buffer > m_bufVsyn, m_bufWeight, m_bufPreSynWeightDecay;
			shared_ptr< cl::Buffer > m_bufSynapseTypeID, m_bufPreSynNeuronIdx; 

			virtual void SetupInitialMemory();
			virtual void StepModel();

			void ExtractNeuronData1(unsigned int iNeuronData1, unsigned short &iRefrCount, unsigned char &iSpiked, unsigned int &iDelayCount);
			unsigned int GenerateNeuronData1(unsigned short iRefrCount, unsigned char iSpiked, unsigned int iDelayCount);
			void ExtractNeuronData2(unsigned int iNeuronData2, unsigned short &iSynCount, unsigned char &iNeuronType);
			unsigned int GenerateNeuronData2(unsigned short iSynCount, unsigned char iNeuronType);

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
