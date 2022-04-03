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
	hyperParameters.m_layersInfo = { 3,10,1 };

	// reading and parsing the train set and test set 
	MnistParser trainSet("train-labels.idx1-ubyte", "train-images.idx3-ubyte");
	MnistParser testSet("t10k-labels.idx1-ubyte", "t10k-images.idx3-ubyte");

	// setting up the NN
	NeuralNetwork nnModel(hyperParameters.m_layersInfo);
	nnModel.InitialParameters();



	//FileWriter printTrainSet("test1.txt");
	//printTrainSet.WrtiePrdectionsToFile(trainSet.GetActualLabels(), trainSet.GetActualLabels(),
	//	trainSet.GetDataSet(), trainSet.GetImgRow(), trainSet.GetImgCol());

	return 0;
}