#include "include/KernelRandomNumbers.h"

#define REFR_COUNT_MASK 0x0000007F
#define SPIKED_MASK 0x00000080
#define SPIKED_SHIFT 7
#define DELAY_COUNT_MASK 0xFFFFFF00
#define DELAY_COUNT_SHIFT 8
#define DELAY_ADD_SPIKE 4
#define SYN_COUNT_MASK 0x0000FFFF
#define NEURON_TYPE_MASK 0x00FF0000
#define NEURON_TYPE_SHIFT 16

__constant float aryNT_Decrement[2] = {0.039210598915815353f, 0.039210598915815353f};
__constant float aryNT_Vth[2] = {20.0f, 22.0f};
__constant float aryNT_VahpDecrement[2] = {0.064493000507354736, 0.064493000507354736};
__constant float aryNT_VahpWadj[2] = {-2.4271199703216553, -2.4271199703216553};
__constant float aryNT_Vmax[2] = {-0.1, -0.2};
__constant float aryNT_RefrCount[2] = {10, 15};
__constant float aryNT_IextConv[2] = {1, 1};

float CalculateAHPVoltageFloat(float fltVahp, unsigned char iSpiked, unsigned char iNeuronType)
{
	//Decrement the previous Vahp and THEN add more for a new spike if needed.

	//If there is current left, but decrement is being rounded off to 0 then
	//we need to keep decrementing by 1 until we get rid of all of the leftover current.
	if(fabs(fltVahp) > 0)
		fltVahp -= (fltVahp * aryNT_VahpDecrement[iNeuronType]);
	else
		fltVahp = 0;

	//If the pre-synaptic neuron spiked then add the synaptic weight to the current value.
	if(iSpiked)
		fltVahp += aryNT_VahpWadj[iNeuronType];

	return fltVahp;
}

float CalculateSynapticVoltage(unsigned int iSynStartIdx, unsigned short iSynCount, __global float *arySynapseVin)
{
	unsigned int iFinalIdx = iSynStartIdx + iSynCount;

	float fltSum = 0;
	for(unsigned int iIdx=iSynStartIdx; iIdx<iFinalIdx; iIdx++)
		fltSum += arySynapseVin[iIdx];

	return fltSum;
}

inline void ExtractNeuronData1(unsigned int iNeuronData1, unsigned short *iRefrCount, unsigned char *iSpiked, unsigned int *iDelayCount)
{
	*iRefrCount = (iNeuronData1 & REFR_COUNT_MASK);
	*iSpiked = (iNeuronData1 & SPIKED_MASK) >> SPIKED_SHIFT;
	*iDelayCount = (iNeuronData1 & DELAY_COUNT_MASK) >> DELAY_COUNT_SHIFT;
}

inline unsigned int GenerateNeuronData1(unsigned short iRefrCount, unsigned char iSpiked, unsigned int iDelayCount)
{
	//set the delay bits and shift over
	iDelayCount = (iDelayCount << 1) | iSpiked;
	unsigned int iData = (iDelayCount << DELAY_COUNT_SHIFT) | (iSpiked << SPIKED_SHIFT) | (iRefrCount & REFR_COUNT_MASK);
	return iData;
}

inline void ExtractNeuronData2(unsigned int iNeuronData2, unsigned short *iSynCount, unsigned char *iNeuronType)
{
	*iSynCount = (iNeuronData2 & SYN_COUNT_MASK);
	*iNeuronType = (iNeuronData2 & NEURON_TYPE_MASK) >> NEURON_TYPE_SHIFT;
}

__kernel void FastSpikingNeuron(unsigned int iTimeSlice, unsigned int iSeed, __global float *aryVm, 
								__global float *aryVahp, __global float *aryIin,
								__global float *aryPostSynWeightDecay, __global unsigned int *arySynapseStartIdx,
								__global unsigned int *aryNeuronData1, __global unsigned int *aryNeuronData2,
								__global float *aryTestOut)
{
	unsigned int gid = get_global_id(0);
	size_t gsize = get_global_size(0);

	float fltVm = aryVm[gid];
	float fltVahp = aryVahp[gid];
	float fltIin = aryIin[gid];

	//extract the ref count, spiked, and delay data
	unsigned int iNeuronData1 = aryNeuronData1[gid];
	unsigned int iNeuronData2 = aryNeuronData2[gid];
	unsigned short iRefrCount = 0;
	unsigned char iSpiked = 0;
	unsigned char iPrevSpiked = 0;
	unsigned int iDelayBuffer = 0;

	float fltPostSynWeightDecay = aryPostSynWeightDecay[gid];
	unsigned int iSynStartIdx = arySynapseStartIdx[gid];
	unsigned short iSynCount = 0; 
	unsigned char iNeuronType = 0;

	ExtractNeuronData1(iNeuronData1, &iRefrCount, &iSpiked, &iDelayBuffer);
	ExtractNeuronData2(iNeuronData2, &iSynCount, &iNeuronType);

	iPrevSpiked = iSpiked;

	float fltVsyn = 0; //CalculateSynapticVoltage(iSynStartIdx, iSynCount, arySynapseVin);

	fltVahp = CalculateAHPVoltageFloat(fltVahp, iSpiked, iNeuronType);

	float fltVext = fltIin * aryNT_IextConv[iNeuronType];

	float fltVnoise = 0;

#ifdef USE_NOISE
		fltVnoise = RandomFloat(gid, iTimeSlice, iSeed, -aryNT_Vmax[iNeuronType], aryNT_Vmax[iNeuronType]);
#endif

	fltVm += (fltVahp + fltVext + fltVsyn + fltVnoise - (fltVm*aryNT_Decrement[iNeuronType]));

	//For now lets just do one spike when it starts.
	//If we are in the refractory period then do not allow another spike to occur period.
	//If not then a spike will occur if the Vm goes above threshold.
	if(iRefrCount > 0)
	{
		iRefrCount--;
		iSpiked = 0;
	}
	else if(fltVm > aryNT_Vth[iNeuronType])
	{
		iRefrCount = aryNT_RefrCount[iNeuronType];
		iSpiked = 1;
	}
	else
	{
		iRefrCount = 0;
		iSpiked = 0;
	}


	iNeuronData1 = GenerateNeuronData1(iRefrCount, iSpiked, iDelayBuffer);

	//Fill data back into the global variables.
	aryVm[gid] = fltVm;
	aryVahp[gid] = fltVahp;
	aryPostSynWeightDecay[gid] = 0;
	aryNeuronData1[gid] = iNeuronData1;
	aryTestOut[gid] = iNeuronData1;
}



