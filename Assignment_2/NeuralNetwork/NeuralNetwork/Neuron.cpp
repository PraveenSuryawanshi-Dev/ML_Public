#include "Neuron.hpp"

#define RANDOM(min,max) { min + (int) (rand() / (double) (RAND_MAX + 1) * (max - min + 1))}

NeuralNetwork::Neuron::Neuron(ACTIVATION_TYPE acType, unsigned int iTotalNeuronNextLayer)
{
	_m_activationType = acType;

	_m_iTotalNeuronNextLayer = iTotalNeuronNextLayer;

	_m_output_sum_margin_of_error = 0.0;
		
	_m_delta_sum = 0.0;

	_m_output_sum = 0.0;

	_m_delta_output_sum = 0.0;

	_m_delat_output_sum_derivative = 0.0;
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

		double x = currentNeuron->_m_output_sum;

		double output = 0;

		for (size_t i = 0; i < currentNeuron->_m_Weights.size(); i++)
		{
			output += x * currentNeuron->_m_Weights[i];
		}

		_m_output_sum = output;

		double activationFunctionResult = 0.0;

		double derivative_activationFunctionResult = 0.0;

		switch (activationType)
		{
		case NONE:
			break;

		case RELU:
			activationFunctionResult = Activation::Relu(_m_output_sum);
			derivative_activationFunctionResult = Activation::Relu(activationFunctionResult);
			break;

		case SIGMOID:
			activationFunctionResult = Activation::Sigmoid(_m_output_sum);
			derivative_activationFunctionResult = Activation::Sigmoid(activationFunctionResult);
			break;

		case HYPERBOLIC_TANGENT:
			activationFunctionResult = Activation::HyperbolicTangent(_m_output_sum);
			derivative_activationFunctionResult = Activation::HyperbolicTangent(activationFunctionResult);
			break;

		case LINEAR:
			activationFunctionResult = Activation::Linear(_m_output_sum);
			derivative_activationFunctionResult = Activation::Linear(activationFunctionResult);
			break;

		default:
			break;
		}

		_m_delta_output_sum = activationFunctionResult;

		_m_delat_output_sum_derivative = derivative_activationFunctionResult;
	}
}

void NeuralNetwork::Neuron::BackPropagation(Layer * previousLayer, double expected)
{
	// for (size_t i = 0; i < previousLayer->Size(); i++)
	{
		//Neuron *currentNeuron = previousLayer->GetNeuron(i);

		//_m_output_sum_margin_of_error = expected - _m_delta_output_sum;

		//_m_delta_sum = _m_delat_output_sum_derivative * _m_output_sum_margin_of_error;
	}
	
}



NeuralNetwork::Neuron::~Neuron()
{
}
