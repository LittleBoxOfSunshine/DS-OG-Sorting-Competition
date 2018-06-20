#include "DynamicArray.h"

DynamicArray::DynamicArray() : SmartArray(this->MAX_FREE_SPACE) {
	currentCapacity = 0;
}

DynamicArray::DynamicArray(int _length, Bucket** elements) : SmartArray(_length + this->MAX_FREE_SPACE, elements) {
	currentCapacity = _length;
}

void DynamicArray::clear() {
	this->_length = this->MAX_FREE_SPACE;
	this->currentCapacity = 0;
	delete[] this->elements;
	this->elements = new Bucket*[this->_length];
}

void DynamicArray::add(Bucket* element) {
		this->_length += this->MAX_FREE_SPACE;
		Bucket** larger = new Bucket*[this->_length];
		for (int i = 0; i < this->currentCapacity; i++)
			larger[i] = this->elements[i];
		delete[] this->elements;
		this->elements = larger;
	this->elements[this->currentCapacity] = element;
	this->currentCapacity++;
}

void DynamicArray::add(Bucket* element, int index) {
	if (this->currentCapacity > 0 && index < currentCapacity){
			this->add(this->elements[currentCapacity - 1]);
		for (int i = this->currentCapacity - 2; i > index; i--){
			this->elements[i] = this->elements[i - 1];
		}
		this->elements[index] = element;
    }
    else
		this->add(element);
}

int DynamicArray::length() {
	return this->currentCapacity;
}

Bucket* DynamicArray::get(const int index) {
	if (index < this->currentCapacity && index >= 0)
		return this->elements[index];
	else if (index == 0)
        return 0;
}

DynamicArray& DynamicArray::operator=(DynamicArray &page) {
	if (this == &page) {
		delete[] this->elements;
		this->_length = page._length;
		this->currentCapacity = page.currentCapacity;
		this->elements = new Bucket*[this->_length];
		for (int i = 0; i < this->_length; i++)
			this->elements[i] = page.operator[](i);
	}
	return *this;
}

///////////////////

SmartArray::SmartArray(int _length) {
	this->_length = _length;
	this->elements = new Bucket*[_length];
}

SmartArray::SmartArray(int _length, Bucket** elements) {
	this->_length = _length;
	this->elements = new Bucket*[_length];
	for (int i = 0; i < _length; i++)
		this->elements[i] = elements[i];
}

SmartArray::SmartArray(SmartArray& sarray) {
	this->_length = sarray.length();
	this->elements = new Bucket*[_length];
	for (int i = 0; i < _length; i++)
		this->elements[i] = sarray[i];
}

int SmartArray::length() {
	return this->_length;
}

SmartArray::~SmartArray() {
	delete[] elements;
}

Bucket*& SmartArray::operator[](const int index) {
        return this->elements[index];
}
