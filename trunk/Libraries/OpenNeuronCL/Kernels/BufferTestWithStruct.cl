__kernel void FastSpikingNeuron(__global float *aryVmIn, __global float *aryVahp, __global float *aryIin,
								__global uchar *aryRefrCount, __global uchar *arySpiked,
								__global float *aryVmOut, __global float *aryTestOut)
{
	int gid = get_global_id(0);
	float fltVm = aryVmIn[gid];
	float fltVahp = aryVahp[gid];
	float fltIin = aryIin[gid];
	uchar iRefrCount = aryRefrCount[gid];
	uchar iSpiked = arySpiked[gid];
	uchar iPreSpiked = iSpiked;

	fltVahp = CalculateAHPVoltageFloat(fltVahp, iSpiked);

	fltVm += (fltVahp + fltIin - (fltVm*0.039210598915815353f));

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

	aryVmOut[gid] = fltVm;
	aryVahp[gid] = fltVahp;
	aryRefrCount[gid] = iRefrCount;
	arySpiked[gid] = iSpiked;
	aryTestOut[gid] = iSpiked;
}



