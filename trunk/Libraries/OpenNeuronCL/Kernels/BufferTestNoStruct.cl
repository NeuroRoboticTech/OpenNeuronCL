__kernel void BufferTestNoStruct(__global float *aryVmIn, __global float *aryVahp, __global float *aryIin, __global int *aryRefrCount,
								 __local float *aryLVmIn, __local float *aryLVahp, __local float *aryLIin, __local int *aryLRefrCount,
								 __global float *aryVmOut, __global float *aryTestOut)
{
	int gid = get_global_id(0);

	aryLVmIn[gid] = aryVmIn[gid];
	aryLVahp[gid] = aryVahp[gid];
	aryLIin[gid] = aryIin[gid];
	aryLRefrCount[gid] = aryRefrCount[gid];

	aryVmOut[gid] = aryLVmIn[gid]+gid;  // aryVmIn[gid];
	aryVahp[gid] = gid; //aryLVahp[gid]; //+gid;
	aryRefrCount[gid] = gid; //aryLRefrCount[gid]; //+gid;
	aryTestOut[gid] = aryLIin[gid]+gid;
}



