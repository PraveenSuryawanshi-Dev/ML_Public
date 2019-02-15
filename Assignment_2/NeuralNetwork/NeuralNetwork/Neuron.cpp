#include "Neuron.hpp"

#define RANDOM(min,max) { min + (int) (rand() / (double) (RAND_MAX + 1) * (max - min + 1))}

double NeuralNetwork::Neuron::_m_totatl_error = 0.0;

NeuralNetwork::Neuron::Neuron(ACTIVATION_TYPE acType, unsigned int iTotalNeuronNextLayer)
{
	_m_activationType = acType;

	_m_iTotalNeuronNextLayer = iTotalNeuronNextLayer;

	_m_output_sum = 0.0;

	_m_error = 0.0;
	
}

void NeuralNetwork::Neuron::Build()
{
	for (size_t i = 0; i < _m_iTotalNeuronNextLayer; i++)
	{
		_m_Weights.push_back(RANDOM(0.0, 1.0));
	}
}
void NeuralNetwork::Neuron::LatchInput(double data)
{
	_m_output_sum = data;
}


void NeuralNetwork::Neuron::FeedForward(Layer *previousLayer, ACTIVATION_TYPE activationType)
{

	for (size_t i = 0; i < previousLayer->Size(); i++)
	{
		Neuron *currentNeuron = previousLayer->GetNeuron(i);

		double output = 0.0;

		for (size_t i = 0; i < currentNeuron->_m_Weights.size(); i++)
		{
			output += currentNeuron->_m_output_sum * currentNeuron->_m_Weights[i];
		}

		_m_output_sum = output;

		double activationFunctionResult = 0.0;

		switch (activationType)
		{
		case NONE:
			break;

		case RELU:
			activationFunctionResult = Activation::Relu(_m_output_sum);
			break;

		case SIGMOID:
			activationFunctionResult = Activation::Sigmoid(_m_output_sum);
			break;

		case HYPERBOLIC_TANGENT:
			activationFunctionResult = Activation::HyperbolicTangent(_m_output_sum);
			break;

		case LINEAR:
			activationFunctionResult = Activation::Linear(_m_output_sum);
			break;

		default:
			break;
		}

		_m_output_sum = activationFunctionResult;

	}
}

void NeuralNetwork::Neuron::BackPropagation(Layer * previousLayer, double expected)
{
	_m_error = (sqrt(expected - _m_output_sum)) * (1.0/2.0);

	_m_totatl_error += _m_error;

}



NeuralNetwork::Neuron::~Neuron()
{
}
