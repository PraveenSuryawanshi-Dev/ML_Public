#include "Neuron.hpp"

#define RANDOM(min,max) { min + (int) (rand() / (double) (RAND_MAX + 1) * (max - min + 1))}

NeuralNetwork::Neuron::Neuron(ACTIVATION_TYPE acType, unsigned int iTotalNeuronNextLayer)
{
	_m_activationType = acType;

	_m_iTotalNeuronNextLayer = iTotalNeuronNextLayer;

	_m_data = 0;
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
	_m_data = data;
}


void NeuralNetwork::Neuron::FeedForward(Layer *previousLayer, ACTIVATION_TYPE activationType)
{
	for (size_t i = 0; i < previousLayer->Size(); i++)
	{
		Neuron *currentNeuron = previousLayer->GetNeuron(i);

		double x = currentNeuron->_m_data;

		double output = 0;

		for (size_t i = 0; i < currentNeuron->_m_Weights.size(); i++)
		{
			output += x * currentNeuron->_m_Weights[i];
		}

		_m_data = output;

		double finalResult = 0.0;

		switch (activationType)
		{
		case NONE:
			break;

		case RELU:
			finalResult = Activation::Relu(x);
			break;

		case SIGMOID:
			finalResult = Activation::Sigmoid(x);
			break;

		case HYPERBOLIC_TANGENT:
			finalResult = Activation::HyperbolicTangent(x);
			break;

		case LINEAR:
			finalResult = Activation::Linear(x);
			break;

		default:
			break;
		}

		_m_delta = finalResult;
	}
}



NeuralNetwork::Neuron::~Neuron()
{
}
