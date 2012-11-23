#ifndef __OPEN_NEURON_CL_LIB_DLL_H__
#define __OPEN_NEURON_CL_LIB_DLL_H__

#ifndef _OPEN_NEURON_CL_LIB_DLL_NOFORCELIBS
	#ifdef _DEBUG
		#pragma comment(lib, "OpenNeuronCL_vc10D.lib")
	#else
		#pragma comment(lib, "OpenNeuronCL_vc10.lib")
	#endif
#endif          // _FAST_NEURAL_NET_LIB_DLL_NOFORCELIBS

#define OPENNEURONCL_PORT __declspec( dllimport )

#include "StdUtils.h"
#include "AnimatLibrary.h"

//Simulation Objects
namespace OpenNeuronCL
{
	class ClassFactory;
}

using namespace OpenNeuronCL;

#endif // __OPEN_NEURON_CL_LIB_DLL_H__
