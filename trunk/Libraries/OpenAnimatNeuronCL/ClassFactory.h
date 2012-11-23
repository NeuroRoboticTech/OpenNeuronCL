/**
\file	ClassFactory.h

\brief	Declares the class factory class.
**/

#pragma once

namespace OpenNeuronCL
{

	class ClassFactory : public IStdClassFactory   
	{
	public:
		ClassFactory();
		virtual ~ClassFactory();
		 
		/**
		\brief	Creates a neuron.
		
		\author	dcofer
		\date	4/1/2011
		
		\param	strType	   	Type of the class to create. 
		\param	bThrowError	true to throw error if type is not found. 
		
		\return	Pointer to the created object.
		**/
		virtual Behavior::Neuron *CreateNeuron(string strType, BOOL bThrowError = TRUE);

		/**
		\brief	Creates a neuron type.
		
		\author	dcofer
		\date	4/1/2011
		
		\param	strType	   	Type of the class to create. 
		\param	bThrowError	true to throw error if type is not found. 
		
		\return	Pointer to the created object.
		**/
		virtual Behavior::NeuronType *CreateNeuronType(string strType, BOOL bThrowError = TRUE);

		/**
		\brief	Creates a synapse.
		
		\author	dcofer
		\date	4/1/2011
		
		\param	strType	   	Type of the class to create. 
		\param	bThrowError	true to throw error if type is not found. 
		
		\return	Pointer to the created object.
		**/
		virtual Behavior::Synapse *CreateSynapse(string strType, BOOL bThrowError = TRUE);

		/**
		\brief	Creates a synapse type.
		
		\author	dcofer
		\date	4/1/2011
		
		\param	strType	   	Type of the class to create. 
		\param	bThrowError	true to throw error if type is not found. 
		
		\return	Pointer to the created object.
		**/
		virtual Behavior::SynapseType *CreateSynapseType(string strType, BOOL bThrowError = TRUE);

		/**
		\brief	Creates an external stimulus.
		
		\author	dcofer
		\date	4/1/2011
		
		\param	strType	   	Type of the class to create. 
		\param	bThrowError	true to throw error if type is not found. 
		
		\return	Pointer to the created object.
		**/
		virtual ExternalStimulus *CreateExternalStimulus(string strType, BOOL bThrowError = TRUE);

		/**
		\brief	Creates a neural module.
		
		\author	dcofer
		\date	4/1/2011
		
		\param	strType	   	Type of the class to create. 
		\param	bThrowError	true to throw error if type is not found. 
		
		\return	Pointer to the created object.
		**/
		virtual NeuralModule *CreateNeuralModule(string strType, BOOL bThrowError = TRUE);

		virtual CStdSerialize *CreateObject(string strClassType, string strObjectType, BOOL bThrowError);
	};

}				//OpenNeuronCL
