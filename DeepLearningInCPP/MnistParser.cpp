/*************************************************************************************/
/// 
/// @file MnistParser.cpp 
/// 
/// @brief  This file is a source file for MnistParser class.
/// 
/// It contains all of the defination of  the member funciton.
///
/// 
/*************************************************************************************/

#include "stdafx.h"

#include "MnistParser.h"
#include "FileReader.h"

/// 
/// @brief destructor 
/// 
/// deallocats the vectors the reperesents the images from the dataset
/// 
MnistParser::~MnistParser()
{
	// deallocating the vector the reperesents the images from the dataset
	std::vector<std::vector<uint8_t>*>::iterator currIte = m_dataSet.begin();
	
	while( currIte != m_dataSet.end() )
	{
		( *currIte )->clear();
		delete (*currIte);
	}

}

/// 
/// @brief parseing the MINST label file to construct the label vector
///   
/// @param a_labelFilePath file path to label file
/// 
void MnistParser::ParseMinstlabelFile(std::string& a_labelFilePath)
{
	// opening the file
	FileReader labelFile(a_labelFilePath);

	// reading the magic nubmer -> first line
	// which should be 2049 -> label identificaiton and converting the endian
	uint32_t magicNumber = 0;
	labelFile.ExtractFromFile((char*)&magicNumber, sizeof(magicNumber));
	magicNumber = SwapEndian(magicNumber);

	// checking the magic number is valid or not
	assert(magicNumber == 2049);

	// extracting the total number of labels
	labelFile.ExtractFromFile((char*)&m_totalLableNum, sizeof(m_totalLableNum));
	m_totalLableNum = SwapEndian(m_totalLableNum); 

	// reserving the space for labels
	m_actualLabel.reserve(m_totalLableNum);

	// extracting all the labels
	// note that all the label is in unsigned char or uint8_t format so no need to change endian 
	uint8_t tempNum = 0;
	for (unsigned currLabelidx = 0; currLabelidx < m_totalLableNum; ++currLabelidx)
	{
		labelFile.ExtractFromFile((char*)&tempNum, sizeof(tempNum));
		m_actualLabel.push_back(tempNum);
	}

	// chekcing if all the labels were extracted
	assert(m_actualLabel.size() == m_totalLableNum);
}

/// 
/// @brief parseing the MINST data set file to construct the set vector
///   
/// @param a_dataSetFilePath file path to dataset file
/// 
void MnistParser::ParseMinstSetFile(std::string& a_dataSetFilePath)
{
	// opening the file
	FileReader labelFile(a_dataSetFilePath);

	// reading the magic nubmer -> first line
	// which should be 2051 -> label identificaiton and converting the endian
	uint32_t magicNumber = 0;
	labelFile.ExtractFromFile((char*)&magicNumber, sizeof(magicNumber));
	magicNumber = SwapEndian(magicNumber);

	// checking the magic number is valid or not
	assert(magicNumber == 2051);

	// extracting the total number of images
	labelFile.ExtractFromFile((char*)&m_totalImgNum, sizeof(m_totalImgNum));
	m_totalImgNum = SwapEndian(m_totalImgNum);

	// extracting the dimentions of the image
	// row
	labelFile.ExtractFromFile((char*)&m_imgRow, sizeof(m_imgRow));
	m_imgRow = SwapEndian(m_imgRow);
	//column
	labelFile.ExtractFromFile((char*)&m_imgCol, sizeof(m_imgCol));
	m_imgCol = SwapEndian(m_imgCol);

	// reserving the space for number images
	m_dataSet.resize( m_totalImgNum );
	
	// dynamically allocating the vector containg the pixels of a image
	for( unsigned i = 0; i < m_totalImgNum; ++i )
	{
		m_dataSet.at(i) = new std::vector<uint8_t>(m_imgRow * m_imgCol, 0);
	}

	// extracting all the pixels
	// note that all the label is in unsigned char or uint8_t format so no need to change endian 
	for (unsigned currImgIdx = 0; currImgIdx < m_totalImgNum; ++currImgIdx)
	{
		uint8_t tempNum = 0;
		for (unsigned currPixelIdx = 0; currPixelIdx < m_imgRow * m_imgCol; ++currPixelIdx)
		{
			labelFile.ExtractFromFile((char*)&tempNum, sizeof(tempNum));
			(m_dataSet.at(currImgIdx))->at(currPixelIdx) = tempNum;
		}
	}
}

/// 
/// @brief Converts the number using the big-endian--MSB 
///		into little-endian--LSB or vice versa
/// @param a_val value to be converted
///  
uint32_t MnistParser::SwapEndian(uint32_t a_val)
{
	uint32_t first8bits = a_val & 0xff;
	uint32_t second8bits = (a_val >> 8) & 0xff;
	uint32_t third8bits = (a_val >> 16) & 0xff;
	uint32_t fourth8bits = (a_val >> 24) & 0xff;

	return (first8bits << 24) + (second8bits << 16) + (third8bits << 8) + fourth8bits;
}

