///-------------------------------------------------------------------------------------------------
// file:	FileHandling.cpp
//
// summary:	Implements the file handling class
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FileHandling.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. </summary>
///
/// <author>	Allyn Vo </author>	
////////////////////////////////////////////////////////////////////////////////////////////////////

FileHandling::FileHandling() {}

// Input: Contents of input.csv -- Opens the file and reads the values into matrix values

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Opens the file and reads the values into matrix values. </summary>
///
/// <author>	Allyn Vo </author>	
///
/// <param name="data">	[in,out] The data. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FileHandling::openFile(ClassData &data)
{
	using namespace std;
	ifstream myFile;
	string line;

	myFile.open(data.fileName);											// Open the file

	if (myFile.is_open()) {												/* Valid File: Begin reading data form the file */
		vector<std::string> columns;

		while (getline(myFile, line)) {									/* While the file has more data */
			istringstream cell(line);
			string distance;
			while (getline(cell, distance, ',')) {
				columns.push_back(distance);
			}
			data.values.push_back(columns);								// Store data
			columns.clear();
		}

	}
	myFile.close();
}

// Input: Contents of input.csv -- Splits the values into x and y coords

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sorts graph. Main sorter for standard graphs.</summary>
///
/// <author>	Allyn Vo </author>	
///
/// <param name="data">	[in,out] The data. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void FileHandling::sortGraph(ClassData &data)
{
	std::vector<float> xdatatemp;
	std::vector<float> ydatatemp;
	float xCoord = 0;
	float yCoord = 0;

	data.getLabels();

 
	for (int i = 1; i < (signed)data.values.size(); i++)					// OLD: for (int i = 1; i < (data.values.size() - 1); i++)
	{																	// Columns
		int nodeClass = 
			stoi(data.values[i][(data.values[0].size() - 1)]);          // Get the class of the node
		if (nodeClass > data.numOfClasses)                              // Get the highest class number
			data.numOfClasses = nodeClass;
		data.classNum.push_back(nodeClass);                             // Add to vector of class numbers

		for (int j = 1; j < ((signed)data.values[i].size() - 1); j++)			// Rows
		{                                          
			if (xdatatemp.size() <= ydatatemp.size())					// Get X-coords
			{                                        
				xCoord = stof(data.values[i][j]);
				xdatatemp.push_back(xCoord);
				if (xCoord > data.xmax)
					data.xmax = xCoord;
			}
			else
			{                                                            // Get y coords
				yCoord = stof(data.values[i][j]);
				ydatatemp.push_back(yCoord);
				if (yCoord > data.ymax)
					data.ymax = yCoord;
			}
		}
		if (xdatatemp.size() != ydatatemp.size())						// Duplicate last pair if odd # of columns
		{                                            
			ydatatemp.push_back(xCoord);
			if (yCoord > data.ymax)  // Get y-max
				data.ymax = yCoord;
		}
		data.xdata.push_back(xdatatemp);                                // Add line plot coords
		data.ydata.push_back(ydatatemp);
		xdatatemp.clear();                                              // Clear for the next plot line
		ydatatemp.clear();
	}
}

