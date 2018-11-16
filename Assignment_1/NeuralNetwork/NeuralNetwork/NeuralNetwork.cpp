// NeuralNetwork.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>


#define INPUT_LAYER 0

#define OUTPUT_LAYER_NEURONS(x) x.back().size()-1

#define EXTRA_BIAS_NEURON 1

#define NEXT_LAYER 1

#define FIRST_HIDDEN_LAYER INPUT_LAYER+1

#define RANDOM_GENERATOR (double)rand() / (double)RAND_MAX

// Forward declaration
class Neuron;

class NeuralNet;

struct Connection
{
	double weights;

	double delta_weights;
};


class Neuron
{
public:

	Neuron(const unsigned  iconnections, const unsigned ineuron)
	{
		for (unsigned conn = 0; conn < iconnections; conn++)
		{
			m_outputWeight.push_back(Connection());

			m_outputWeight.back().weights = RANDOM_GENERATOR;
		}

		m_ineuron = ineuron;
	}

	static double TransformFn(double x)
	{
		//tanh - output range [-1.0 .... 1.0] 
		return tanh(x);
	}

	static double TransformFnDerivative(double x)
	{
		//tanh derivative
		return 1.0 - x * x;
	}


	void FeedForward(const Layer &prevLayer)
	{
		double sum = 0.0;

		//sum the previous layer's output neuron (which are inputs);
		//note also include the bias neuron from input.
		for (unsigned ineuron = 0; ineuron < prevLayer.size() + EXTRA_BIAS_NEURON; ineuron++)
		{			
			sum = sum + prevLayer[ineuron].GetOutput() * prevLayer[ineuron].m_outputWeight[m_ineuron].weights;
		}

		//set by computational neurons andby input neurons
		m_output = Neuron::TransformFn(sum);
	}

	 // called by bias neuron only.
	void SetOutput(double input)
	{
		m_output = input;
	}

	double GetOutput() const
	{
		return m_output;
	}


private:

	std::vector<Connection> m_outputWeight;

	double m_output;

	unsigned m_ineuron;
};


//every layer contains neurons for its vector.
typedef std::vector<Neuron> Layer;

class NeuralNet
{
public:

	NeuralNet(const std::vector<unsigned> &topology)
	{

		unsigned numLayers = topology.size();

		//pushing the layers in neural network.
		for (unsigned ilayer = 0; ilayer < numLayers; ilayer++)
		{
			//push the layer to network
			m_layer.push_back(Layer());

			//finde previous neuron for connection to next layer neurons
			unsigned iconnections = (ilayer == (topology.size()-1) ? 0 : topology[ilayer + NEXT_LAYER]);

			//create the neurons of that layer and push in the currently created layer with one exta bias neuron.
			for (size_t ineuron = 0; ineuron < topology[ilayer] + EXTRA_BIAS_NEURON; ineuron++)
			{
				//pushing the neurons to layer.
				m_layer.back().push_back(Neuron(iconnections,ineuron));
			}

			//set the bias neuron output to 1.0 ( this was the last neuron pushed in the layer)
			m_layer.back().back().SetOutput(1.0);
		}
	}


	void FeedForward(const std::vector<double> &input)
	{
		for (unsigned ineuron = 0; ineuron < input.size(); ineuron++)
		{
			//set input value to input neuron or latch the value to input neurons
			// here INPUT_LAYER:0 represent input layer and neuron 
			m_layer[INPUT_LAYER][ineuron].SetOutput(input[ineuron]);
		}

		//forward progate
		//traverse from all hidden layers to output layer
		for (unsigned ilayer = FIRST_HIDDEN_LAYER; ilayer < m_layer.size(); ilayer++)
		{
			Layer &previousLayer = m_layer[ilayer - 1];

			for (unsigned ineuron = 0; ineuron < m_layer[ilayer].size(); ineuron++)
			{
				m_layer[ilayer][ineuron].FeedForward(previousLayer);
			}
		}
	}


	void BackPropagation(const std::vector<double> &vlaue)
	{
		//this place tells wheather training is working or not.
		
		//todo:

		//1. calculate overall net error (RMS of output neuron errors)

		//2. calculate output layer gradients.

		//3. calculate gradients of hidden layeres.

		//4. update the connection weights.
	}


	void GetResult(std::vector<double> &output) const
	{
		//clean the previous results
		output.clear();


		for (unsigned ineuron = 0; ineuron < OUTPUT_LAYER_NEURONS(m_layer); ineuron++)
		{
			output.push_back(m_layer.back()[ineuron].GetOutput());
		}
	}

private:

	std::vector<Layer> m_layer;

};

int main()
{
	//topology
	//eg topology{3,2,2}
	//3- input neuron
	//2- hidden layer neurons
	//2- output neurons 
	//size of above vector  will give us neural network layers present.
	std::vector<unsigned> topology;
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(2);
	//constructor with minimum information
	NeuralNet nn(topology);


	//input values
	std::vector<double> input;

	//target values
	std::vector<double> vlaue;

	//output values
	std::vector<double> output;


	

	while (true)
	{
		//for setting training input data
		nn.FeedForward(input);

		//getting result back from neural network.
		nn.GetResult(output);

		//after the training what output is suppose 
		//to be and back propagation for neuron
		nn.BackPropagation(vlaue);
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
