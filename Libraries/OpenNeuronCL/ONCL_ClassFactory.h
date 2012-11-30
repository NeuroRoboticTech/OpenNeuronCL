#pragma once

namespace OpenNeuronCL
{

class OPENNEURONCL_PORT ClassFactory {
    public:
		static boost::shared_ptr<IOpenNeuronCLBase> GetInstance(string strType)
		{
			ClassFactory factory;
			boost::shared_ptr<IOpenNeuronCLBase> lpBase(factory.NeruonBaseMap[strType]());
			return lpBase;
		}

		static boost::shared_ptr<INeuralModel> GetNeuralModelInstance(string strType)
		{
			ClassFactory factory;
			boost::shared_ptr<INeuralModel> lpModel(factory.NeuralModelMap[strType]());
			return lpModel;
		}

		static boost::shared_ptr<INervousSystem> GetNervousSystemInstance(string strType)
		{
			ClassFactory factory;
			boost::shared_ptr<INervousSystem> lpNervousSys(factory.NervousSystemMap[strType]());
			return lpNervousSys;
		}

        typedef boost::function< IOpenNeuronCLBase*() > IOpenNeuronBase_fact;
        typedef boost::function< INeuralModel*() > INeuralModel_fact;
        typedef boost::function< INervousSystem*() > INervousSystem_fact;

    private:
        ClassFactory(); 

        std::map<std::string, IOpenNeuronBase_fact>   NeruonBaseMap;
        std::map<std::string, INeuralModel_fact>   NeuralModelMap;
        std::map<std::string, INervousSystem_fact>   NervousSystemMap;
    };

}