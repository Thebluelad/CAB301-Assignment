#include <ctime>
#include <iostream>
#include <random>
#include <fstream>
#include <math.h>
#include <sys/time.h>

using namespace std;

int select(int a[], int l, int m, int h);
int comparisons = 0;
int total = 0;

//Returns the median value in a given array A of n numbers. This is the kth element, where k = |n/2|, if the array was sorted.
int bruteForceMedian(int a[], int n)
{
    int k = ceil(n/2);

    for (int i = 0; i <= n-1; i++)
    {
	int numSmaller = 0;
	int numEqual = 0;
	for (int j = 0; j <= n-1; j++)
	{
	    comparisons++;
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
    return 42;
}

int median(int a[], int n)
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
    return 0;
}

int * generateArray(int n, int seed)
{
    srand(time(NULL) * seed^clock());
    int a[n];
    
    for(int i = 0; i < n; i++)
    {
	int randGenerated = rand() % 10;
	a[i] = randGenerated;
	cout << randGenerated << " ";
	cout << a[i] << endl;
    }
    cout << endl;
    
    return a;
}

void generateArray2(int *a, int n, int seed)
{
    srand(time(NULL) * seed^clock());
    for(int i = 0; i < n; i++)
    {
	int randGenerated = rand();
	a[i] = randGenerated;
//	cout << randGenerated << " ";
//	cout << a[i] << endl;
    }
//    cout << endl;
}


int main()
{
    int n = 10000;
    int numTests = 50;
    int median;
    int *p;
    for (int j = 0; j <= n; j += 500)
    {
	for(int f = 0; f < numTests; f++)
	{
	    int generated[j];
	    p = generated;
	    generateArray2(p, j, f * j);
//	    clock_t begin = clock();
	    median = bruteForceMedian(p, j);
//	    clock_t end = clock();
	    
//	    double elapsed_secs = double(end - begin);
//	    cout << j << "," << elapsed_secs << endl;
	    

//	    for (int i = 0; i < n; i++)
//	    {
//		cout << *(p + i) << " ";
//	    }
//	    cout << endl;
	    total += comparisons;
	    comparisons = 0;
	}
	cout << j << "," << total/numTests << endl;
	total = 0;
    }
    return 0;
}
