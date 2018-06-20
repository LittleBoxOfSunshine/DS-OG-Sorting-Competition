#include "Bucket.h"
#include <string>

void getBucket(Bucket* &ptr,  long &index, unsigned  long &l);
void ReverseBytes(unsigned long* start, int size);
Bucket* temp_Bucket;

Bucket::Bucket()
{
	children = new DynamicArray;
	counts = new int[THREAD_COUNT];
}

//initialize bucket for use (allows resets in prepare without delay reallocating memory)
void Bucket::init(){
	children->clear();
	memset(counts, 0L, THREAD_COUNT*sizeof(int));
}

 long Bucket::getLabel(){
	return this->label;
}

//get address of child bucket
void Bucket::getChild(Bucket* &ptr, int &index){
	ptr = this->children->get(index);
}
//same as get, but assigns a bucket if the requested bucket is currently null
//and by doing so "inserts" the digit as a child
void Bucket::insertChild(unsigned  long labelnew, Bucket* &ptr,  long &lastI){
	int i = 0;
	for (i; i < children->length(); i++){
        if (children->get(i)->label <= labelnew)
			break;
    }
    if (children->length()<1 || (i>=children->length() || children->get(i)->label != labelnew)){
		getBucket(temp_Bucket, lastI, labelnew);
        children->add(temp_Bucket, i);
	}
	ptr = children->get(i);
}

//TEMP GETTER FOR TESTING
Bucket* Bucket::getChild(int index){
	return this->children->get(index);
}

//return summation of number of times each thread logged the word
void Bucket::getCount(int &count){
	//sum up counts
	for (int i = 0; i < THREAD_COUNT; i++){
		count += counts[i];
	}
}

//log an occurence of word at thread's reserved counter (prevent data race)
void Bucket::add(const int &index){
	this->counts[index]++;
}

Bucket::~Bucket()
{
	delete children;
	delete[] counts;
}
