
#define REFR_COUNT_MASK 0x0000007F
#define SPIKED_MASK 0x00000080
#define SPIKED_SHIFT 7
#define DELAY_COUNT_MASK 0xFFFFFF00
#define DELAY_COUNT_SHIFT 8
#define DELAY_ADD_SPIKE 4
#define SYNAPSE_COUNT_MASK 0x0000FFFF
#define NEURON_TYPE_MASK 0x00FF0000
#define NEURON_TYPE_SHIFT 16

#define SYNAPSE_DELAY_MASK   0x000000FF
#define SYNAPSE_TYPE_MASK 0x0000FF00
#define SYNAPSE_TYPE_SHIFT 8

//__constant float aryST_Decrement[2] = {0.064493000507354736f, 0.039210598915815353f};
__constant float aryST_Decrement[2] = {0.064493001f, 0.039210598915815353f};

inline void ExtractSynapseData1(unsigned int iSynapseData1, unsigned char *iDelayMaskIdx, unsigned char *iSynapseType)
{
	*iDelayMaskIdx = (iSynapseData1 & SYNAPSE_DELAY_MASK);
	*iSynapseType = (iSynapseData1 & SYNAPSE_TYPE_MASK) >> SYNAPSE_TYPE_SHIFT;
}

inline void ExtractNeuronData1(unsigned int iNeuronData1, unsigned int *iDelayBuffer)
{
	*iDelayBuffer = (iNeuronData1 & DELAY_COUNT_MASK) >> DELAY_COUNT_SHIFT;
}

__kernel void FastSpikingSynapse(unsigned int iTimeSlice, unsigned int iSeed, 
								__global float *aryVsyn, __global float *aryWeight, 
								__global float *aryPreSynWeightDecay, 
								__global unsigned int *arySynapseData1, 
								__global unsigned int *aryPreSynNeuronIdx,
								__global unsigned int *aryNeuronData1,
								__global float *arySynTestOut)
{
	int gid = get_global_id(0);
	size_t gsize = get_global_size(0);

	float fltVsyn = aryVsyn[gid];
	float fltWeight = aryWeight[gid];
	float fltPreSynWeightDecay = aryPreSynWeightDecay[gid];
	unsigned int iSynapseData1 = arySynapseData1[gid];
	unsigned int iPreSynNeuronIdx = aryPreSynNeuronIdx[gid];
	unsigned int iNeuronData1 = aryNeuronData1[iPreSynNeuronIdx];

	unsigned char iDelayMaskIdx;
	unsigned char iSynapseType;
	unsigned int iDelayBuffer;
	unsigned int iDelayMask = 1;

	ExtractSynapseData1(iSynapseData1, &iDelayMaskIdx, &iSynapseType);
	ExtractNeuronData1(iNeuronData1, &iDelayBuffer);

	//Decrement the synaptic current/generated voltage
	fltVsyn -= (fltVsyn*aryST_Decrement[iSynapseType]);

	//generate the delay mask used on the delay buffer to determine if a spike occurred.
	iDelayMask = iDelayMask << iDelayMaskIdx;
	unsigned int iSpiked = (iDelayBuffer & iDelayMask);
	
	if(iSpiked > 0)
		fltVsyn += fltWeight;

	aryVsyn[gid] = fltVsyn;
	aryWeight[gid] = fltWeight;
	aryPreSynWeightDecay[gid] = fltPreSynWeightDecay;
	arySynTestOut[gid] = iDelayBuffer;
}



