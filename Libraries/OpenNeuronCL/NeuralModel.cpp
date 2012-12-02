#include "StdAfx.h"
#include "NeuralModel.h"

namespace OpenNeuronCL
{

NeuralModel::NeuralModel(shared_ptr<INervousSystem> lpNS, double dblDT) : m_lpNervousSystem(lpNS), INeuralModel(lpNS, dblDT)
{
	TimeStep(dblDT);
}


NeuralModel::~NeuralModel(void)
{		
	int i = 5;
}

void NeuralModel::TimeStep(double dblDt)
{
	if(dblDt <= 0)
		BOOST_THROW_EXCEPTION(InvalidParamValueException("NeuralModel", "TimeStep", boost::lexical_cast<std::string>(dblDt), "must be greater than zero."));

	m_dblTimeStep = dblDt;
}


}