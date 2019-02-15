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

void NeuralNetwork::Network::LatchInput(Tensor & tensor)
{
	NeuralNetwork::TENSOR_DIMENSION dimension = tensor.GetDimension();

	for (size_t i = 0; i < dimension.x; i++)
	{
		for (size_t j = 0; j < dimension.y; j++)
		{
			double data = tensor.GetValue(TENSOR_DIMENSION{i,j,0});

			_m_Layers[INPUT_LAYER]->LatchInput(i,data);
		}
	}
}

void NeuralNetwork::Network::FeedForward()
{
	for (size_t i = FIRST_HIDDEN_LAYER; i < _m_Layers.size(); i++)
	{
		Layer *previousLayer = _m_Layers[i - 1];

		_m_Layers[i]->FeedForward(previousLayer);
	}
}

void NeuralNetwork::Network::SetLearningRateETA(double x)
{
	_m_learnigRate = x;
}

void NeuralNetwork::Network::BackPropagation(double target)
{
	int lastLayer = _m_Layers.size();

	for (size_t i = lastLayer; i > 0; i--)
	{
		Layer *previousLayer = _m_Layers[i - 1];

		_m_Layers[i]->BackPropagation(target,previousLayer);
	}
}

NeuralNetwork::Network::~Network()
{
}
