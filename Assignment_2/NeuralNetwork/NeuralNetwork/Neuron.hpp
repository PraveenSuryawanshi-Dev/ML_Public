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

		void CalculateTotalError(double expected);

		double GetTotalError();
		
		double GetWeight(int index);

		double GetOutput();

		size_t GetWeightSize();

		void SetWeight(int index, double weight);

		void UpdateWeights();

		~Neuron();

	private:

		ACTIVATION_TYPE _m_activationType;

		double _m_output_sum;

		double _m_SquareError;

		unsigned int _m_iTotalNeuronNextLayer;

		std::vector<double> _m_Weights;

		std::vector<double> _m_TempWeights;

		static double _m_totatl_SquareError;

	};
}

#endif
