/**
\file	ClassFactory.cpp

\brief	Implements the class factory class.
**/

#include "stdafx.h"
#include "ClassFactory.h"

namespace OpenNeuronCL
{

/**
\brief	Default constructor.

\author	dcofer
\date	4/1/2011
**/
ClassFactory::ClassFactory()
{

}

/**
\brief	Destructor.

\author	dcofer
\date	4/1/2011
**/
ClassFactory::~ClassFactory()
{

}

// ************* Neuron Conversion functions ******************************

Behavior::Neuron *ClassFactory::CreateNeuron(string strType, BOOL bThrowError)
{
	/*
	Behavior::Neuron *lpNeuron=NULL;

try
{
	strType = Std_ToUpper(Std_Trim(strType));

	if(strType == "SPIKING")
		lpNeuron = new Behavior::IGF::SpikingNeuron;
	else if(strType == "FASTSPIKING")
		lpNeuron = new Behavior::IGF::FastSpikingNeuron;
	else 
	{
		lpNeuron = NULL;
		if(bThrowError)
			THROW_PARAM_ERROR(Nl_Err_lInvalidNeuronType, Nl_Err_strInvalidNeuronType, "Neuron", strType);
	}

	return lpNeuron;
}
catch(CStdErrorInfo oError)
{
	if(lpNeuron) delete lpNeuron;
	RELAY_ERROR(oError); 
	return NULL;
}
catch(...)
{
	if(lpNeuron) delete lpNeuron;
	THROW_ERROR(Std_Err_lUnspecifiedError, Std_Err_strUnspecifiedError);
	return NULL;
}*/
	return NULL;
}


// ************* Neuron Conversion functions ******************************

// ************* Neuron Type Conversion functions ******************************

Behavior::NeuronType *ClassFactory::CreateNeuronType(string strType, BOOL bThrowError)
{
	/*
	Behavior::NeuronType *lpType=NULL;

try
{
	strType = Std_ToUpper(Std_Trim(strType));

	if(strType == "SPIKING")
		lpType = new Behavior::IGF::SpikingNT;
	else if(strType == "FASTSPIKING")
		lpType = new Behavior::IGF::FastSpikingNT;
	else 
	{
		lpType = NULL;
		if(bThrowError)
			THROW_PARAM_ERROR(Nl_Err_lInvalidNeuronType, Nl_Err_strInvalidNeuronType, "Neuron Type", strType);
	}

	return lpType;
}
catch(CStdErrorInfo oError)
{
	if(lpType) delete lpType;
	RELAY_ERROR(oError); 
	return NULL;
}
catch(...)
{
	if(lpType) delete lpType;
	THROW_ERROR(Std_Err_lUnspecifiedError, Std_Err_strUnspecifiedError);
	return NULL;
}*/
	return NULL;
}


// ************* Neuron Type Conversion functions ******************************


// ************* Synapse Conversion functions ******************************

Behavior::Synapse *ClassFactory::CreateSynapse(string strType, BOOL bThrowError)
{/*
	Behavior::Synapse *lpSynapse=NULL;

try
{
	strType = Std_ToUpper(Std_Trim(strType));

	if(strType == "SPIKING")
		lpSynapse = new Behavior::IGF::SpikingSynapse;
	else if(strType == "FASTSPIKING")
		lpSynapse = new Behavior::IGF::FastSpikingSynapse;
	else
	{
		lpSynapse = NULL;
		if(bThrowError)
			THROW_PARAM_ERROR(Nl_Err_lInvalidSynapseType, Nl_Err_strInvalidSynapseType, "Synapse", strType);
	}

		return lpSynapse;
}
catch(CStdErrorInfo oError)
{
	if(lpSynapse) delete lpSynapse;
	RELAY_ERROR(oError); 
	return NULL;
}
catch(...)
{
	if(lpSynapse) delete lpSynapse;
	THROW_ERROR(Std_Err_lUnspecifiedError, Std_Err_strUnspecifiedError);
	return NULL;
}*/
	return NULL;
}


// ************* Synapse Conversion functions ******************************


// ************* Synapse Type Conversion functions ******************************

Behavior::SynapseType *ClassFactory::CreateSynapseType(string strType, BOOL bThrowError)
{/*
	Behavior::SynapseType *lpType=NULL;

try
{
	strType = Std_ToUpper(Std_Trim(strType));

	if(strType == "SPIKING")
		lpType = new Behavior::IGF::SpikingST;
	else if(strType == "FASTSPIKING")
		lpType = new Behavior::IGF::FastSpikingST;
	else 
	{
		lpType = NULL;
		if(bThrowError)
			THROW_PARAM_ERROR(Nl_Err_lInvalidSynapseType, Nl_Err_strInvalidSynapseType, "Synapse Type", strType);
	}

	return lpType;
}
catch(CStdErrorInfo oError)
{
	if(lpType) delete lpType;
	RELAY_ERROR(oError); 
	return NULL;
}
catch(...)
{
	if(lpType) delete lpType;
	THROW_ERROR(Std_Err_lUnspecifiedError, Std_Err_strUnspecifiedError);
	return NULL;
}*/
	return NULL;
}


// ************* Synapse Type Conversion functions ******************************


// ************* External Stimulus Type Conversion functions ******************************


ExternalStimulus *ClassFactory::CreateExternalStimulus(string strType, BOOL bThrowError)
{/*
	ExternalStimulus *lpStimulus=NULL;

try
{
	strType = Std_ToUpper(Std_Trim(strType));

	if(strType == "CURRENT")
		lpStimulus = new AnimatSim::ExternalStimuli::CurrentStimulus;
	else
	{
		lpStimulus = NULL;
		if(bThrowError)
			THROW_PARAM_ERROR(Al_Err_lInvalidExternalStimulusType, Al_Err_strInvalidExternalStimulusType, "ExternalStimulusType", strType);
	}

	return lpStimulus;
}
catch(CStdErrorInfo oError)
{
	if(lpStimulus) delete lpStimulus;
	RELAY_ERROR(oError); 
	return NULL;
}
catch(...)
{
	if(lpStimulus) delete lpStimulus;
	THROW_ERROR(Std_Err_lUnspecifiedError, Std_Err_strUnspecifiedError);
	return NULL;
}*/
	return NULL;
}

// ************* External Stimulus Type Conversion functions ******************************


// ************* External Neural Module Conversion functions ******************************

NeuralModule *ClassFactory::CreateNeuralModule(string strType, BOOL bThrowError)
{/*
	NeuralModule *lpModule=NULL;

try
{
	strType = Std_ToUpper(Std_Trim(strType));

	if(strType == "EBRAINNEURALMODULE")
		lpModule = new Behavior::eBrainNeuralModule;
	else
	{
		lpModule = NULL;
		if(bThrowError)
			THROW_PARAM_ERROR(Al_Err_lInvalidNeuralModuleType, Al_Err_strInvalidNeuralModuleType, "NeuralModule", strType);
	}

	return lpModule;
}
catch(CStdErrorInfo oError)
{
	if(lpModule) delete lpModule;
	RELAY_ERROR(oError); 
	return NULL;
}
catch(...)
{
	if(lpModule) delete lpModule;
	THROW_ERROR(Std_Err_lUnspecifiedError, Std_Err_strUnspecifiedError);
	return NULL;
}*/
	return NULL;
}

// ************* Neural Module Type Conversion functions ******************************


// ************* IStdClassFactory functions ******************************

CStdSerialize *ClassFactory::CreateObject(string strClassType, string strObjectType, BOOL bThrowError)
{/*
	CStdSerialize *lpObject=NULL;

	strClassType = Std_ToUpper(Std_Trim(strClassType));

	if(strClassType == "EXTERNALSTIMULUS")
		lpObject = CreateExternalStimulus(strObjectType, bThrowError);
	else if(strClassType == "NEURALMODULE")
		lpObject = CreateNeuralModule(strObjectType, bThrowError);
	else if(strClassType == "NEURON")
		lpObject = CreateNeuron(strObjectType, bThrowError);
	else if(strClassType == "NEURONTYPE")
		lpObject = CreateNeuronType(strObjectType, bThrowError);
	else if(strClassType == "SYNAPSE")
		lpObject = CreateSynapse(strObjectType, bThrowError);
	else if(strClassType == "SYNAPSETYPE")
		lpObject = CreateSynapseType(strObjectType, bThrowError);
	else
	{
		lpObject = NULL;
		if(bThrowError)
			THROW_PARAM_ERROR(Std_Err_lInvalidClassType, Std_Err_strInvalidClassType, "ClassType", strClassType);
	}

	return lpObject;*/
	return NULL;
}

// ************* IStdClassFactory functions ******************************

}				//OpenNeuronCL



extern "C" __declspec(dllexport) IStdClassFactory* __cdecl GetStdClassFactory() 
{
	IStdClassFactory *lpFactory = new ClassFactory;
	return lpFactory;
}
