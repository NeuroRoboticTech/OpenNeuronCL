#pragma once

namespace OpenNeuronCL
{

	class OpenNeuronCLBase
	{
		protected:
			unsigned long m_lID;

		public:
			OpenNeuronCLBase(void);
			virtual ~OpenNeuronCLBase(void);

	};

}