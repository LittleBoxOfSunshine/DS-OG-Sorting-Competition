#pragma once

#include "Globals.h"
#include "Bucket.h"

class BucketSupplier
{
private:
     long size;

public:

	Bucket* buckets;

	//Initialize defaults
	BucketSupplier()
	{
		size = 0L;
		buckets = 0L;
	}

	//prepares buckets for use in sorting (creates/clears them)
    void build( long sizes){
		size = sizes;
		//if this is first time being run, allocate array
		if (!buckets){
			//Enforce a maximum amount of ram to be used
			if (size > MAX_BUCKET_RESERVE)
				size = MAX_BUCKET_RESERVE;
			//allocate memory
			buckets = new Bucket[size];
		}
		//initilize all buckets
		for (int i = 0; i < size; i++){
			buckets[i].init();
		}
	}

	//assign a bucket
    void getBucket(Bucket* &bucketPointer,  long &lastIndex){
		lastIndex += THREAD_COUNT;
        if (lastIndex > size)
            std::cout << lastIndex << "\t" << size << std::endl;
		bucketPointer = &buckets[lastIndex];
	}

	~BucketSupplier()
	{
		delete[] buckets;
	}
};
