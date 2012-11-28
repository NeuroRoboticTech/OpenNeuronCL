#ifndef __OPEN_NEURAL_CL_SIM_INCLUDES_H__
#define __OPEN_NEURAL_CL_SIM_INCLUDES_H__

#define OPENNEURONCL_PORT __declspec( dllexport )

#include "OpenNeuronCLConstants.h"

#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/algorithm/string.hpp>

//Simulation Objects
namespace OpenNeuronCL
{
	class INeuralModel;
	class ONCL_ClassFactory;

	namespace NeuralModels
	{
		class FastSpikingNeuralModel;
	}

	namespace Exceptions
	{
		class InvalidNeuronModelTypeException;
	}
}

#include "ONCL_Exceptions.h"
#include "INeuralModel.h"

using namespace OpenNeuronCL;
using namespace OpenNeuronCL::NeuralModels;
using namespace OpenNeuronCL::Exceptions;

#endif // __OPEN_NEURAL_CL_SIM_INCLUDES_H__
