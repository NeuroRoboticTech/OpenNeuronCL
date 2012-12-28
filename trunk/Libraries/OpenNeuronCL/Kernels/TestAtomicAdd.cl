
inline void AtomicAdd(volatile __global float *source, const float operand) {
    union {
        unsigned int intVal;
        float floatVal;
    } newVal;
    union {
        unsigned int intVal;
        float floatVal;
    } prevVal;
    do {
        prevVal.floatVal = *source;
        newVal.floatVal = prevVal.floatVal + operand;
    } while (atomic_cmpxchg((volatile __global unsigned int *)source, prevVal.intVal, newVal.intVal) != prevVal.intVal);
}

__kernel void TestAtomicAdd(__global float *arySynapseI, __global unsigned int *arySynapsePostNeuronIdx, __global float *aryNeuronIin)
{
	unsigned int gid = get_global_id(0);

	//Synaptic current
	float fltIs = arySynapseI[gid];
	//Post-synaptic neuron for this synapse
	unsigned int iPostNeuronIdx = arySynapsePostNeuronIdx[gid];

	//aryNeuronIin[iPostNeuronIdx] = gid;
	AtomicAdd((aryNeuronIin+iPostNeuronIdx), fltIs);
}



