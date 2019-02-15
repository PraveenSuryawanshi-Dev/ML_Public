#pragma once
#ifndef _ACTIVATION_HPP_
#define _ACTIVATION_HPP_


#include <math.h>

namespace NeuralNetwork
{
	typedef enum _ACTIVATION_TYPE_
	{
		NONE,
		LINEAR,
		RELU,
		SIGMOID,
		HYPERBOLIC_TANGENT,

	}ACTIVATION_TYPE;


	class Activation
	{

	public:

		static double Linear(double x);

		static double Sigmoid(double x);

		static double Relu(double x);
		
		static double HyperbolicTangent(double x);
	};
}

#endif