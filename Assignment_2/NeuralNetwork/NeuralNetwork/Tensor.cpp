#include "Tensor.hpp"

NeuralNetwork::Tensor::Tensor(TENSOR_DIMENSION dimension)
{
	_m_dimension = dimension;

}

NeuralNetwork::TENSOR_DIMENSION NeuralNetwork::Tensor::GetDimension()
{
	return _m_dimension;
}

double NeuralNetwork::Tensor::GetValue(TENSOR_DIMENSION location)
{
	return _m_data.at(location.x).at(location.y).at(location.z);
}

NeuralNetwork::Tensor::~Tensor()
{
}
