#pragma once
#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <stdio.h>
#include <vector>
#include "Activation.hpp"
#include "Tensor.hpp"

namespace NeuralNetwork
{
	class Neuron;


	typedef enum _LAYER_TYPE_
	{
		INPUT,
		HIDDEN,
		OUTPUT
	}LAYER_TYPE;


	class Layer
	{

	public:

		Layer(LAYER_TYPE lType, ACTIVATION_TYPE acType, unsigned int iTotalNeuronsCurrentLayer, unsigned int iTotalNeuronNextLayer,bool bIsBiasNeuronNeeded);

		void Build();

		void LatchInput(unsigned int whichNeuron, double data);

		void FeedForward(NeuralNetwork::Layer *previousLayer);

		void CalculateTotalError(Tensor &tensor);

		void BackPropagation(NeuralNetwork::Layer *previousLayer, Tensor &tensor ,double learningRate);

		bool IsBiasNeuron();

		size_t Size();

		NeuralNetwork::Neuron *GetNeuron(int which);

		void UpdateWeights();

		~Layer();

	private:

		LAYER_TYPE _m_layerTpye;

		ACTIVATION_TYPE _m_activationType;

		unsigned int _m_inTotalNeuronsCurrentLayer;

		unsigned int _m_inTotalNeuronsNextLayer;
		
		bool _m_isBiasNeeded;

		std::vector<NeuralNetwork::Neuron *> _m_Neurons;
	};
}

#endif