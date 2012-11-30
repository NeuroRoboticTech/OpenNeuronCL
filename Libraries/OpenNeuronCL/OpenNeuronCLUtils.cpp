#include "StdAfx.h"
#include "OpenNeuronCLUtils.h"      // OpenNeuronCL

#ifdef WIN32
	#include <Rpc.h>
	#pragma comment(lib, "Rpcrt4.lib")
#else
	#include <uuid/uuid.h>
#endif

namespace OpenNeuronCL
{

	std::string OPENNEURONCL_PORT GenerateGUID()
	{
	#ifdef WIN32
		UUID uuid;
		UuidCreate ( &uuid );

		unsigned char * str;
		UuidToStringA ( &uuid, &str );

		std::string s( ( char* ) str );

		RpcStringFreeA ( &str );
	#else
		uuid_t uuid;
		uuid_generate_random ( uuid );
		char s[37];
		uuid_unparse ( uuid, s );
	#endif
		return s;
	}


}			//OpenNeuronCL