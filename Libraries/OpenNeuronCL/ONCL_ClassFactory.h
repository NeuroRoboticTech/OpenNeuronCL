#pragma once

namespace OpenNeuronCL
{

class OPENNEURONCL_PORT ClassFactory {
    public:
		static shared_ptr<IOpenNeuronCLBase> GetInstance(string strType)
		{
			ClassFactory factory;
			shared_ptr<IOpenNeuronCLBase> lpBase(factory.NeruonBaseMap[strType]());
			return lpBase;
		}

		static shared_ptr<INeuralModel> GetNeuralModelInstance(string strType,shared_ptr<INervousSystem> lpNS, double dblDT)
		{
			ClassFactory factory;
			shared_ptr<INeuralModel> lpModel(factory.NeuralModelMap[strType](lpNS, dblDT));
			return lpModel;
		}

		static shared_ptr<INervousSystem> GetNervousSystemInstance(string strType);
		static void Test();

        typedef boost::function< IOpenNeuronCLBase*() > IOpenNeuronBase_fact;
        typedef boost::function< shared_ptr<INervousSystem>() > INervousSystem_fact;
        typedef boost::function< INeuralModel*(shared_ptr<INervousSystem> lpNS, double dblDT) > INeuralModel_fact;

    private:
        ClassFactory(); 

        std::map<std::string, IOpenNeuronBase_fact>   NeruonBaseMap;
        std::map<std::string, INervousSystem_fact>   NervousSystemMap;
        std::map<std::string, INeuralModel_fact>   NeuralModelMap;
    };

}