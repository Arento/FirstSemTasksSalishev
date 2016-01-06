#include<fstream>
#include<map>
#include<iostream>
#include<vector>
using namespace std;
void solve()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt"); 
	map<double,int> cont;
	double d;
	fin >> d;
	bool flag = true;
	while(flag)
	{
		double temp;
		fin >> temp;
		cont[temp] = 1;
		map<double,int>::iterator it = cont.find(temp);
		it++;
		if( it != cont.end())
			if(it->first - temp <= d)
				flag = false;
		(it--)--;
		if(cont.find(temp) != cont.begin())
			if(temp - it->first	 <= d)
				flag = false;
   	}
   	fout << cont.size() <<" ";
   	for(map<double,int>::iterator it = cont.begin();it != cont.end();it++)
   		fout << it->first <<" ";
   	fin.close();
   	fout.close();
}
void tester()
{
	ifstream tfin("tests_11.txt");
	int tests;
	tfin >> tests;
	for(int t=0;t<tests;t++)
	{
		ofstream fout("input.txt");
		int tn;
		tfin >> tn;
		for(int i=0;i<tn;i++)
		{
			double buf;
			tfin >> buf;
			fout << buf <<" ";
		}
		fout.close();

		solve();
		ifstream fin("output.txt");
		int ansn,retn; 
		tfin >> ansn;
		fin  >>  retn;
		vector<double> ans(ansn,0);
		vector<double> ret(ansn,0);

		for(int i=0;i<ansn;i++)
			tfin >> ans[i];

		for(int i=0;i<retn;i++)
			fin >> ret[i];
		//for(int i=0;i<ansn;i++)
			//cout << ans[i] <<" " << ret[i] << endl;
		bool flag = true;
		if(ansn != retn)
		{
			flag = false;
			cout << "num\n";
		}

		else
			for(int i=0;i<ansn;i++)
			{   
				if(ans[i] != ret[i])
				{
					flag = false;
					cout << "sort\n";
					break;
				}
			}
		fin.close();	
		if(flag)                              
			cout << "OK\n";         
		else
			cout << "NOT OK\n";
			
	}
	tfin.close();
}	
		

int main()
{
	tester();
}