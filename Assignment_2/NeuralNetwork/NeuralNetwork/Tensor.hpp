#pragma once
#ifndef _TENSOR_HPP_
#define _TENSOR_HPP_

#include <vector>

namespace NeuralNetwork
{
	typedef struct _DIMENSION_
	{
		unsigned int x;
		unsigned int y;
		unsigned int z;
	}TENSOR_DIMENSION;

	class Tensor
	{
	public:

		Tensor(TENSOR_DIMENSION dimension);

		TENSOR_DIMENSION GetDimension();

		double GetValue(TENSOR_DIMENSION location);

		~Tensor();

	private:

		TENSOR_DIMENSION _m_dimension;

		std::vector<std::vector<std::vector<double>>> _m_data;
	};
}

#endif
