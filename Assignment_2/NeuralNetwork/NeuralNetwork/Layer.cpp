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
	unsigned int length = _m_isBiasNeeded ? _m_inTotalNeuronsCurrentLayer + 1 : _m_inTotalNeuronsCurrentLayer;

	for (size_t i = 0; i < length; i++)
	{
		Neuron *neuron =new  Neuron(_m_activationType, _m_inTotalNeuronsNextLayer);
		
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
	for (size_t i = 0; i < _m_Neurons.size(); i++)
	{
		_m_Neurons[i]->FeedForward(previousLayer, _m_activationType);
	}
}

size_t NeuralNetwork::Layer::Size()
{
	return _m_Neurons.size();
}

NeuralNetwork::Neuron* NeuralNetwork::Layer::GetNeuron(int which)
{
	return _m_Neurons.at(which);
}

NeuralNetwork::Layer::~Layer()
{
}
