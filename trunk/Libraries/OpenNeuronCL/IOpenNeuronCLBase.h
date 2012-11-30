#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT IOpenNeuronCLBase
	{
	public:

		IOpenNeuronCLBase(void)	{}
		virtual ~IOpenNeuronCLBase(void) {};

		virtual string ID() = 0;

	};

}
