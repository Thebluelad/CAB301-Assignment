#include <ctime>
#include <iostream>
#include <random>
#include <fstream>
#include <math.h>
#include <sys/time.h>

using namespace std;

int main()
{
    int n = 1000;
    int numTests = 5;
    int median;
    int *p;
    for (int j = 10; j <= n; j += 10)
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
	    cout << j << "," << comparisons << endl;

//	    for (int i = 0; i < n; i++)
//	    {
//		cout << *(p + i) << " ";
//	    }
//	    cout << endl;

	    comparisons = 0;
	}
    }
    return 0;
}
