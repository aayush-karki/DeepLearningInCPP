/*************************************************************************************/
/// 
/// @file FileWriter.cpp 
/// 
/// @brief  This file is a source file for FileWriter class.
/// 
/// It contains all of the defination of  the member funciton.
///
/// 
/*************************************************************************************/

#include "stdafx.h"
#include "iomanip"

#include "FileWriter.h"

/// 
/// @brief constructor, creates and opens the file.
///
/// @param a_fileName: name of the file to be opened
/// @param a_openIstream: true if open as istream, false if open as ostream
/// 
FileWriter::FileWriter(std::string a_fileName)
{
	// opening the file
	m_oFile.open(a_fileName, std::ios::binary);

	// checking if the file opened or not
	if (!m_oFile.is_open())
	{
		throw("Could not open!!");
	}
}

/// 
/// @brief deconstructor, Closes the file.
///
FileWriter::~FileWriter()
{
	// closing the file 
	m_oFile.close();
}


/// 
/// @brief Writes to the file
/// 
/// @param a_actualOutput memory address of vector containing all the actual output listed in the label
/// @param a_predictedOutput memory address of vector containing all the output predicted by our NN
/// @param a_inputSet memory address of vector containing all the inputs that is used to train/test our our NN
/// @param a_imgRow number of row of pixel in one image
/// @param a_imgCol number of column of pixel in one image
/// 
void FileWriter::WrtiePrectionsToFile(const std::vector<int>& a_actualOutput, const std::vector<int>& a_predictedOutput,
	const std::vector<std::vector<int>>& a_inputSet, int a_imgRow, int a_imgCol)
{
	// checking that the size is same
	assert(a_actualOutput.size() == a_predictedOutput.size() == a_inputSet.size());

	for (unsigned i = 0; i < a_actualOutput.size(); i++) 
	{
		m_oFile << "Image Actual Label: " << a_actualOutput.at(i) << "\n";
		m_oFile << "Our predicted Label: " << a_actualOutput.at(i)<< "\n" << "\n";

		// writing the representation of the image to the file in the form of ascii char '*'
		// assumes that the number of row and 
		for (unsigned row = 0; row < a_imgRow; row++) {
			for (unsigned col = 0; col < a_imgCol; col++) {
				if (a_inputSet[i][row * a_imgRow + col] == 0) {
					m_oFile << " ";
				}
				else {
					m_oFile << "*";
				}
			}
			m_oFile << "\n";
		}

		int fillWidth = 0;
		if (a_imgCol < 25)
		{
			fillWidth = 30;
		}
		else
		{
			fillWidth = a_imgCol + 5;
		}

		m_oFile << "\n" << std::setw(fillWidth) << std::setfill('-') << "\n";
		m_oFile << std::setfill(' ');

	}
}

