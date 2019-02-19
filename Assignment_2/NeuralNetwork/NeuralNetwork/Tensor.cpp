#include "Tensor.hpp"

NeuralNetwork::Tensor::Tensor(TENSOR_DIMENSION dimension)
{
	_m_dimension = dimension;

	double zero = 0.0;

	for (size_t z = 0; z < _m_dimension.z; z++)
	{
		_m_data.push_back(std::vector<std::vector<double>>());
		
		for (size_t x = 0; x < _m_dimension.x; x++)
		{
			_m_data[z].push_back(std::vector<double>());	

			for (size_t y = 0; y < _m_dimension.y; y++)
			{
				_m_data[z][x].push_back(zero);
			}
		}
	}
}

NeuralNetwork::TENSOR_DIMENSION NeuralNetwork::Tensor::GetDimension()
{
	return _m_dimension;
}

double NeuralNetwork::Tensor::GetValue(TENSOR_DIMENSION location)
{
	return _m_data[location.z][location.x][location.y];
}

void NeuralNetwork::Tensor::operator+(double value)
{
	for (size_t z = 0; z < _m_dimension.z; z++)
	{
		for (size_t x = 0; x < _m_dimension.x; x++)
		{
			for (size_t y = 0; y < _m_dimension.y; y++)
			{
				_m_data[z][x][y] += value;
			}
		}
	}
}

void NeuralNetwork::Tensor::operator*(double scale)
{
	for (size_t z = 0; z < _m_dimension.z; z++)
	{
		for (size_t x = 0; x < _m_dimension.x; x++)
		{
			for (size_t y = 0; y < _m_dimension.y; y++)
			{
				_m_data[z][x][y] *= scale;
			}
		}
	}
}

void NeuralNetwork::Tensor::operator/(double value)
{
	for (size_t z = 0; z < _m_dimension.z; z++)
	{
		for (size_t x = 0; x < _m_dimension.x; x++)
		{
			for (size_t y = 0; y < _m_dimension.y; y++)
			{
				_m_data[z][x][y] /= value;
			}
		}
	}
}


NeuralNetwork::Tensor::~Tensor()
{
}

std::ostream & NeuralNetwork::operator<<(std::ostream & cout, const Tensor & tensor)
{
	for (size_t z = 0; z < tensor._m_dimension.z; z++)
	{
		for (size_t x = 0; x < tensor._m_dimension.x; x++)
		{
			cout << "\n";

			for (size_t y = 0; y < tensor._m_dimension.y; y++)
			{
				cout << tensor._m_data[z][x][y] << "\t";
			}
		}
	}
	return cout;
}
