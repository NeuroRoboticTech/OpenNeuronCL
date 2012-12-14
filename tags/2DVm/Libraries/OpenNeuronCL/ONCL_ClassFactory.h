#pragma once

namespace OpenNeuronCL
{

class OPENNEURONCL_PORT ClassFactory {
    public:
		static shared_ptr<INervousSystem> GetNervousSystemInstance(string strType);
		static shared_ptr<INeuralModel> GetNeuralModelInstance(string strType, INervousSystem *lpNS, double dblDT);
		static shared_ptr<IKernel> GetKernelInstance(string strType, INervousSystem *lpNS, INeuralModel *lpModel, 
													 string strKernelSource, string strKernelName);
		//static void Test();

        typedef boost::function< IOpenNeuronCLBase*() > IOpenNeuronBase_fact;
        typedef boost::function< shared_ptr<INervousSystem>() > INervousSystem_fact;
        typedef boost::function< shared_ptr<INeuralModel>(INervousSystem *lpNS, double dblDT) > INeuralModel_fact;
        typedef boost::function< shared_ptr<IKernel>(INervousSystem *lpNS, INeuralModel *lpModel, 
													 string strKernelSource, string strKernelName) > IKernel_fact;

    private:
        ClassFactory(); 

        std::map<std::string, INervousSystem_fact>   NervousSystemMap;
        std::map<std::string, INeuralModel_fact>   NeuralModelMap;
        std::map<std::string, IKernel_fact>   KernelMap;
    };

}