#include<cstdio>
#include<iostream>
#include<time.h>
#include<math.h>
#include<windows.h>
#include<cstdlib>
using namespace std;
void gen(double *m1,double *m2,long long n)
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			m1[i*n+j] = double(j+1)/(i+1);
    for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		    m1[i*n+j] = double(i+1)/(j+1);
}
void solve(double *m1,double *m2,long long n)
{       
	LARGE_INTEGER Start, Stop; 
	double *ret = new double[n*n];

	printf("Average time for one interation for matrix %ix%i\n",n,n);

	QueryPerformanceCounter(&Start); 
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int c=0;c<n;c++)
				ret[i*n+j] += m1[i*n+c]*m2[c*n+j];
	QueryPerformanceCounter(&Stop);

	printf ("Without transpose:%lf\n", ( Stop.QuadPart - Start.QuadPart ) / pow((double)n, 3));

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			double c = m2[i*n+j];
			m2[i*n+j] = m2[j*n+i];
			m2[j*n+i] = c;
		}

	QueryPerformanceCounter(&Start);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int c=0;c<n;c++)
				ret[i*n+j] += m1[i*n+c]*m2[j*n+c];
    QueryPerformanceCounter(&Stop);

	printf ("With transpose:   %lf\n", ( Stop.QuadPart - Start.QuadPart ) / pow((double)n, 3));

   
   
	delete [] ret;       
}
void test()
{
	int min,max,step;
	printf("Enter min, max, step\n");
	scanf("%i%i%i",&min,&max,&step);
	for(long long n = min;n <= max;n+=step)
	{
		double *m1 = new double[n*n];
		double *m2 = new double[n*n];
		gen(m1,m2,n);
		solve(m1,m2,n);
		delete [] m1;
		delete [] m2;
	}
}
		 
int main()
{
	test();
	return 0;
}
		
						

	
	