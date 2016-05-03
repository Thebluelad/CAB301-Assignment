#include <ctime>
#include <iostream>
#include <random>
#include <fstream>
#include <math.h>

using namespace std;

int select(int a[], int l, int m, int h);

//Returns the median value in a given array A of n numbers. This is the kth element, where k = |n/2|, if the array was sorted.
int bruteForceMedian(int a[], int n)
{
    int k = abs(n/2);

    for (int i = 0; i < n-1; i++)
    {
	int numSmaller = 0;
	int numEqual = 0;
	for (int j = 0; j < n-1; j++)
	{
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




int * generateArray(int n)
{
    int a[n];
    int min = 0;
    int max = 10;

    std::random_device r;
    std::mt19937 rand(r());
    std::uniform_int_distribution<int> uniform(min,max);

    for(int i = 0; i < n; i++)
    {
	a[i] = uniform(rand);
    }
    return a;
}

int main()
{
    int n = 100;
    int *p = generateArray(n);
    for (int i = 0; i < n; i++)
    {
	cout << *(p + i) << ",";
    }
    cout << endl;
    cout << bruteForceMedian(p, n) << endl;
    cout << median(p, n) << endl;
    return 0;
}
