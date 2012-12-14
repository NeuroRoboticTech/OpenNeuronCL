#include "StdAfx.h"
#include "OpenNeuronCLBase.h"
#include "OpenNeuronCLUtils.h"

namespace OpenNeuronCL
{

OpenNeuronCLBase::OpenNeuronCLBase(void) : m_iID(0)
{
	m_iID = GenerateID();
}


OpenNeuronCLBase::~OpenNeuronCLBase(void)
{
}

}