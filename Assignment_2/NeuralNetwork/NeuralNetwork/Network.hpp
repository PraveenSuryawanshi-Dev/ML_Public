#pragma once
#ifndef  _NETWORK_HPP_
#define _NETWORK_HPP_

#include <vector>
#include "Layer.hpp"
#include "Tensor.hpp"

namespace NeuralNetwork
{
	class Network
	{
	public:

		Network();

		void Add(Layer *layer);		

		void LatchInput(Tensor &tensor);

		void FeedForward();

		void BackPropagation(double target);

		~Network();

	private:

		std::vector<Layer*> _m_Layers;
	};
}

#endif