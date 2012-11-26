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

//Simulation Objects
namespace OpenNeuronCL
{
	class TestOpenCL;
}

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


#include "TestOpenCL.h"

using namespace OpenNeuronCL;

#endif // __OPEN_NEURON_CL_LIB_DLL_H__
