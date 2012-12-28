
__kernel void TestAddSynapsePerNeuron(__global float *arySynapseI, __global unsigned int *arySynapseStartIdx, 
									  __global unsigned int *arySynapseCount, __global float *aryNeuronIin, unsigned int iUnused)
{
	unsigned int gid = get_global_id(0);

	//Index of where to start looping in the synapse list for this neuron
	unsigned int iSynapseStartIdx = arySynapseStartIdx[gid];

	//Number of synapses coming into this neuron
	unsigned int iSynapseCount = arySynapseCount[gid];

	unsigned int iFinalIdx = iSynapseStartIdx + iSynapseCount;

	float fltSum = 0;
	for(unsigned int iIdx=iSynapseStartIdx; iIdx<iFinalIdx; iIdx++)
		fltSum += arySynapseI[iIdx];

	aryNeuronIin[gid] = fltSum;
}


__kernel void TestAddSynapsePerNeuronStrided(__global float *arySynapseI, __global unsigned int *arySynapseStartIdx, 
									         __global unsigned int *arySynapseCount, __global float *aryNeuronIin, unsigned int iStride)
{
	unsigned int gid = get_global_id(0);

	//Index of where to start looping in the synapse list for this neuron
	unsigned int iSynapseStartIdx = arySynapseStartIdx[gid];

	//Number of synapses coming into this neuron
	unsigned int iSynapseCount = arySynapseCount[gid];

	unsigned int iFinalIdx = iSynapseStartIdx + iSynapseCount;

	float fltSum = 0;
	for(unsigned int iIdx=iSynapseStartIdx; iIdx<iFinalIdx; iIdx++)
		fltSum += arySynapseI[iSynapseStartIdx + (iIdx*iStride)];

	aryNeuronIin[gid] = fltSum;
}


