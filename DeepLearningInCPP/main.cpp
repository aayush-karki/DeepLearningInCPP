/// 
/// DeepLearningInCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
///
#include "stdafx.h"
#include <iostream>

#include "FileReader.h"
#include "FileWriter.h"

int main()
{
	FileReader readTestLabel("t10k-labels-idx1-ubyte");
	FileReader readTestImg("t10k-images-idx3-ubyte");
	FileReader readTrainImg("train-images-idx3-ubyte");
	FileReader readTrainlaber("train-labels-idx1-ubyte");

	FileWriter wFile("test1.txt");
	
	std::vector<int> aOut = { 1 };
	std::vector<int> pOut = { 1 };
	std::vector<std::vector<int>> img = { {0,2,3,0,0,6,7,8,9} };

	std::cout << aOut.size() << " " << pOut.size() << " " << img.size();

	wFile.WrtiePrectionsToFile(aOut, pOut, img, 3, 3);
	


	return 0;
}