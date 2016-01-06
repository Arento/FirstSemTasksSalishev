#include<fstream>
#include<string>
#include<iostream>
using namespace std;
string strscan(char stop,ifstream& fin)
{   
	string ret="";
	char buf;
	while(fin.get(buf))
	{
		if(buf == stop)
			break;
		else
			ret += buf;
	}
	return ret;
}


void strrev()
{

	ifstream fin("input.txt");
	ofstream fout("output.txt");
	string ret = "";
	char buf,prev = '?';
	while(fin.get(buf))
	{
		if(buf == ' ' && prev == ' ')
		{
			ret += buf;
			break;
        }
        ret += buf;
   		prev = buf;
   	}
   	for(int i = ret.length()-1;i>=0;i--)
   		fout << ret[i];
   	fin.close();
   	fout.close();
}              
void tester()
{
	ifstream tfin("tests_1.txt");
	int number;
	tfin >> number;
	tfin.get();
	for(int t=0;t<number;t++)
	{
		string test;
		string ans;
		char buf;
		test = strscan('$',tfin);
        ans = strscan('#',tfin);
		ofstream fout("input.txt");
		fout << test;
		fout.close();
		strrev();
		ifstream fin("output.txt");		
		bool flag = true;
		int count=0;
		string ret = strscan(EOF,fin);
		fin.close();
		if(ret.length() != ans.length())
			flag = false;
		else
			for(int i=0;i<ans.length();i++)
				if(ans[i] != ret[i])
					flag = false;	
		if(flag)
			cout << "OK\n";

		else
			cout << "NOT OK:\nans:" << ans << "\nret:"<<ret<<'\n' ;
	}
	tfin.close();
}
	 	     
int main()
{                               
	tester();
	return 0;
}