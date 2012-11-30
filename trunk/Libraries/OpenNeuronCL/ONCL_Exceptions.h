#pragma once

#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>

namespace OpenNeuronCL
{
	namespace Exceptions
	{

		class OpenNeuronCLException : public std::exception 
		{ 
		public: 
		  OpenNeuronCLException(string strErrorText) 
			: what_(strErrorText) 
		  { 
		  } 

		  virtual const char *what() const throw() 
		  { 
			return what_.c_str(); 
		  } 

		protected: 
		  std::string what_; 
		}; 

		class InvalidNeuronModelTypeException : public OpenNeuronCLException
		{ 
		public: 
		  InvalidNeuronModelTypeException(string strTypeName, string strTypeValue) 
			: OpenNeuronCLException("Invalid neuron model was specified. " + strTypeName + ": " + strTypeValue) {} 
		}; 

		class InvalidParamValueException : public OpenNeuronCLException
		{ 
		public: 
		  InvalidParamValueException(string strClassName, string strParamName, string strParamValue, string strParamRange) 
			: OpenNeuronCLException("Invalid parameter value set for " + strClassName + "::" + strParamName + ". Value: " + strParamValue + ", Valid range: " + strParamRange) {} 
		}; 

	}
}