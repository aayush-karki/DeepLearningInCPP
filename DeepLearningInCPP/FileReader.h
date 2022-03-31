/*************************************************************************************/
/// 
/// @file FileReader.h 
/// 
/// @brief  This file is a header file for FileReader class.
/// 
/// It contains all of the declaration of the member funciton of FileReader class.
/// It contains all of the inline funcitons defination of  the member funciton of FileReader class 
///
/*************************************************************************************/
#pragma once

#include <fstream>

///
/// @class FileReader "FileReader.h"
/// 
/// @brief This is a class allows to read a file
///	
/// FileReader class deals entierly with reading files
/// 
/// 
class FileReader
{
public:
	FileReader(std::string a_FilePath); // constructor
	~FileReader(); // deconstructor
	bool ExtractFromFile(char* a_extracted, std::size_t a_sizeToExtract); // extracts a number from file
	bool GetNextLine(std::string& a_line); // extracts a number from file
	bool CheckEOF();

private:
	std::ifstream m_iFile; // input  File
};

/// 
/// @brief CheckEOF checks if the file pointer is currently at end of file
/// 
/// @returns true if file pointer is pointed at end of file
/// 
inline bool FileReader::CheckEOF()
{
	return m_iFile.eof();
}