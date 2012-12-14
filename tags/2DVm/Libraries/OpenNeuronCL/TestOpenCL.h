#pragma once

namespace OpenNeuronCL
{

class OPENNEURONCL_PORT TestOpenCL
{
protected:
	void RunFastSpikingNeurons();
	void RunIDCheck();
	void RunBufferTestNoStruct();
	void RunBufferTestWithStruct();

	void SaveOutput(string strFilename, vector<float> &aryData);

public:
	TestOpenCL(void);
	virtual ~TestOpenCL(void);

	void Run();
};
 
}
