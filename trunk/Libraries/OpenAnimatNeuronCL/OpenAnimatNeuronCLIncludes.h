#ifndef __EBRAIN_SIM_INCLUDES_H__
#define __EBRAIN_SIM_INCLUDES_H__

#define OPENNEURONCL_PORT __declspec( dllexport )

#include "AnimatSim.h"
#include "OpenNeuronCLConstants.h"

#define Nl_Err_lSynapseToAddNull -3013
#define Nl_Err_strSynapseToAddNull "Synapse to be added to the Neuron is null."

#define Nl_Err_lInvalidSynapseIndex -3014
#define Nl_Err_strInvalidSynapseIndex "An invalid Synapse index value was specified."

#define Nl_Err_lInvalidSizeSpec -3006
#define Nl_Err_strInvalidSizeSpec "Invalid Size specification."

#define Nl_Err_lNeuronToSetNull -3007
#define Nl_Err_strNeuronToSetNull "The neuron to set was null."

#define Nl_Err_lSimulationNotDefined -3024
#define Nl_Err_strSimulationNotDefined "Simulation has not been defined."

//Simulation Objects
namespace OpenNeuronCL
{
	class ClassFactory;
	class MemorySegment;
	class MemoryWord;
	class MemoryLink;
	class MemoryBlock;

	namespace Behavior
	{

		class eBrainNeuralModule;
	
		class Neuron;
		class Synapse;
		class NeuralType;
		class NeuronType;
		class SynapseType;

		class NeuronCounts;
		class NeuralTypeCountRef;
		class SynapseCountRef;
		class SynapseCounts;
		class NPE_ClusterNode;
		class ProcessList;

		namespace IGF
		{
			class IGF_NeuronType;
			class SpikingNeuron;
			class FastSpikingNeuron;
			class SpikingNT;
			class SpikingST;
			class FastSpikingST;
			class SpikingSynapse;
			class FastSpikingSynapse;
		}
	}

	namespace Interface
	{
		class eBrain;
		class MemoryLayout;
		class NPU;
		class NPE;

		namespace BoardTypes
		{
			class eBrain_S3S200P256_1;
		}

		namespace NpeTypes
		{
			class NPE_S3S200P256_18B;
			class NPE_S3S200P256_32B;
		}
	}
}

using namespace OpenNeuronCL;
using namespace OpenNeuronCL::Behavior;
using namespace OpenNeuronCL::Interface;

#endif // __FAST_NET_INCLUDES_H__