void FileHandling::normalizeData(ClassData &data)
{
	// Y Normalization
	std::vector<float> minYcol;
	std::vector<float> maxYcol;
	std::vector<float> temp;

	std::vector<std::vector<float> > convertedValues; // NEW


	float min = 0;
	float max = 0;

 
	for (int j = 0; j < (signed)data.ydata[0].size(); j++) {                                               // Gets the min and max of every column
		for (int i = 0; i < (signed)data.ydata.size(); i++) {
			if (data.ydata[i][j] > max) {
				max = data.ydata[i][j];
			}
			if (data.ydata[i][j] < min) {
				min = data.ydata[i][j];
			}
		}
		
	}
	minYcol.push_back(min);
	maxYcol.push_back(max);
	max = 0;
	min = 0;

 
	for (int i = 0; i < (signed)data.ydata.size(); i++) {                                                  // Normalize the data from 0 - 1
		for (int j = 0; j < (signed)data.ydata[0].size(); j++) {
			float original = data.ydata[i][j];
			float currentMin = minYcol[0];
			float currentMax = maxYcol[0];
			float converted = (original - currentMin) / (currentMax - currentMin);

			temp.push_back(converted);
		}
		convertedValues.push_back(temp);
		temp.clear();
	}
	data.ydata.clear();
	data.ydata = convertedValues;																	// Fill ydata coordinates with normalized data  
	convertedValues.clear();
	//data.xmax = data.ydata[0].size();																// Change xMax and yMax to normalized data
	data.ymax = 1;

	// X Normalization after this point
	std::vector<float> minXcol;
	std::vector<float> maxXcol;
	temp.clear();

	convertedValues.clear();


	min = 0;
	max = 0;

 
	for (int j = 0; j < (signed)data.xdata[0].size(); j++) {                                               // Gets the min and max of every column
		for (int i = 0; i < (signed)data.xdata.size(); i++) {
			if (data.xdata[i][j] > max) {
				max = data.xdata[i][j];
			}
			if (data.xdata[i][j] < min) {
				min = data.xdata[i][j];
			}
		}

	}
	minXcol.push_back(min);
	maxXcol.push_back(max);
	max = 0;
	min = 0;

 
	for (int i = 0; i < (signed)data.xdata.size(); i++) {                                                  // Normalize the data from 0 - 1
		for (int j = 0; j < (signed)data.xdata[0].size(); j++) {
			float original = data.xdata[i][j];
			float currentMin = minXcol[0];
			float currentMax = maxXcol[0];
			float converted = (original - currentMin) / (currentMax - currentMin);

			temp.push_back(converted);
		}
		convertedValues.push_back(temp);
		temp.clear();
	}
	data.xdata.clear();
	data.xdata = convertedValues;																	// Fill ydata coordinates with normalized data  
	convertedValues.clear();
	//data.xmax = data.ydata[0].size();																// Change xMax and yMax to normalized data
	data.xmax = 1;
}

void FileHandling::normalizeDataV2(ClassData &data)
{
	std::vector<float> minYcol;
	std::vector<float> maxYcol;
	std::vector<float> temp;

	//float Ymax = 0;

	std::vector<std::vector<float> > convertedValues; // NEW


	float min = 0;
	float max = 0;

 
	for (int j = 0; j < (signed)data.ydata[0].size(); j++) {                                               // Gets the min and max of every column
		for (int i = 0; i < (signed)data.ydata.size(); i++) {
			if (data.ydata[i][j] > max) {
				max = data.ydata[i][j];
			}
			if (data.ydata[i][j] < min) {
				min = data.ydata[i][j];
			}
			//if (data.ydata[i][j] > Ymax) {
			//	Ymax = data.ydata[i][j];
			//}
		}
	}
	minYcol.push_back(min);
	maxYcol.push_back(max);
	max = 0;
	min = 0;

	float original;
	float currentMin;
	float currentMax;
	float converted;

 
	for (int i = 0; i < (signed)data.ydata.size(); i++) {                                                  // Normalize the data from 0 - 1
		for (int j = 0; j < (signed)data.ydata[0].size(); j++) {
			original = data.ydata[i][j];
			currentMin = minYcol[0];
			currentMax = maxYcol[0];
			converted = (original - currentMin) / (currentMax - currentMin);

			temp.push_back(converted);
		}
		convertedValues.push_back(temp);
		temp.clear();
	}
	data.ydata.clear();
	data.ydata = convertedValues;																	// Fill ydata coordinates with normalized data  
	convertedValues.clear();
	data.xmax = data.ydata[0].size();																// Change xMax and yMax to normalized data
	data.ymax = 1;
	minYcol.clear();
	maxYcol.clear();
}