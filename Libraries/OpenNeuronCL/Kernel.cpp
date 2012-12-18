#include "StdAfx.h"
#include "Kernel.h"

namespace OpenNeuronCL
{

	Kernel::Kernel(INervousSystem *lpNS, INeuralModel *lpModel, string strKernelSource, string strKernelName) : 
					IKernel(lpNS, lpModel, strKernelSource, strKernelName)
	{
		m_lpNervousSystem = dynamic_cast<NervousSystem *>(lpNS);
		m_lpModel = dynamic_cast<NeuralModel *>(lpModel);

		if(!m_lpNervousSystem)
			BOOST_THROW_EXCEPTION(BasePtrNotInitException("Kernel", "NervousSystem"));

		if(!m_lpModel)
			BOOST_THROW_EXCEPTION(BasePtrNotInitException("Kernel", "NeuralModel"));

		if(!strKernelSource.length())
			BOOST_THROW_EXCEPTION(KernelSourceMissingException());

		if(!strKernelName.length())
			BOOST_THROW_EXCEPTION(KernelSourceMissingException());
		
		m_arySourceFiles.push_back(strKernelSource);
		m_strKernelName = strKernelName;
	}


	Kernel::~Kernel(void)
	{
		int i = 5;
	}

	void Kernel::Build()
	{
		// Create kernel.
		//TODO: For now only using a single source file. Change this to be able to handle multiple files. 
		std::ifstream programFile(m_arySourceFiles[0]);
		std::string programString(std::istreambuf_iterator<char>(programFile),
			(std::istreambuf_iterator<char>()));
		cl::Program::Sources source(1, std::make_pair(programString.c_str(),
			programString.length()+1));
		m_Program = shared_ptr<cl::Program>(new cl::Program(m_lpNervousSystem->ActiveContext(), source));

		//std::cout << "Program kernel: " << std::endl << programString << std::endl;

		try
		{
			m_Program->build(m_lpNervousSystem->ActiveDevices(m_lpModel));
		}
		catch(cl::Error e)
		{
			std::cout << e.what() << ": Error code " << e.err() << std::endl;   
			string buildlog;
			m_Program->getBuildInfo( m_lpNervousSystem->ActiveDevices(m_lpModel)[0], (cl_program_build_info)CL_PROGRAM_BUILD_LOG, &buildlog );
			std::cout << "Error: " << buildlog << std::endl;   
			throw e;
		}

		m_Kernel = shared_ptr<cl::Kernel>(new cl::Kernel(CLProgram(), m_strKernelName.c_str()));
	}

	void Kernel::Initialize()
	{
		Build();
	}

	void Kernel::SetArg(int iIdx, cl::Buffer &buf)
	{
		m_Kernel->setArg(iIdx, buf);
	}

	void Kernel::SetArg(int iIdx, unsigned char iVal)
	{
		m_Kernel->setArg(iIdx, iVal);
	}
	
}