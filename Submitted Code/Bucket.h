#pragma once

#include "Globals.h"
#include "DynamicArray.h"
#include <cstring>

class Bucket
{
public:
	DynamicArray* children;
	int* counts;
    unsigned long label;

	Bucket();
	//initialize bucket for use (allows resets in prepare without delay reallocating memory)
	void init();
	 long getLabel();
	//get adress of child bucket
	void getChild(Bucket* &ptr, int &index);
	//same as get, but assigns a bucket if the requested bucket is currently null
	//and by doing so "inserts" the digit as a child
	void insertChild(unsigned  long labelnew, Bucket* &ptr,  long &lastI);

	Bucket* getChild(int index);


	//log an occurence of word at thread's reserved counter (prevent data race)
	void add(const int &index);
	//return summation of number of times each thread logged the word
	void getCount(int &count);
	~Bucket();
};
