#include<fstream>
#include<iostream>
#include<unordered_map>
#include<string>
#include<map>
using namespace std;
void solve()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	unordered_map<string,int> hash_table;
	string word;
	while(fin >> word)
		hash_table[word]++;
   	for(unordered_map<string,int>::iterator it = hash_table.begin();it!=hash_table.end();it++)
   	{
   		fout << it->first << " " << it->second << endl;
   		//cout << it->first << " " << it->second << endl;
   	}
   	fin.close();
   	fout.close();
}
void tester()
{
	ifstream tfin("tests_12.txt");
	int n_of_tests;
	tfin >> n_of_tests;
	for(int t=0;t<n_of_tests;t++)
	{              		
		ofstream fout("input.txt");
		map<string,int> ans;
		int n;
		tfin >> n;
		//cout << n <<" "<<n_of_tests <<endl;
		string word;
		for(int i = 0;i<n;i++)
		{
			tfin >> word;
			ans[word]++;
			fout << word << " ";
			//cout << n;
		}
		fout.close();
		solve();
		ifstream fin("output.txt");
		bool passed = true;
		int count = 0;
		while(fin >> word && fin >> n)
		{   
			count++;
			if(n != ans[word])
				passed = false;
		}
	   	if(ans.size() !=  count)
	   		passed = false;
	   	if(passed)
	   		cout << "OK\n";
	   	else
	   		cout << "NOT OK\n";
	   	fin.close();
	   	fout.close();
	}
	tfin.close();
}
int main()
{
	tester();
}	

			

	