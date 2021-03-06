// NeuralNetwork.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>


#define INPUT_LAYER 0

#define OUTPUT_LAYER_NEURONS(x) x.back().size()-1

#define EXTRA_BIAS_NEURON 1

#define NEXT_LAYER 1

#define FIRST_HIDDEN_LAYER INPUT_LAYER+1

#define RANDOM_GENERATOR (double)rand() / (double)RAND_MAX

// Forward declaration
struct Connection
{
	double weights;

	double delta_weights;
};

class Neuron;
//every layer contains neurons for its vector.
typedef std::vector<Neuron> Layer;

class Neuron
{
public:

	Neuron(const unsigned  iconnections, const unsigned ineuron);

	static double TransformFn(double x);

	static double TransformFnDerivative(double x);

	void FeedForward(const Layer &prevLayer);

	void SetOutput(double input);

	double GetOutput() const;

	void CalculateOutputGradients(double targetValue);

	double SumDOW(const Layer &nextLayer);

	void CalculateHiddenGradient(const Layer &nextLayer);

	void UpdateInputWeights(Layer &prevLayer);

private:

	std::vector<Connection> m_connections;

	double m_output;

	unsigned m_ineuron;

	double m_gradient;

	static double eta; // {0.0 ..... 1.0) overall net training

	static double alpha; // {0.0 ... n } momentum , multiplier of last weight change

};


double Neuron::eta = 0.15; //overall net learning rate;

double Neuron::alpha = 0.5; // momentum





class NeuralNet;

class NeuralNet
{

public:

	NeuralNet(const std::vector<unsigned> &topology);

	void FeedForward(const std::vector<double> &input);

	void BackPropagation(const std::vector<double> &targetVlaue);

	void GetResult(std::vector<double> &output) const;

	double GetRecentAverageError(void) const { return m_recentAverageError; }

private:

	std::vector<Layer> m_layer;

	double m_error;

	double m_recentAverageError;

	static double m_recentAverageSmoothingFactor;
};


double NeuralNet::m_recentAverageSmoothingFactor = 30000.0; // Number of training samples to average over



Neuron::Neuron(const unsigned  iconnections, const unsigned ineuron)
{
	for (unsigned conn = 0; conn < iconnections; conn++)
	{
		m_connections.push_back(Connection());

		m_connections.back().weights = RANDOM_GENERATOR;
	}

	m_ineuron = ineuron;
}


double Neuron::TransformFn(double x)
{
	//tanh - output range [-1.0 .... 1.0] 
	return tanh(x);
}

double Neuron::TransformFnDerivative(double x)
{
	//tanh derivative
	return 1.0 - x * x;
}


void Neuron::FeedForward(const Layer &prevLayer)
{
	double sum = 0.0;

	//sum the previous layer's output neuron (which are inputs);
	//note also include the bias neuron from input.
	for (unsigned ineuron = 0; ineuron < prevLayer.size(); ineuron++)
	{
		sum = sum + prevLayer[ineuron].GetOutput() * prevLayer[ineuron].m_connections[m_ineuron].weights;
	}

	//set by computational neurons andby input neurons
	m_output = Neuron::TransformFn(sum);
}

// called by bias neuron only.
void Neuron::SetOutput(double input)
{
	m_output = input;
}


void Neuron::CalculateOutputGradients(double targetValue)
{
	double delta = targetValue - m_output;

	m_gradient = delta * TransformFnDerivative(m_output);
}

double Neuron::SumDOW(const Layer &nextLayer)
{
	double sum = 0.0;

	for (unsigned ineuron = 0; ineuron < nextLayer.size() - 1; ineuron++)
	{
		sum +=   m_connections[ineuron].weights * nextLayer[ineuron].m_gradient;
	}

	return sum;

}


void Neuron::CalculateHiddenGradient(const Layer &nextLayer)
{
	double dow = SumDOW(nextLayer);

	m_gradient = dow * TransformFnDerivative(m_output);
}


void Neuron::UpdateInputWeights(Layer &prevLayer)
{
	for (unsigned ineuron = 0; ineuron < prevLayer.size(); ineuron++)
	{
		Neuron &neuron = prevLayer[ineuron];

		double oldDeltaWeight = neuron.m_connections[m_ineuron].delta_weights;

		double newDeltaWeight =
			//individual input , magnified by the graadient and train rate:
			eta
			* neuron.GetOutput()
			*m_gradient
			//also add momentum = a fraction of the previous delta weight
			+ alpha
			+ oldDeltaWeight;


		neuron.m_connections[m_ineuron].delta_weights = newDeltaWeight;
		neuron.m_connections[m_ineuron].weights += newDeltaWeight;

	}

}


double Neuron::GetOutput() const
{
	return m_output;
}




NeuralNet::NeuralNet(const std::vector<unsigned> &topology)
{

	unsigned numLayers = (unsigned)topology.size();

	//pushing the layers in neural network.
	for (unsigned ilayer = 0; ilayer < numLayers; ilayer++)
	{
		//push the layer to network
		m_layer.push_back(Layer());

		//finde previous neuron for connection to next layer neurons
		unsigned iconnections = (ilayer == (topology.size() - 1) ? 0 : topology[ilayer + NEXT_LAYER]);

		//create the neurons of that layer and push in the currently created layer with one exta bias neuron.
		for (unsigned ineuron = 0; ineuron < (unsigned)topology[ilayer] + EXTRA_BIAS_NEURON; ineuron++)
		{
			//pushing the neurons to layer.
			m_layer.back().push_back(Neuron(iconnections, ineuron));
		}

		//set the bias neuron output to 1.0 ( this was the last neuron pushed in the layer)
		m_layer.back().back().SetOutput(1.0);
	}
}


