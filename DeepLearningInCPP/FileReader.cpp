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
/// @param a_fileName: name of the file to be opened
/// @param a_openIstream: true if open as istream, false if open as ostream
/// 
FileReader::FileReader(std::string a_fileName)
{
	// opening the file
	m_iFile.open(a_fileName, std::ios::binary);

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
/// @brief GetNextLine gets the next line from the source file.  
/// 
/// @param a_line is the string where the extracted line is stored
/// 
/// @returns true if there was one.
/// 
bool FileReader::GetNextLine(std::string& a_line)
{
	// If there is no more data, return false.
	if (CheckEOF())
	{
		return false;
	}

	std::getline(m_iFile, a_line);

	// Return indicating success.
	return true;
}

