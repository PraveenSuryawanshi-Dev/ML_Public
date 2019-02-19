#include "Neuron.hpp"

#define RANDOM(min,max) { min + (int) (rand() / (double) (RAND_MAX + 1) * (max - min + 1))}

#define SQR(x) x * x

double NeuralNetwork::Neuron::_m_totatl_SquareError = 0.0;

NeuralNetwork::Neuron::Neuron(ACTIVATION_TYPE acType, unsigned int iTotalNeuronNextLayer)
{
	_m_activationType = acType;

	_m_iTotalNeuronNextLayer = iTotalNeuronNextLayer;

	_m_output_sum = 0.0;

	_m_SquareError = 0.0;
	
}

void NeuralNetwork::Neuron::Build()
{
	for (size_t weightIndex = 0; weightIndex < _m_iTotalNeuronNextLayer; weightIndex++)
	{
		_m_Weights.push_back(RANDOM(0.0, 1.0));

		_m_TempWeights.push_back(RANDOM(0.0, 1.0));
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

		for (size_t weightIndex = 0; weightIndex < currentNeuron->_m_Weights.size(); weightIndex++)
		{
			output += currentNeuron->_m_output_sum * currentNeuron->_m_Weights[weightIndex];
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

void NeuralNetwork::Neuron::CalculateTotalError(double expected)
{
	_m_SquareError = (SQR(expected - _m_output_sum)) * (1.0/2.0);

	_m_totatl_SquareError += _m_SquareError;

}

double NeuralNetwork::Neuron::GetTotalError()
{
	return _m_totatl_SquareError;
}

double NeuralNetwork::Neuron::GetWeight(int index)
{
	return  _m_Weights[index];
}

double NeuralNetwork::Neuron::GetOutput()
{
	return _m_output_sum;
}

size_t NeuralNetwork::Neuron::GetWeightSize()
{
	return _m_Weights.size();
}

void NeuralNetwork::Neuron::SetWeight(int index, double weight)
{
	_m_TempWeights.at(index) = weight;
}

void NeuralNetwork::Neuron::UpdateWeights()
{
	for (size_t weightIndex = 0; weightIndex < _m_TempWeights.size(); weightIndex++)
	{
		_m_Weights[weightIndex] = _m_TempWeights[weightIndex];
	}
}



NeuralNetwork::Neuron::~Neuron()
{
}
