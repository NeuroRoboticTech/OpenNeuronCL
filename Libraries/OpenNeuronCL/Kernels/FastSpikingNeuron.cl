#include "include/KernelRandomNumbers.h"

__constant float aryNT_Decrement[2] = {0.039210598915815353f, 0.039210598915815353f};

float CalculateAHPVoltageFloat(float fltVahp, uchar iSpiked)
{
	//Decrement the previous Vahp and THEN add more for a new spike if needed.

	//If there is current left, but decrement is being rounded off to 0 then
	//we need to keep decrementing by 1 until we get rid of all of the leftover current.
	if(fabs(fltVahp) > 0)
		fltVahp -= (fltVahp * 0.064493000507354736);
	else
		fltVahp = 0;

	//If the pre-synaptic neuron spiked then add the synaptic weight to the current value.
	if(iSpiked)
		fltVahp += -2.4271199703216553;

	return fltVahp;
}


__kernel void FastSpikingNeuron(unsigned int iTimeSlice, unsigned char iActiveArray, 
								unsigned int iSeed, __global float *aryVm, 
								__global float *aryVahp, __global float *aryIin,
								__global int *aryRefrCount, __global float *aryTestOut)
{
	int gid = get_global_id(0);
	size_t gsize = get_global_size(0);

	int iActiveIdx = (gsize*iActiveArray)+gid;
	int iInactiveIdx = (gsize*!iActiveArray) + gid;

	float fltVm = aryVm[iInactiveIdx];
	float fltVahp = aryVahp[gid];
	float fltIin = aryIin[gid];
	int iRefrCount = aryRefrCount[gid];
	unsigned char iSpiked = 0; //aryRefrCount[gid];
	unsigned char iPreSpiked = 0; //iSpiked;

	fltVahp = CalculateAHPVoltageFloat(fltVahp, iSpiked);

	fltVm += (fltVahp + fltIin - (fltVm*aryNT_Decrement[0])); //0.039210598915815353f));

	//For now lets just do one spike when it starts.
	//If we are in the refractory period then do not allow another spike to occur period.
	//If not then a spike will occur if the Vm goes above threshold.
	if(iRefrCount > 0)
	{
		iRefrCount--;
		iSpiked = 0;
	}
	else if(fltVm > 20.0f)
		iSpiked = 1;
	else
		iSpiked = 0;

	//Start the refractory period
	if(iPreSpiked)
		iRefrCount = 10;

	float fltRandom = RandomFloat(gid, iTimeSlice, iSeed, 10, 15);

	aryVm[iActiveIdx] = fltVm;
	aryVahp[gid] = fltVahp;
	aryRefrCount[gid] = iRefrCount;
	//arySpiked[gid] = iSpiked;
	aryTestOut[gid] = fltRandom;
}



