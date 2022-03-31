/// 
/// DeepLearningInCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
///
#include "stdafx.h"
#include <iostream>

#include "FileReader.h"
#include "FileWriter.h"
#include "MnistParser.h"

int main()
{
	MnistParser trainSet("t10k-labels.idx1-ubyte", "t10k-images.idx3-ubyte");
	FileWriter printTrainSet("test1.txt");
	printTrainSet.WrtiePrectionsToFile(trainSet.GetActualLabels(), trainSet.GetActualLabels(),
		trainSet.GetDataSet(), trainSet.GetImgRow(), trainSet.GetImgCol());

	return 0;
}