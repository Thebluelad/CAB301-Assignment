#include <ctime>
#include <iostream>
#include <random>
#include <fstream>
#include <math.h>
#include <sys/time.h>

using namespace std;

//Constants
const int STARTN = 0;
const int FINISHN = 10000;
const int INCREMENT = 50;
const int NUMTESTS = 100;

//Global Variables
int comparisonsp = 0;
int comparisonsb = 0;
long totalb = 0;
long totalp = 0;
double totalTimeb = 0;
double totalTimep = 0;

//Function Declarations
int bruteForceMedian(int a[], int n);
int partitionMedian(int a[], int n);
int select(int a[], int l, int m, int h);
int partition(int a[], int l, int h);
int select(int a[], int l, int m, int h);
void generateArray(int *a, int n, int seed);
void functionalTests();
void runComparisonsAndTimeData();

//Output Files
ofstream testLog;
ofstream graphLog;

//Returns the median value in a given array A of n numbers. This is the kth element, where k = |n/2|, if the array was sorted.
int bruteForceMedian(int a[], int n)
{
    int k = ceil(n/2.0);

    for (int i = 0; i <= n-1; i++)
    {
	int numSmaller = 0;
	int numEqual = 0;
	for (int j = 0; j <= n-1; j++)
	{
	    comparisonsb++;
	    if (a[j] < a[i])
	    {
		numSmaller++;
	    }
	    else
	    {
		if (a[j] == a[i])
		{
		    numEqual++;
		}
	    }
	}
	if (numSmaller < k && k <= (numSmaller + numEqual))
	{
	    return a[i];
	}

    }
    //return 42;
}

int partitionMedian(int a[], int n)
{
    if (n == 1)
    {
	return a[0];
    }
    else
    {
	return select(a, 0, floor(n/2), n-1);
    }
}

int partition(int a[], int l, int h)
{
    int pivotval = a[l];
    int pivotloc = l;
    for (int j = l + 1; j <= h; j++)
    {
	if (a[j] < pivotval)
	{
	    //This is where the comparisons should happen
	    comparisonsp++;
	    pivotloc++;
	    //Swaps elements around the pivot
	    int temp = a[pivotloc];
	    a[pivotloc] = a[j];
	    a[j] = temp;
	}
    }
    //Put pivot element in place
    int temp = a[l];
    a[l] = a[pivotloc];
    a[pivotloc] = temp;
    return pivotloc;

}

int select(int a[], int l, int m, int h)
{
    //Returns the value at index m in array slice a[l..h], if the slice were sorted into nondecreasing order.
    int pos = partition(a, l, h);
    if (pos == m)
    {
	return a[pos];
    }
    if (pos > m)
    {
	return select(a, l, m, pos - 1);
    }
    if (pos < m)
    {
	return select(a, pos + 1, m, h);
    }
    //return 0;
}

void generateArray(int *b, int *a, int n, int seed)
{
    srand(time(NULL) * seed^clock());
    for(int i = 0; i < n; i++)
    {
	int randGenerated = rand() % 10000;
	a[i] = randGenerated;
	b[i] = randGenerated;
//	cout << randGenerated << ",";
    }
  //  cout << endl << endl;
}


int main()
{
    functionalTests();
    //runComparisonsAndTimeData();
    return 0;
}

void runComparisonsAndTimeData()
{
    graphLog.open("graphLog.csv");

    for (int j = STARTN; j <= FINISHN; j += INCREMENT)
    {
	int medianPartition;
	int medianBruteForce;
	for (int i = 0; i < 1; i++)
	{
	    for(int f = 0; f < NUMTESTS; f++)
	    {
		int *p;
		int *b;
		int generated[j];
		p = generated;
		b = generated;
		generateArray(b, p, j, f * j);
		clock_t beginb = clock();
		medianBruteForce = bruteForceMedian(b, j);
		clock_t endb = clock();
		clock_t beginp = clock();
		medianPartition = partitionMedian(p, j);
		clock_t endp = clock();
		double elapsedb = double(endb - beginb);
		double elapsedp = double(endp - beginp);
		totalp += comparisonsp;
		totalb += comparisonsb;
		totalTimep += elapsedp;
		totalTimeb += elapsedb;
		comparisonsb = 0;
		comparisonsp = 0;
	    }
	    graphLog << j << "," << totalb/NUMTESTS << "," << totalTimeb/NUMTESTS << "," << medianBruteForce << ","  << totalp/NUMTESTS << "," << totalTimep/NUMTESTS << "," << medianPartition << endl;
	    medianPartition = 0;
	    medianBruteForce = 0;
	    totalp = 0;
	    totalb = 0;
	    totalTimep = 0;
	    totalTimeb = 0;
	}
	
    }
}

