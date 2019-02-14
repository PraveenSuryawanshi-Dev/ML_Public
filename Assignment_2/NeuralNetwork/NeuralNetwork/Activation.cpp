#include "Activation.hpp"

double NeuralNetwork::Activation::Linear(double x)
{
	return x;
}

double NeuralNetwork::Activation::Sigmoid(double x)
{	
	return 1 / (1 + exp(-x));
}

double NeuralNetwork::Activation::Relu(double x)
{
	if (x <= 0.0)
		return 0.0;
	else
		return x;
}

double NeuralNetwork::Activation::HyperbolicTangent(double x)
{
	double num = 1 - exp(-2*x);

	double den = 1 + exp(2 * x);

	return num/den;
}
