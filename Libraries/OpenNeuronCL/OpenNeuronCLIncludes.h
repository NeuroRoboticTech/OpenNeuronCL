#ifndef __OPEN_NEURAL_CL_SIM_INCLUDES_H__
#define __OPEN_NEURAL_CL_SIM_INCLUDES_H__

#define OPENNEURONCL_PORT __declspec( dllexport )

#pragma warning(disable: 4018 4244 4290 4786 4251 4275 4267 4311 4312 4800 4003 4482 4996 4251)

#define __CL_ENABLE_EXCEPTIONS
#include <ncl.hpp>

#include "OpenNeuronCLConstants.h"

#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/bind.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/lexical_cast.hpp> 
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/foreach.hpp>

//Simulation Objects
namespace OpenNeuronCL
{
	class IOpenNeuronCLBase;
	class ISimulationObject;
	class INervousSystem;
	class INeuralModel;
	class IKernel;
	class ClassFactory;
	class OpenNeuronCLBase;
	class NervousSystem;
	class NeuralModel;
	class Kernel;

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
#include "IOpenNeuronCLBase.h"
#include "ISimulationObject.h"
#include "INervousSystem.h"
#include "INeuralModel.h"
#include "IKernel.h"
#include "OpenNeuronCLBase.h"
#include "NervousSystem.h"
#include "NeuralModel.h"
#include "ONCL_ClassFactory.h"

using namespace OpenNeuronCL;
using namespace OpenNeuronCL::NeuralModels;
using namespace OpenNeuronCL::Exceptions;

#endif // __OPEN_NEURAL_CL_SIM_INCLUDES_H__
