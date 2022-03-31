
/*************************************************************************************/
/// 
/// @file FileWriter.h 
/// 
/// @brief  This file is a header file for FileWriter class.
/// 
/// It contains all of the declaration of the member funciton of FileWriter class.
/// It contains all of the inline funcitons defination of  the member funciton of FileWriter class 
///
/*************************************************************************************/
#pragma once

#include <fstream>

///
/// @class FileWriter "FileWriter.h"
/// 
/// @brief This is a class allows to write to a file
///	
/// FileWriter class deals entierly with reading files
/// 
/// 
class FileWriter
{
public:
	FileWriter(std::string a_FilePath); // constructor
	~FileWriter(); // deconstructor
	void WrtiePrectionsToFile(const std::vector<uint8_t>& a_actualOutput, const std::vector<uint8_t>& a_predictedOutput,
		const std::vector<std::vector<uint8_t>>& a_inputSet, uint32_t a_imgRow, uint32_t a_imgCol);
	//bool WrtieAllToFile(std::string& a_line); // writes the tresting result to a file
	
	/// @todo: maybe in the future write a function to plot to a graph
	

private:
	std::ofstream m_oFile; // output  File
};
