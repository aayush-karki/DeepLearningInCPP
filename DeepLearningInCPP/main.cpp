/// 
/// DeepLearningInCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
///
#include "stdafx.h"
#include <iostream>

#include "FileReader.h"
#include "FileWriter.h"
#include "MnistParser.h"
#include "RandomNumGenerator.h"
#include "NeuralNetwork.h"

int main()
{
	// inializing the random seed
	RandomNumGenerator::InializeSeed();

	// inializing the hyperparametes
	ST_HyperParameters hyperParameters;
	hyperParameters.m_layersInfo = { 2,2,1 };




	// @TODO: add SetActivationFunction() so that we do not have to pass it 
	// again and agian on forward pass. 
	
 	// inializing the activation function list of each neuron
	std::vector<AF::ENUM_ActiFunc> activationFuncPerLayerList = { AF::ENUM_ActiFunc::m_none,
		AF::ENUM_ActiFunc::m_leakyRelu, AF::ENUM_ActiFunc::m_sigmoid };

	// reading and parsing the train set and test set 
	/*MnistParser trainSet("train-labels.idx1-ubyte", "train-images.idx3-ubyte");
	MnistParser testSet("t10k-labels.idx1-ubyte", "t10k-images.idx3-ubyte");*/

	std::vector<int> inputList = { 1,2 };

	// setting up the NN
	NeuralNetwork nnModel( hyperParameters.m_layersInfo );
	//todo make it 
	nnModel.SetActivaitonFunciton( activationFuncPerLayerList );

	nnModel.InitialParameters();
	
	//@todo delete me
	// entering a 2 input for text purposes
	NeuralNetworkLayer* inputLayer = nnModel.GetNeuronLayers().at( 0 );
	if(inputLayer->GetLayerType() != ENUM_NeuronLayerType::m_inputLayer )
	{ 
		std::cerr << "Not Input layer!!" << std::endl;
		return -1;
	}
	// checking if the number of neuron in the input layer is same as the 
	// number of values in the input list
	if( inputLayer->GetLayerWidth() != inputList.size() )
	{
		std::cerr << "Num Neuron mismatch Input layer!! the layer has "<< 
			inputLayer->GetLayerWidth() << " neuron." << std::endl;
		return -1;
	}
	
	std::vector<Neuron*> inputLayerNeuronList = inputLayer->GetLayerNeuronList();
	// populating the input neurons
	for( unsigned i = 0; i < inputLayerNeuronList.size(); ++i )
	{
		inputLayerNeuronList.at( i )->SetActivationValue( inputList.at( i ) );
	}

	nnModel.ForwardPropagation( );

	//FileWriter printTrainSet("test1.txt");
	//printTrainSet.WrtiePrdectionsToFile(trainSet.GetActualLabels(), trainSet.GetActualLabels(),
	//	trainSet.GetDataSet(), trainSet.GetImgRow(), trainSet.GetImgCol());

	return 0;
}