void functionalTests()
{
    testLog.open("testLog.txt");

    testLog << "Median Function Tests" << endl << endl;
    
    testLog << "Test 1 - Basic Array Even" << endl;
    int basicArrayEven[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    testLog << "Testing: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10" << endl;
    testLog << "Brute force expects 5: " << bruteForceMedian(basicArrayEven, 10) << endl;
    testLog << "PartitionMedian expects 6: " << partitionMedian(basicArrayEven, 10) << endl << endl;

    testLog << "Test 2 - Basic Array Odd" << endl;
    int basicArrayOdd[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    testLog << "Testing: 1, 2, 3, 4, 5, 6, 7, 8, 9" << endl;
    testLog << "Brute force expects 5: " << bruteForceMedian(basicArrayOdd, 9) << endl;
    testLog << "PartitionMedian expects 5: " << partitionMedian(basicArrayOdd, 9) << endl << endl;
    
    testLog << "Test 3 - Reverse Array Odd" << endl;
    int reverseArrayOdd[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    testLog << "Testing: 9, 8, 7, 6, 5, 4, 3, 2, 1" << endl;
    testLog << "Brute force expects 5: " << bruteForceMedian(reverseArrayOdd, 9) << endl;
    testLog << "PartitionMedian expects 5: " << partitionMedian(reverseArrayOdd, 9) << endl << endl;

    testLog << "Test 4 - Reverse Array Even" << endl;
    int reverseArrayEven[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    testLog << "Testing: 10, 9, 8, 7, 6, 5, 4, 3, 2, 1" << endl;
    testLog << "Brute force expects 5: " << bruteForceMedian(reverseArrayEven, 10) << endl;
    testLog << "PartitionMedian expects 6: " << partitionMedian(reverseArrayEven, 10) << endl << endl;

    testLog << "Test 5 - Duplicate Numbers Even" << endl;
    int duplicateArrayEven[10] = {1, 2, 4, 4, 5, 6, 7, 8, 9, 10};
    testLog << "Testing: 1, 2, 4, 4, 5, 6, 7, 8, 9, 10" << endl;
    testLog << "Brute force expects 5: " << bruteForceMedian(duplicateArrayEven, 10) << endl;
    testLog << "PartitionMedian expects 6: " << partitionMedian(duplicateArrayEven, 10) << endl << endl;

    testLog << "Test 6 - Duplicate Numbers Odd" << endl;
    int duplicateArrayOdd[9] = {1, 2, 4, 4, 5, 6, 7, 8, 9};
    testLog << "Testing: 1, 2, 4, 4, 5, 6, 7, 8, 9" << endl;
    testLog << "Brute force expects 5: " << bruteForceMedian(duplicateArrayOdd, 9) << endl;
    testLog << "PartitionMedian expects 5: " << partitionMedian(duplicateArrayOdd, 9) << endl << endl;

    testLog << "Test 7 - Random Values Odd" << endl;
    int randomArray[9] = {2, 3, 6, 5, 8, 7, 1, 9, 4};
    testLog << "Testing: 2, 3, 6, 5, 8, 7, 1, 9, 4" << endl;
    testLog << "Brute force expects 5: " << bruteForceMedian(duplicateArrayOdd, 9) << endl;
    testLog << "PartitionMedian expects 5: " << partitionMedian(duplicateArrayOdd, 9) << endl << endl;

    testLog << "Array Generator Tests" << endl << endl;

    testLog.close();
}


