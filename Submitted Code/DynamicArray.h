#pragma once

#include "SmartArray.h"

class DynamicArray : public SmartArray
{
public:
	int currentCapacity;
    static const int MAX_FREE_SPACE = 10;
public:
	DynamicArray();
	DynamicArray(int _length, Bucket** elements);
	void clear();
	void add(Bucket* element);
	void add(Bucket* element, int index);
	int length();
	Bucket* get(const int index);
	DynamicArray& operator=(DynamicArray& page);
};
