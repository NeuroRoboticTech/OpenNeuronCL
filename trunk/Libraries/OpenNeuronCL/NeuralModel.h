#pragma once

namespace OpenNeuronCL
{

	class NeuralModel : public OpenNeuronCLBase, public INeuralModel
	{
	protected:
		double m_dblTimeStep;

		//cl::Context context(devices);

	public:
		NeuralModel(void);
		virtual ~NeuralModel(void);

		virtual unsigned int ID() {return m_iID;};

		virtual double TimeStep() {return m_dblTimeStep;};
		virtual void TimeStep(double dblDt);

	};

}
