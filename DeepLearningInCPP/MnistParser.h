/*************************************************************************************/
/// 
/// @file MnistParser.h 
/// 
/// @brief  This file is a header file for MnistParser class that parses the mnist database's file
///		into something that we can use
/// 
/// @note assumes that for every data set there is a label file
/// 
/// @note All the integers in the files are stored in the MSB first (high endian) format used by most non-Intel processors.
///  Users of Intel processors and other low-endian machines must flip the bytes of the header.
/// 
/// @warning the vector for a image is dynamically allocated
/// 
/// @warning Currently designed to only process 32 bit unsigned int data
/// 
/// @todo convert this into template
/// 
/// It contains all of the declaration of the member funciton of FileWriter class.
/// It contains all of the inline funcitons defination of  the member funciton of FileWriter class 
///
/*************************************************************************************/
#pragma once

class MnistParser
{
public:
	MnistParser(std::string a_labelFilePath, std::string a_setFilePath); // constructor
	~MnistParser(); // deconstructor
	
	const std::vector<uint8_t>* GetActualLabels() const; // getter function
	const std::vector<std::vector<uint8_t>*>* GetDataSet() const; // getter function
	const uint32_t GetTotalLabelNum() const; // getter function
	const uint32_t GetTotalImgNum() const; // getter function
	const uint8_t GetImgRow() const; // getter function
	const uint8_t GetImgCol() const; // getter function

private:
	// private member function
	void ParseMinstlabelFile(std::string& a_labelFilePath);
	void ParseMinstSetFile(std::string& a_dataSetFilePath);
	uint32_t SwapEndian(uint32_t a_val); // convert number form MSB endian to LSB endian

private:
	// private data member
	std::vector<uint8_t> m_actualLabel; // pointer to the vector containing the actual label
	std::vector<std::vector<uint8_t>*> m_dataSet; // pointer to the vector containg the train/test set

	uint32_t m_totalLableNum; // total number of labels
	uint32_t m_totalImgNum; // total number of images
	uint32_t m_imgRow; // number of rows of pixels in a image 
	uint32_t m_imgCol; // number of columns of pixels in a image
};

/// 
/// @brief constructor
/// 
/// parses the file to extract the data contained in the label and dataset file
/// 
/// @param a_labelFilePath file path to the MNIST label file
/// @param a_setFilePath file path to the MNIST dataset lfile
/// 
inline MnistParser::MnistParser(std::string a_labelFilePath, std::string a_setFilePath)
{
	ParseMinstlabelFile(a_labelFilePath);
	ParseMinstSetFile(a_setFilePath);
}

/// 
/// @brief getter function to get the pointer to the vector containing the actual labels
/// 
/// @return pointer to the vector containing the actual labels
/// 
inline const std::vector<uint8_t>* MnistParser::GetActualLabels() const
{
	return &m_actualLabel;
}

/// 
/// @brief getter function to get the pointer to the vector containing the data set
/// 
/// @return pointer to the vector containing the data sets
/// 
inline const std::vector<std::vector<uint8_t>*>* MnistParser::GetDataSet() const
{
	return &m_dataSet;
}

/// 
/// @brief getter function to get total number of labels
/// 
/// @return total number of labels
/// 
inline const uint32_t MnistParser::GetTotalLabelNum() const
{
	return m_totalLableNum;
}

/// 
/// @brief getter function to get total number of images count
/// 
/// @return total number of images count
/// 
inline const uint32_t MnistParser::GetTotalImgNum() const
{
	return m_totalImgNum;
}

/// 
/// @brief getter function to get total number of row in a image
/// 
/// @return total number of row in a image
/// 
inline const uint8_t MnistParser::GetImgCol() const
{
	return m_imgCol;
}

/// 
/// @brief getter function to get total number of columns in a image
/// 
/// @return total number of columns in a image
/// 
inline const uint8_t MnistParser::GetImgRow() const
{
	return m_imgRow;
}