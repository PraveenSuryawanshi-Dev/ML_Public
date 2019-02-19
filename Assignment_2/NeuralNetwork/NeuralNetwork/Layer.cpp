#include "Layer.hpp"
#include "Neuron.hpp"

NeuralNetwork::Layer::Layer(LAYER_TYPE lType,ACTIVATION_TYPE acType, unsigned int iTotalNeuronsCurrentLayer, unsigned int iTotalNeuronNextLayer, bool bIsBiasNeuronNeeded)
{

	_m_layerTpye = lType;

	_m_activationType = acType;

	_m_inTotalNeuronsCurrentLayer = iTotalNeuronsCurrentLayer;

	_m_inTotalNeuronsNextLayer = iTotalNeuronNextLayer;

	_m_isBiasNeeded = bIsBiasNeuronNeeded;
}

void NeuralNetwork::Layer::Build()
{
	for (size_t neuronIndex = 0; neuronIndex < _m_inTotalNeuronsCurrentLayer; neuronIndex++)
	{
		Neuron *neuron = new  Neuron(_m_activationType, _m_inTotalNeuronsNextLayer);
		
		neuron->Build();

		_m_Neurons.push_back(neuron);
	}

}

void NeuralNetwork::Layer::LatchInput(unsigned int whichNeuron,double data)
{
	_m_Neurons.at(whichNeuron)->LatchInput(data);
}


void NeuralNetwork::Layer::FeedForward(NeuralNetwork::Layer *previousLayer)
{
	for (size_t neuronIndex = 0; neuronIndex < _m_Neurons.size(); neuronIndex++)
	{
		_m_Neurons[neuronIndex]->FeedForward(previousLayer, _m_activationType);
	}
}

void NeuralNetwork::Layer::CalculateTotalError(Tensor &tensor)
{
	for (size_t neuronIndex = 0; neuronIndex < _m_Neurons.size(); neuronIndex++)
	{
		NeuralNetwork::TENSOR_DIMENSION dimension{ neuronIndex,1,0 };

		_m_Neurons[neuronIndex]->CalculateTotalError(tensor.GetValue(dimension));
	}
}

void NeuralNetwork::Layer::BackPropagation(NeuralNetwork::Layer * previousLayer, Tensor &tensor , double learningRate)
{

	if (_m_activationType == ACTIVATION_TYPE::SIGMOID)
	{
		if (_m_layerTpye == OUTPUT)
		{
			for (size_t currentNeuronIndex = 0; currentNeuronIndex < _m_Neurons.size(); currentNeuronIndex++)
			{

				NeuralNetwork::TENSOR_DIMENSION dimension{ currentNeuronIndex,1,0 };


				double t1 = -(tensor.GetValue(dimension) - _m_Neurons[currentNeuronIndex]->GetOutput());

				double t2 = _m_Neurons[currentNeuronIndex]->GetOutput() * (1 - _m_Neurons[currentNeuronIndex]->GetOutput());


				for (size_t currentNeuronWeightIndex = 0; currentNeuronWeightIndex < _m_Neurons[currentNeuronIndex]->GetWeightSize(); currentNeuronWeightIndex++)
				{
					double t3 = previousLayer->GetNeuron(currentNeuronWeightIndex)->GetOutput();

					double newWeight = _m_Neurons[currentNeuronIndex]->GetWeight(currentNeuronWeightIndex) - learningRate * (t1 * t2 * t3);

					_m_Neurons[currentNeuronIndex]->SetWeight(currentNeuronWeightIndex, newWeight);
				}

			}
		}


		if (_m_layerTpye == HIDDEN)
		{

		}
	}

}

bool NeuralNetwork::Layer::IsBiasNeuron()
{
	return _m_isBiasNeeded;
}

size_t NeuralNetwork::Layer::Size()
{
	return _m_Neurons.size();
}

NeuralNetwork::Neuron* NeuralNetwork::Layer::GetNeuron(int which)
{
	return _m_Neurons.at(which);
}

void NeuralNetwork::Layer::UpdateWeights()
{
	for (size_t neuronIndex = 0; neuronIndex < _m_Neurons.size(); neuronIndex++)
	{
		_m_Neurons[neuronIndex]->UpdateWeights();
	}
}

NeuralNetwork::Layer::~Layer()
{
}
