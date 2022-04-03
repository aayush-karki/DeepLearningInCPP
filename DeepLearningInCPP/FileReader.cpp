/*************************************************************************************/
/// 
/// @file FileReader.cpp 
/// 
/// @brief  This file is a source file for FileReader class.
/// 
/// It contains all of the defination of  the member funciton.
///
/// 
/*************************************************************************************/

#include "stdafx.h"
#include "FileReader.h"

/// 
/// @brief constructor, Opens the file.
///
/// @param a_FilePath: name of the file to be opened
/// @param a_openIstream: true if open as istream, false if open as ostream
/// 
FileReader::FileReader(std::string a_FilePath)
{
	// opening the file
	m_iFile.open(a_FilePath, std::ios::binary);

	// checking if the file opened or not
	if (!m_iFile)
	{
		throw("Could not open!!" );
	}
}

/// 
/// @brief deconstructor, Closes the file.
///
FileReader::~FileReader()
{
	// closing the file 
	m_iFile.close();
}

/// 
/// @brief ExtractFromFile reads from the file and extract a nubmer
///  
/// @param a_extracted memory address of place to store the extracted data
/// @param a_sizeToExtract total number of bytes to extract
/// 
/// @returns true if successfull
///
bool FileReader::ExtractFromFile(char* a_extracted, std::size_t a_sizeToExtract)
{
	if (CheckEOF())
	{
		return false;
	}
	m_iFile.read(a_extracted, a_sizeToExtract);
	return true;
}
 
///@brief GetNextLine gets the next line from the source file.  
///
///@param a_line is the string where the extracted line is stored
///
///@returns true if there was one.
 
bool FileReader::GetNextLine(std::string& a_line)
{
	// If there is no more data, return false.
	if (CheckEOF())
	{
		return false;
	}

	std::getline( m_iFile, a_line);
	return true;
}