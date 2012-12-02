#pragma once

namespace OpenNeuronCL
{

	class NeuralModel : public OpenNeuronCLBase, public INeuralModel, public enable_shared_from_this<INeuralModel>
	{
	protected:
		weak_ptr<INervousSystem> m_lpNervousSystem;
		double m_dblTimeStep;

		//cl::Context context(devices);

	public:
		NeuralModel(shared_ptr<INervousSystem> lpNS, double dblDT);
		virtual ~NeuralModel(void);

		virtual unsigned int ID() {return m_iID;};

		virtual weak_ptr<INervousSystem> NervousSystem() {return m_lpNervousSystem;}; 

		virtual double TimeStep() {return m_dblTimeStep;};
		virtual void TimeStep(double dblDt);

	};

}
