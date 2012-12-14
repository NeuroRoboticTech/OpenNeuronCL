
struct __attribute__ ((packed)) NeuronDataPacked 
{
    float Vm[2];
    float Vahp;
	float Iin;
    int RefrCountSpiked;
};

__kernel void BufferTestWithStruct(__global struct NeuronDataPacked *aryNeuronsGlobal, __local struct NeuronDataPacked *aryNeuronsLocal,
								__global float *aryVmOut, __global float *aryTestOut)
{
	int gid = get_global_id(0);

	aryNeuronsLocal[gid] = aryNeuronsGlobal[gid];

	aryVmOut[gid] = gid; //aryNeuronsLocal[gid].Vm[0];  // aryVmIn[gid];
	aryTestOut[gid] = aryNeuronsLocal[gid].Vm[1];
}



