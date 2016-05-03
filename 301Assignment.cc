#include <ctime>
#include <iostream>
#include <random>
#include <fstream>

using namespace std;

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
    return 0;
}
