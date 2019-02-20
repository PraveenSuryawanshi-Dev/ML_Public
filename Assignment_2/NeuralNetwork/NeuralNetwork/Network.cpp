#include "Network.hpp"

#define INPUT_LAYER 0

#define FIRST_HIDDEN_LAYER 1

NeuralNetwork::Network::Network()
{
	_m_learnigRate = 0.0;
}

void NeuralNetwork::Network::Add(NeuralNetwork::Layer *layer)
{
	layer->Build();

	_m_Layers.push_back(layer);

}


void NeuralNetwork::Network::LatchInput(Tensor &tensor)
{
	NeuralNetwork::TENSOR_DIMENSION dimension = tensor.GetDimension();

	for (size_t i = 0; i < dimension.x; i++)
	{
		double data = tensor.GetValue(TENSOR_DIMENSION{ i,0,0 });

		_m_Layers[INPUT_LAYER]->LatchInput(i, data);
	}
}

void NeuralNetwork::Network::FeedForward()
{
	for (size_t LayersIndex = FIRST_HIDDEN_LAYER; LayersIndex < _m_Layers.size(); LayersIndex++)
	{
		Layer *previousLayer = _m_Layers[LayersIndex - 1];

		_m_Layers[LayersIndex]->FeedForward(previousLayer);
	}
}

void NeuralNetwork::Network::SetLearningRateETA(double x)
{
	_m_learnigRate = x;
}

void NeuralNetwork::Network::BackPropagation(Tensor &tensor)
{
	int lastLayer = _m_Layers.size()-1;

	_m_Layers[lastLayer]->CalculateTotalError(tensor);

	for (size_t LayersIndex = lastLayer; LayersIndex > 0; LayersIndex--)
	{
		Layer *previousLayer = _m_Layers[LayersIndex - 1];

		_m_Layers[LayersIndex]->BackPropagation(previousLayer,tensor, _m_learnigRate);
	}



	for (size_t LayersIndex = FIRST_HIDDEN_LAYER; LayersIndex < _m_Layers.size(); LayersIndex++)
	{
		_m_Layers[LayersIndex]->UpdateWeights();
	}
}

NeuralNetwork::Network::~Network()
{
}
