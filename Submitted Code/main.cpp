// Sort V2.0.cpp : Defines the entry point for the console application.
//

#include "Sort.h"
#include "DynamicArray.h"
#include "Bucket.h"

using namespace std;

int main(int argc, char* argv[])
{

    //declare 2 time points
    std::chrono::time_point<std::chrono::system_clock> start, end;

    SortingCompetition sort("s.txt");
    sort.readData();

    for(int i=0; i<30; i++){
    sort.prepareData();
    std::cout << "Begin Sorting...\n";
    start = std::chrono::system_clock::now();
    sort.sortData();
    end = std::chrono::system_clock::now();
    std::cout << "Done Sotring!";

    //subtract end from beginning to get number of seconds elapsed
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time =
        std::chrono::system_clock::to_time_t(end);

    //output the duration.
    std::cout << "finished computation at " <<
        std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    sort.outputData("test.txt");

    return 0;
}
