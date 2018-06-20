#include <algorithm>

#pragma once

//GLOABL CONSTANTS:
static const int KEY_LENGTH = 8*13;
static const int DIGITS = 255;
static const int THREAD_COUNT = 1;
static const long BUCKETS_PER_GB = 50000;
static const long MAX_RAM_RESERVE = 2L;
static const long MAX_BUCKET_RESERVE = MAX_RAM_RESERVE*BUCKETS_PER_GB;
//END GLOBAL CONSTANTS
