#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;
int kth_element()
{
	ifstream fin("input.txt");
	int n;
	int k;
	fin >> n >> k;
	k--;
	vector<int> v(n);
	for(int i=0;i<n;i++)
		fin >> v[i];
	nth_element(v.begin(),v.begin()+k,v.end());	
	return v[k];
}
void tester()
{
	ifstream tfin("tests_3.txt");
	int tests;
	tfin >> tests;
	for(int t =0;t<tests;t++)
	{
		int n,k;
		tfin >> n >> k;
		ofstream fout("input.txt");
		fout << n <<" "<< k <<endl;
		for(int i=0;i<n;i++)
		{
			int buf;
			tfin >> buf;
			fout << buf <<" ";
		}
		fout.close();
		int ans;
		tfin >> ans;
		if(kth_element() == ans)
			printf("OK\n");
		else
			printf("NOT OK\n");
	}
	tfin.close();
}
		


int main()                 
{
	tester();
}