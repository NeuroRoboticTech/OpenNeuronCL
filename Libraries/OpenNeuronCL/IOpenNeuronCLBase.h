#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT IOpenNeuronCLBase
	{
	public:

		IOpenNeuronCLBase(void)	{}
		virtual ~IOpenNeuronCLBase(void) {};

		virtual unsigned long ID() = 0;

	};

}
