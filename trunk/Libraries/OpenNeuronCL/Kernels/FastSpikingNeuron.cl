#include "include/KernelRandomNumbers.h"

#define REFR_COUNT_MASK 0x0007
#define SPIKED_MASK 0x0008
#define SPIKED_SHIFT 3
#define DELAY_COUNT_MASK 0xFFF0
#define DELAY_COUNT_SHIFT 8
#define DELAY_ADD_SPIKE 4

__constant float aryNT_Decrement[2] = {0.039210598915815353f, 0.039210598915815353f};
__constant float aryNT_Vth[2] = {20.0f, 22.0f};
__constant float aryNT_Vth[2] = {20.0f, 22.0f};
__constant float aryNT_VahDecrement[2] = {0.064493000507354736, 0.064493000507354736};
__constant float aryNT_VahWadj[2] = {-2.4271199703216553, -2.4271199703216553};
__constant float aryNT_Vmax[2] = {-0.1, -0.2};
__constant float aryNT_RefrCount[2] = {10, 15};

float CalculateAHPVoltageFloat(float fltVahp, unsigned char iSpiked, unsigned char iNeuronType)
{
	//Decrement the previous Vahp and THEN add more for a new spike if needed.

	//If there is current left, but decrement is being rounded off to 0 then
	//we need to keep decrementing by 1 until we get rid of all of the leftover current.
	if(fabs(fltVahp) > 0)
		fltVahp -= (fltVahp * aryNT_VahDecrement[iNeuronType]);
	else
		fltVahp = 0;

	//If the pre-synaptic neuron spiked then add the synaptic weight to the current value.
	if(iSpiked)
		fltVahp += aryNT_VahDecrement[iNeuronType];

	return fltVahp;
}

float CalculateSynapticVoltage(unsigned int iSynStartIdx, unsigned short iSynCount, __global float *arySynapseVin)
{
	unsigned int iFinalIdx = iSynapseStartIdx + iSynapseCount;

	float fltSum = 0;
	for(unsigned int iIdx=iSynapseStartIdx; iIdx<iFinalIdx; iIdx++)
		fltSum += arySynapseVin[iIdx];

	return fltSum;
}

__kernel void FastSpikingNeuron(unsigned int iTimeSlice, unsigned char iActiveArray, 
								unsigned int iSeed, __global float *aryVm, 
								__global float *aryVahp, __global float *aryIin,
								__global float *aryPostSynWeightDecay, __global unsigned int *arySynapseStartIdx,
								__global unsigned short *arySynapseCount, __global unsigned int *aryData, 
								__global unsigned char *aryNeuronTypeID, __global float *arySynapseVin,
								__global float *aryTestOut)
{
	unsigned int gid = get_global_id(0);
	size_t gsize = get_global_size(0);

	unsigned int iActiveIdx = (gsize*iActiveArray)+gid;
	unsigned int iInactiveIdx = (gsize*!iActiveArray) + gid;

	float fltVm = aryVm[iInactiveIdx];
	float fltVahp = aryVahp[gid];
	float fltIin = aryIin[gid];

	//extract the ref count, spiked, and delay data
	unsigned int iData = aryData[gid];
	unsigned short iRefrCount = (iData & REFR_COUNT_MASK);
	unsigned char iSpiked = (iData & SPIKED_MASK) >> SPIKED_SHIFT;
	unsigned char iPrevSpiked = iSpiked;
	unsigned int iDelayCount = (iData & DELAY_COUNT_MASK) >> DELAY_COUNT_SHIFT;

	float fltPostSynWeightDecay = aryPostSynWeightDecay[gid];
	unsigned int iSynStartIdx = arySynapseStartIdx[gid];
	unsigned short iSynCount = arySynapseCount[gid];
	unsigned char iNeuronType = aryNeuronTypeID[gid];

	fltVsyn = CalculateSynapticVoltage(iSynStartIdx, iSynCount, arySynapseVin);

	fltVahp = CalculateAHPVoltageFloat(fltVahp, iSpiked, iNeuronType);

	float fltVext = aryIin * aryNT_IextConv[iNeuronType];

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
		iSpiked = 1;
	else
		iSpiked = 0;

	//Start the refractory period
	if(iPrevSpiked)
		iRefrCount = aryNT_RefrCount[iNeuronType];

	//set the delay bits and shift over
	iDelayCount = (iDelayCount << 1) | (((unsigned int) iSpiked) << DELAY_ADD_SPIKE);
	iData = (iDelayCount << DELAY_COUNT_SHIFT) | (iSpiked << SPIKED_SHIFT) | iRefCount;

	//Fill data back into the global variables.
	aryVm[iActiveIdx] = fltVm;
	aryVahp[gid] = fltVahp;
	aryPostSynWeightDecay[gid] = 0;
	aryData[gid] = iRefrCount;
	aryTestOut[gid] = fltRandom;
}



