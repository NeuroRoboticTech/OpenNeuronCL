#pragma once

namespace OpenNeuronCL
{

	class OpenNeuronCLBase : public IOpenNeuronCLBase
	{
		protected:
			string m_strID;

		public:
			OpenNeuronCLBase(void);
			virtual ~OpenNeuronCLBase(void);

			virtual string ID() {return m_strID;};
	};

}