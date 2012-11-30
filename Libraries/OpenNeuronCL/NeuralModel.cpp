#include "StdAfx.h"
#include "NeuralModel.h"

namespace OpenNeuronCL
{

NeuralModel::NeuralModel(void) : m_dblTimeStep(0)
{
}


NeuralModel::~NeuralModel(void)
{
}


void NeuralModel::TimeStep(double dblDt)
{
	if(dblDt <= 0)
		BOOST_THROW_EXCEPTION(InvalidParamValueException("NeuralModel", "TimeStep", boost::lexical_cast<std::string>(dblDt), "must be greater than zero."));

	m_dblTimeStep = dblDt;
}


}