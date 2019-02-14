#include "Network.hpp"
#include "Layer.hpp"
#include "Activation.hpp"
#include "Tensor.hpp"

//https://stevenmiller888.github.io/mind-how-to-build-a-neural-network/

int main()
{

	NeuralNetwork::Network network;

	NeuralNetwork::Layer *input_Layer = new NeuralNetwork::Layer(NeuralNetwork::LAYER_TYPE::INPUT,NeuralNetwork::ACTIVATION_TYPE::SIGMOID, 2,3, false);
	
	NeuralNetwork::Layer *hidden_Layer1 = new NeuralNetwork::Layer(NeuralNetwork::LAYER_TYPE::HIDDEN, NeuralNetwork::ACTIVATION_TYPE::SIGMOID, 3,1, false);
	
	NeuralNetwork::Layer *output_Layer = new NeuralNetwork::Layer(NeuralNetwork::LAYER_TYPE::OUTPUT, NeuralNetwork::ACTIVATION_TYPE::SIGMOID, 1,0, false);
	

	network.Add(input_Layer);

	network.Add(hidden_Layer1);

	network.Add(output_Layer);
	

	NeuralNetwork::TENSOR_DIMENSION dimension{ 2,1,0 };

	NeuralNetwork::Tensor InputTensor(dimension);

	while (true)
	{
		network.LatchInput(InputTensor);

		network.FeedForward();

		network.BackPropagation(1.0);
	}
	
	return 1;
}