void NeuralNet::FeedForward(const std::vector<double> &input)
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

		for (unsigned ineuron = 0; ineuron < m_layer[ilayer].size()-1; ineuron++)
		{
			m_layer[ilayer][ineuron].FeedForward(previousLayer);
		}
	}
}


void NeuralNet::BackPropagation(const std::vector<double> &targetVlaue)
{
	//this place tells wheather training is working or not.

	//todo:

	//1. calculate overall net error (RMS of output neuron errors)
	m_error = 0.0;
	Layer &outputLayer = m_layer.back();
	for (unsigned ineuron = 0; ineuron < outputLayer.size() - EXTRA_BIAS_NEURON; ineuron++)
	{
		double delta = targetVlaue[ineuron] - outputLayer[ineuron].GetOutput();

		m_error += delta * delta;

	}

	m_error /= outputLayer.size() - 1; // get average error squared

	m_error = sqrt(m_error); // RMS


	// Implement Recent Average Mesaurement for check the error indication how well the network is trained or workingo over the sample		 
	m_recentAverageError = (m_recentAverageError*m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);


	//2. calculate output layer gradients.
	for (unsigned ineuron = 0; ineuron < outputLayer.size() - EXTRA_BIAS_NEURON; ineuron++)
	{
		outputLayer[ineuron].CalculateOutputGradients(targetVlaue[ineuron]);
	}


	//3. calculate gradients of hidden layeres.
	for (unsigned iLayer = ((unsigned)m_layer.size() - 2); iLayer > 0; iLayer--)
	{
		Layer &hiddenLayer = m_layer[iLayer];

		Layer &nextLayer = m_layer[iLayer + 1];

		for (unsigned ineuron = 0; ineuron < hiddenLayer.size(); ineuron++)
		{
			hiddenLayer[ineuron].CalculateHiddenGradient(nextLayer);
		}
	}

	//4. update the connection weights.
	for (unsigned iLayer = ((unsigned)m_layer.size() - 1); iLayer > 0; iLayer--)
	{
		Layer &currentLayer = m_layer[iLayer];

		Layer &prevLayer = m_layer[iLayer - 1];

			for (unsigned ineuron = 0; ineuron < currentLayer.size()-1; ineuron++)
		{
			currentLayer[ineuron].UpdateInputWeights(prevLayer);
		}

	}
}


void NeuralNet::GetResult(std::vector<double> &output) const
{
	//clean the previous results
	output.clear();


	for (unsigned ineuron = 0; ineuron < OUTPUT_LAYER_NEURONS(m_layer); ineuron++)
	{
		output.push_back(m_layer.back()[ineuron].GetOutput());
	}
}








void DEBUG_VECTOR(std::string label, std::vector<double> &v)
{
	std::cout << label << " ";
	for (unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}

	std::cout << std::endl;
}
int main()
{

	//create training data:
	std::vector<std::vector<double>> trainingInputData;
	std::vector<std::vector<double>> trainingTargetData;

	for (size_t i = 0; i < 30000; i++)
	{
		int  n1 = rand() % 2;
		int  n2 = rand() % 2;
		double  target = n1 ^ n2;

		std::vector<double> InputRecord;
		std::vector<double>targetRecord;
		InputRecord.push_back(n1);
		InputRecord.push_back(n2);
		targetRecord.push_back(target);

		trainingInputData.push_back(InputRecord);
		trainingTargetData.push_back(targetRecord);
		

		std::cout << "\n n1: " << n1 <<" XOR " << " n2:" << n2 << " target:" << target;
	}
	//



	//topology
	//eg topology{3,2,2}
	//3- input neuron
	//2- hidden layer neurons
	//2- output neurons 
	//size of above vector  will give us neural network layers present.
	std::vector<unsigned> topology;
	topology.push_back(2);
	topology.push_back(4);
	topology.push_back(1);
	//constructor with minimum information
	NeuralNet nn(topology);


	
	


	




	int record = 0;
	while (record != trainingInputData.size())
	{

		std::cout << std::endl << "PASS: "<<record << std::endl<<  std::endl;
		
		//for setting training input data
		//input values
		std::vector<double> input = trainingInputData[record];
		DEBUG_VECTOR("\ INPUT : ", input);
		nn.FeedForward(input);

		//getting result back from neural network.
		//output values
		std::vector<double> output;
		nn.GetResult(output);
		DEBUG_VECTOR("\n OUTPUT : ", output);

		//after the training what output is suppose 
		//to be and back propagation for neuron
		//target values
		std::vector<double> target = trainingTargetData[record];
		DEBUG_VECTOR("\n TARGET : ", target);
		nn.BackPropagation(target);
		
		// Report how well the training is working, average over recent samples:
		std::cout << std::endl <<"NET RECENT AVERAGE ERROR : "<< nn.GetRecentAverageError() << std::endl;

		record++;
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
