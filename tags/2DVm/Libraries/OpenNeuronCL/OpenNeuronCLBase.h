#pragma once

namespace OpenNeuronCL
{

	class OpenNeuronCLBase
	{
		protected:
			unsigned int m_iID;

		public:
			OpenNeuronCLBase(void);
			virtual ~OpenNeuronCLBase(void);

	};

}