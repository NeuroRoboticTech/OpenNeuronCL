#pragma once

namespace OpenNeuronCL
{

class NeuralModel : public OpenNeuronCLBase, public INeuralModel
{
protected:
	//cl::Context context(devices);

public:
	NeuralModel(void);
	virtual ~NeuralModel(void);
};

}
