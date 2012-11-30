#ifndef __OPEN_NEURON_CL_LIB_DLL_H__
#define __OPEN_NEURON_CL_LIB_DLL_H__

#ifndef _OPEN_NEURON_CL_LIB_DLL_NOFORCELIBS
	#ifdef _DEBUG
		#pragma comment(lib, "OpenNeuronCL_vc10D.lib")
	#else
		#pragma comment(lib, "OpenNeuronCL_vc10.lib")
	#endif
#endif          // _OPEN_NEURON_CL_LIB_DLL_NOFORCELIBS

#define OPENNEURONCL_PORT __declspec( dllimport )

#pragma warning(disable: 4018 4244 4290 4786 4251 4275 4267 4311 4312 4800 4003 4482 4996 4251)

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <conio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <io.h>
#include <direct.h>

#include <exception>
#include <string>
#include <iosfwd>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <deque>
#include <stack>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <math.h>
#include <memory.h>
#include <algorithm>
#include <tchar.h> 
#include <string.h>
#include <wtypes.h>
#include <vfw.h>
using namespace std;

#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/bind.hpp>

//Simulation Objects
namespace OpenNeuronCL
{
	class IOpenNeuronCLBase;
	class INervousSystem;
	class INeuralModel;
	class ClassFactory;

	namespace Exceptions
	{
		class InvalidNeuronModelTypeException;
	}
}

using namespace OpenNeuronCL;
using namespace OpenNeuronCL::Exceptions;

#include "ONCL_Exceptions.h"
#include "IOpenNeuronCLBase.h"
#include "INervousSystem.h"
#include "INeuralModel.h"
#include "ONCL_ClassFactory.h"
#include "OpenNeuronCLUtils.h"

#endif // __OPEN_NEURON_CL_LIB_DLL_H__
