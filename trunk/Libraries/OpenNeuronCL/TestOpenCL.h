#pragma once

namespace OpenNeuronCL
{

class OPENNEURONCL_PORT TestOpenCL
{
protected:
	void RunFastSpikingNeurons();
	void RunIDCheck();

public:
	TestOpenCL(void);
	virtual ~TestOpenCL(void);

	void Run();
};
 
}
