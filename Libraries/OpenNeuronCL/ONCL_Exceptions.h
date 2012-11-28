#pragma once

#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>

namespace OpenNeuronCL
{
	namespace Exceptions
	{

		class InvalidNeuronModelTypeException : public std::exception 
		{ 
		public: 
		  InvalidNeuronModelTypeException(string strTypeName, string strTypeValue) 
			: what_("Invalid neuron model was specified. " + strTypeName + ": " + strTypeValue) 
		  { 
		  } 

		  virtual const char *what() const throw() 
		  { 
			return what_.c_str(); 
		  } 

		private: 
		  std::string what_; 
		}; 
	}
}