#pragma once

namespace OpenNeuronCL
{
	namespace NeuralModels
	{
		class FastSpikingNeuralModel : public NeuralModel
		{
		protected:
			string m_strOutputfile; 

			shared_ptr<Kernel> m_aryFsNeuronKernel;
			shared_ptr<Kernel> m_aryFsSynapseKernel;
			shared_ptr<cl::CommandQueue> m_lpQueue;
			int m_iSeed;
			
			unsigned int m_iNeuronCount;
			unsigned int m_iSynapseCount;
			unsigned short m_iSynapsesPerNeuron;

			vector<float> m_aryTestData1;
			vector<float> m_aryTestData2;
			//vector<unsigned int> m_aryTestData2;

			vector<float> m_aryTestData3;
			vector<float> m_aryTestData4;

			cl::NDRange m_FSN_Global;
			cl::NDRange m_FSN_Local;

			cl::NDRange m_FSS_Global;
			cl::NDRange m_FSS_Local;

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

			//Synapse Fast Spiking Data
			cl_float *m_aryVsyn, *m_aryWeight, *m_aryPreSynWeightDecay, *m_arySynTestOut;
			cl_uint *m_aryPreSynNeuronIdx, *m_arySynapseData1;

			shared_ptr< cl::Buffer > m_bufVsyn, m_bufWeight, m_bufPreSynWeightDecay, m_bufSynTestOut;
			shared_ptr< cl::Buffer > m_bufSynapseData1, m_bufPreSynNeuronIdx; 

			shared_ptr<cl::Event> m_aryMarkerEvent;

			OpenNeuronCL::Timer m_RunSimTimer;

			virtual void SetupInitialMemory();
			virtual void StepModel();

			void ExtractNeuronData1(unsigned int iNeuronData1, unsigned short &iRefrCount, unsigned char &iSpiked, unsigned int &iDelayCount);
			unsigned int GenerateNeuronData1(unsigned short iRefrCount, unsigned char iSpiked, unsigned int iDelayCount);
			void ExtractNeuronData2(unsigned int iNeuronData2, unsigned short &iSynCount, unsigned char &iNeuronType);
			unsigned int GenerateNeuronData2(unsigned short iSynCount, unsigned char iNeuronType);

			void ExtractSynapseData1(unsigned int iSynapseData1, unsigned char &iDelayMaskIdx, unsigned char &iSynapseType);
			unsigned int GenerateSynapseData1(unsigned char iDelayMaskIdx, unsigned char iSynapseType);

			virtual void SaveOutput(string strFilename);

			virtual void StepSynapses();
			virtual void StepNeurons();

		public:
			FastSpikingNeuralModel(INervousSystem *lpNS, double dblDT);
			virtual ~FastSpikingNeuralModel(void);

			virtual void Initialize();
			virtual void StartingStepSequence();
			virtual void EndingStepSequence();

			void FinishProcessing();

			static shared_ptr<INeuralModel> Create(INervousSystem *lpNS, double dblDT) 
			{
				shared_ptr<INeuralModel> lpModel(new FastSpikingNeuralModel(lpNS, dblDT));
				return lpModel;
			};

		};

	}
}
