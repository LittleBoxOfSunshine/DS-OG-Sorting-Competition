//Chris Henk
//Eric Smith

#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>

#include "BucketSupplier.h"
#include "Bucket.h"
#include "Globals.h"

using namespace std;

class SortingCompetition
{
private:
	string inputPath;
public:
	char* words_original;
	char* words;
	int numWords;
	Bucket* origin;
	Bucket** shortcuts;
	Bucket* tempSort;
	ofstream output;
	unsigned  long* _label;
	void display(Bucket* bucket, string prefix);
	string digitToChar(unsigned  long c);
	//you are free to determine your own internal
	//implementation with the following stipulations:
	//1) when the prepare method is called, you must make a
	//copy of the original dataset into another instance-level
	//data structure which will be used by the sort method. This will
	//allow for multiple executions of the sort method in order to
	//get better timing data.
	//2) your data structure must be linear (no trees).

	//basic constructor that accepts an input
	//file name
	SortingCompetition(const string& inputFileName);


	//change the input file name
	void setFileName(const string& inputFileName);

	//read the data from the file and store it in
	//a linear data structure.
	//No sorting actions can be done in this method.
	//This includes no duplicate removal or anything else
	//that could make your sorting more efficient later.
	//Literally, the 5th word in the file should be 
	//in the 5th place in your structure. 
	bool readData();

	//copy the data from the original data structure
	//into a second location that will be used for sorting.
	//This will allow you to sort the same data set (with
	//the same starting order of elements) multiple times.
	//You can then calculate the average of execution times for 
	//one data set against one algorithm. 
	//No sorting actions can be done in this method.
	bool prepareData();

	//sort the data based on the criteria set forth in the
	//hand out.
	//THIS IS THE FUNCTION THAT WILL BE TIMED.
	void sortData();

	//using outputFileName, write the "sorted" data structure
	//to the file. This will be used to test the validity of
	//your sorting algorithm (in other words, did it sort properly?).
	void outputData(const string& outputFileName);

	~SortingCompetition();

};
