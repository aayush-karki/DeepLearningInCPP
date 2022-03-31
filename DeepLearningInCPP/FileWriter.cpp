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
/// @param a_FilePath: name of the file to be opened
/// @param a_openIstream: true if open as istream, false if open as ostream
/// 
FileWriter::FileWriter(std::string a_FilePath)
{
	// opening the file
	m_oFile.open(a_FilePath, std::ios::binary);

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
void FileWriter::WrtiePrectionsToFile(const std::vector<uint8_t>& a_actualOutput, const std::vector<uint8_t>& a_predictedOutput,
	const std::vector<std::vector<uint8_t>>& a_inputSet, uint32_t a_imgRow, uint32_t a_imgCol)
{
	// checking that the size is same
	assert(a_actualOutput.size() == a_predictedOutput.size());
	assert(a_predictedOutput.size() == a_inputSet.size());

	for (unsigned currOutputIdx = 0; currOutputIdx < a_actualOutput.size(); ++currOutputIdx)
	{
		m_oFile << "Image Actual Label: " << a_actualOutput.at(currOutputIdx) << "\n";
		m_oFile << "Our predicted Label: " << a_actualOutput.at(currOutputIdx)<< "\n" << "\n";

		// writing the representation of the image to the file in the form of ascii char '*'
		for (uint32_t row = 0; row < a_imgRow; row++) {
			for (uint32_t col = 0; col < a_imgCol; col++) {
				std::cout << a_inputSet[currOutputIdx][row * a_imgRow + col] <<std::endl;
				if (a_inputSet[currOutputIdx][row * a_imgRow + col] == 0) {
					m_oFile << " ";
				}
				else {
					m_oFile << "*";
				}
			}
			m_oFile << "\n";
		}

		uint32_t fillWidth = 0;
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

