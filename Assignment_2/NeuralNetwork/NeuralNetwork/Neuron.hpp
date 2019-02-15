#pragma once
#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include <stdio.h>
#include <vector>
#include "Activation.hpp"
#include "Layer.hpp"

namespace NeuralNetwork
{
	class Neuron
	{
	public:

		Neuron(ACTIVATION_TYPE acType, unsigned int iTotalNeuronNextLayer);

		void Build();

		void LatchInput(double data);

		void FeedForward(Layer *previousLayer, ACTIVATION_TYPE activationType);

		void BackPropagation(Layer *previousLayer, double expected);

		~Neuron();

	private:

		ACTIVATION_TYPE _m_activationType;

		double _m_output_sum;

		double _m_delta_output_sum;

		double _m_delat_output_sum_derivative;

		unsigned int _m_iTotalNeuronNextLayer;

		double _m_output_sum_margin_of_error;

		double _m_delta_sum;

		std::vector<double> _m_Weights;

	};
}

#endif
