#include<iostream>
#include<vector>
#include<fstream>
#include<cstdio>
using namespace std;
int min(int a,int b)
{
	return a<b?a:b;
}
int max(int a,int b)
{
	return a>b?a:b;
}

vector<int> lazy(10000,1e9);
int dp(int n)
{
	if(lazy[n] == 1e9)
	{
		int ret = 1e9;
		for(int i=0; i<n ; i++)
				ret = min(ret,max(1+dp(i),2+dp(n-i-1)));
	   	lazy[n] = ret;
	}
	return lazy[n];
}
int main()
{
	lazy[0] = 0;
	lazy[1] = 0;
	lazy[2] = 1;
	ofstream fout("123.txt");
	for(int i=1;i<=100;i++)
		fout << i << " " << dp(i) << endl;
	fout.close();
}		
