#pragma once
#include <iostream>

class Bucket;

class SmartArray
{
public:
	int _length;
	Bucket** elements;
public:
	SmartArray(int _length);
	SmartArray(int _length, Bucket** elements);
	SmartArray(SmartArray& sarray);
	int length();
	~SmartArray();
	Bucket*& operator[](const int index);
};
