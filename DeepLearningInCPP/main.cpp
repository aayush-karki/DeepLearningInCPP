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
	hyperParameters.m_layersInfo = { 4,2,1 };

	// @TODO: add SetActivationFunction() so that we do not have to pass it 
	// again and agian on forward pass. 
	
 	// inializing the activation function list of each neuron
	std::vector<AF::ENUM_ActiFunc> activationFuncPerLayerList = { AF::ENUM_ActiFunc::m_none,
		AF::ENUM_ActiFunc::m_leakyRelu, AF::ENUM_ActiFunc::m_sigmoid };

	// reading and parsing the train set and test set 
	/*MnistParser trainSet("train-labels.idx1-ubyte", "train-images.idx3-ubyte");
	MnistParser testSet("t10k-labels.idx1-ubyte", "t10k-images.idx3-ubyte");*/

	/// @todo delete me
	// creating a  temp data set and actual labels
	std::vector<std::vector<uint8_t>*> inputList;
	std::vector<uint8_t> input1 = { 11,12,13,14 };
	std::vector<uint8_t> input2 = { 21,22,23,24 };
	inputList.push_back( &input1 );
	inputList.push_back( &input2 );

	std::vector<uint8_t> label = { 1,0,0,1 };

	// setting up the NN
	NeuralNetwork nnModel( input1.size(), hyperParameters.m_layersInfo );

	nnModel.SetActivaitonFunciton( activationFuncPerLayerList );
	nnModel.InitialParameters(); 
	nnModel.SetDataSet( &inputList ); /// @todo change me to actual dataset
	nnModel.SetDataLabel( &label ); /// @todo change me to actual labels

	nnModel.ForwardPropagation( );

	//FileWriter printTrainSet("test1.txt");
	//printTrainSet.WrtiePrdectionsToFile(trainSet.GetActualLabels(), trainSet.GetActualLabels(),
	//	trainSet.GetDataSet(), trainSet.GetImgRow(), trainSet.GetImgCol());

	return 0;
}