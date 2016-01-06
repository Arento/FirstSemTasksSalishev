#include<cstdio>
#include<stack>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
void han(int n,FILE* fout)
{
	int cols[3] = {1,2,3};
	if(n%2 == 0)
	{
		cols[1] = 3;
		cols[2] = 2;
	}

	for (int k = 1; k < (1 << n); k++)
    {                
		int h1 = (k &( k - 1)) % 3;
        int h2 = ((k | (k - 1)) + 1) % 3;
        fprintf(fout,"%d -> %d\n",cols[h1], cols[h2]);
    }          
}

void do_step(int x,int y, stack<int>* r,FILE* fout)
{
	if((r+x)->top() > (r+y)->top())
	{
		fprintf(fout,"%i -> %i\n",y+1,x+1);
		(r+x)->push((r+y)->top());
		(r+y)->pop();
	}
	else
	{
		fprintf(fout,"%i -> %i\n",x+1,y+1);
		(r+y)->push((r+x)->top());
		(r+x)->pop();
	}	
}
				
void hanoy(unsigned long long n,FILE* fout)
{
	stack<int> r[3];
	for(int i=0;i<3;i++)
		r[i].push(n+1);
	for(int i=n;i>=1;i--)
		r[0].push(i);
	for(unsigned long long i = 0;i<(1ULL<<n) -1;i++)
	{   
		if(n%2 == 0)
			switch(i%3)
			{
				case 0: do_step(0,1,r,fout);
					    break;
				case 1: do_step(0,2,r,fout);
						break;
				case 2: do_step(1,2,r,fout);
						break;
			}
		else
			switch(i%3)
			{
				case 0: do_step(0,2,r,fout);
						break;
				case 1: do_step(0,1,r,fout);
						break;
				case 2: do_step(1,2,r,fout);
						break;
			}				
	}
}
void rec_han(int n, int from, int to, int dop,FILE* fout)
{

	if (n == 0) 
	{
		return;
	}
    rec_han(n - 1, from, dop, to, fout);
	fprintf(fout,"%d -> %d\n", from, to);
	rec_han(n - 1, dop, to, from, fout);
}
int solve(unsigned long long n)
{
	FILE* rec = fopen("rec.txt","w");  
	FILE* notrec = fopen("notrec.txt","w");
	//int n;
	//scanf("%i",&n);
	rec_han(n,1,3,2,rec);
	han(n,notrec);
	fclose(rec);
	fclose(notrec);
	return n;
}	
void tester()
{
	FILE* tfin = fopen("tests_16.txt","r");
	int tests;
	fscanf(tfin,"%i",&tests);
	for(int t=0;t<tests;t++)
	{
		int n;
	    fscanf(tfin,"%i",&n);
	    solve(n);
		FILE* rec = fopen("rec.txt","r");  
		FILE* notrec = fopen("notrec.txt","r");
		bool flag = true;
		for(int i=0;i<(1ULL<<n)-1;i++)
		{
			int rret1,rret2,nrret1,nrret2;
			fscanf(rec,"%i -> %i",&rret1,&rret2);
			fscanf(notrec,"%i -> %i",&nrret1,&nrret2);
			if(rret1 != nrret1 || rret2 != nrret2)
				flag = false;
		//	printf("%i -> %i | %i -> %i\n",rret1,rret2,nrret1,nrret2);
	
			}
		if(flag)
			printf("OK\n");
		else
			printf("NOT K\n");	
		fclose(rec);
		fclose(notrec);
   	}
   	fclose(tfin);
}

int main()
{
//tester(solve());	

	tester();
}
		