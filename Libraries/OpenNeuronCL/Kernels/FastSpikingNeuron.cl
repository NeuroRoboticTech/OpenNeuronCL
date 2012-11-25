__kernel void FastSpikingNeuron(__global float *aryVmIn, __global float *aryVahp, 
								__global uchar *aryRefrCount, __global uchar *arySpiked,
								__global float *aryVmOut, __global float *aryTestOut)
{
	int gid = get_global_id(0);
	float fltVm = aryVmIn[gid];
	float fltVahp = aryVahp[gid];
	uchar iRefrCount = aryRefrCount[gid];
	uchar iSpiked = arySpiked[gid];

	aryVmOut[gid] = fltVm * 2.0f;
	aryTestOut[gid] = iSpiked;
}



