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

		class BasePtrNotInitException : public OpenNeuronCLException
		{ 
		public: 
		  BasePtrNotInitException(string strClassName, string strPointerName) 
			: OpenNeuronCLException("A base pointer for " + strClassName + "::" + strPointerName + " was not initialized when object was created.") {} 
		}; 

		class KernelSourceMissingException : public OpenNeuronCLException
		{ 
		public: 
		  KernelSourceMissingException() 
			: OpenNeuronCLException("Attempted to create a kernel without specifying a source filename, or kernel name.") {} 
		}; 

		class MethodNotImplementedException : public OpenNeuronCLException
		{ 
		public: 
		  MethodNotImplementedException(string strClassName, string strMethodName) 
			: OpenNeuronCLException("Method " + strClassName + "::" + strMethodName + " has not been implemented yet.") {} 
		}; 

		class QueueForDeviceNotFoundException : public OpenNeuronCLException
		{ 
		public: 
		  QueueForDeviceNotFoundException(string strVendor, string strName, string strDriverVersion) 
			: OpenNeuronCLException("No queue was found for the device '" + strVendor + " " + strName + " Version: " + strDriverVersion) {} 
		}; 

	}
}