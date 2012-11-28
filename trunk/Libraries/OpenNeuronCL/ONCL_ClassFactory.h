#pragma once

namespace OpenNeuronCL
{

	class OPENNEURONCL_PORT ONCL_ClassFactory
	{
	public:
		ONCL_ClassFactory(void);
		virtual ~ONCL_ClassFactory(void);

		static boost::shared_ptr<INeuralModel> CreateNeuralModel(string strType, BOOL bThrowError = TRUE);
	};

}