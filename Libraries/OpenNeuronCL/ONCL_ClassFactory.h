#pragma once

namespace OpenNeuronCL
{

class OPENNEURONCL_PORT ClassFactory {
    public:
		static INeuralModel* GetInstance(string strType)
		{
			ClassFactory factory;
			return factory.map[strType]();
		}

        typedef boost::function< INeuralModel*() > INeuralModel_fact;

    private:
        ClassFactory(); 

        std::map<std::string, INeuralModel_fact>   map;
    };

}