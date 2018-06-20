#include "Sort.h"

 long lastIndex = -1;//Temp holder until threads are implemented
BucketSupplier supply;
vector<char> output_words;
void getBucket(Bucket* &ptr,  long &index, unsigned long &l){
	supply.getBucket(ptr, index);
   // cout << "bucket ptr =" << ptr << endl;
    ptr->label = l;
   // cout << "Label ptr =" << &(ptr->label) << endl;
   // cout << "Label val =" << hex << l << endl;
    //cout << sizeof(ptr) << endl;
    //cout << sizeof(ptr->label) << endl;
}

void ReverseBytes(unsigned long* start, int size)
{
	char *istart = (char*)start;
	char *iend = istart + size;
	std::reverse(istart, iend);
}

SortingCompetition::SortingCompetition(const string& inputFileName){
	inputPath = inputFileName;
	//allocate memory for lookup table
	shortcuts = new Bucket*[KEY_LENGTH];
    words = 0;
}


//change the input file name
void SortingCompetition::setFileName(const string& inputFileName){
	inputPath = inputFileName;
}


bool SortingCompetition::readData(){
	ifstream  input(inputPath);

	//Load into dynamic storage
	vector<string> tempWords;
	//load each word from file into tempwords
	string tempWord;
	while (input >> tempWord){
		tempWords.push_back(string(tempWord));
		//cout << tempWord << endl;
	}

	numWords = tempWords.size();

	//Load into contiguous block from vector
	//max of 99 chars + 1 byte for length for each word
    words_original = new char[KEY_LENGTH * numWords];
	memset(words_original, 32, KEY_LENGTH * numWords);
	//copy words into array
	for (int i = 0; i < numWords; i++){
		for (unsigned int p = 0; p < tempWords[i].length(); p++){
			words_original[(i + 1)* KEY_LENGTH - tempWords[i].length() + p] = (tempWords[i]).at(p);
			//cout << words_original[(i + 1)* KEY_LENGTH - tempWords[i].length() + p];
		}
        //cout << "TEST" << endl;
		_label = (unsigned  long*)(words_original + (KEY_LENGTH*i));
        //cout << hex << *(_label) << endl;
       // cout << digitToChar(*(_label)) << endl;
        for(int z=0; z<13; z++)
            ReverseBytes(_label+z, 8);
       // cout << digitToChar(*(_label)) << endl;
	}

	return true;
}

//copy the data from the original data structure
//into a second location that will be used for sorting.
//This will allow you to sort the same data set (with
//the same starting order of elements) multiple times.
//You can then calculate the average of execution times for 
//one data set against one algorithm. 
//No sorting actions can be done in this method.
bool SortingCompetition::prepareData(){
	//copy the words (manipulate bits as loaded at another point)
	if(!words)
        words = new char[KEY_LENGTH * numWords];

	//copy words
	for (int i = 0; i < numWords * KEY_LENGTH; i++){
		words[i] = words_original[i];
	//	cout << words[i];
	}

	//Prebuild buckets (numWords*Key length)
	supply.build(DIGITS * KEY_LENGTH);

	//Build tree and store appropriate pointers in shortcuts
	supply.getBucket(origin, lastIndex);
	origin->label = -100;

	//Create threads

	return true;
}

//sort the data based on the criteria set forth in the
//hand out.
//THIS IS THE FUNCTION THAT WILL BE TIMED.
void SortingCompetition::sortData(){
	for (int i = 0; i < numWords; i++){
		tempSort = origin;
		for (int z = 0; z<KEY_LENGTH / 8; z++){
        _label = (unsigned  long*)(words + (KEY_LENGTH*i + z * 8));
        tempSort->insertChild(*_label, tempSort, lastIndex);
    }
    tempSort->add(0);
	}
}

//using outputFileName, write the "sorted" data structure
//to the file. This will be used to test the validity of
//your sorting algorithm (in other words, did it sort properly?).
void SortingCompetition::outputData(const string& outputFileName){
	output.open(outputFileName);
	
	string prefix("");
	//recurse through tree to write words to file
	display(origin, prefix);
	
    for(int i=output_words.size()-2; i>-1; i--)
        output << output_words[i];

	//save file
	output.close();
}

void SortingCompetition::display(Bucket* bucket, string prefix){
	bool print = true;
	if (bucket->children){
		for ( int i = 0; i < bucket->children->length(); i++){
            print = false;
			display(bucket->getChild(i), prefix + digitToChar(bucket->getChild(i)->label));
		}
	}
    if (print){
		int max=0;
        bucket->getCount(max);
		for (int i = 0; i < max; i++){

            for (int z = 0; z < prefix.length(); z++)
                output_words.push_back(prefix[z]);
             output_words.push_back('\n');
		}
	}
}

string SortingCompetition::digitToChar(unsigned  long i){
	string temp("");
	char* test = (char *)&i;
	for (int z = 0; z < 8; z++){
        if (*(test + z) != 32)
			temp += *(test + z);
    }
	return temp;
}

SortingCompetition::~SortingCompetition(){
	delete[] shortcuts;
}
