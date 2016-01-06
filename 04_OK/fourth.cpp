#include<vector>
#include<fstream>
#include<cstdio>
#include<iostream>
using namespace std;
int brev(int n,int max)
{
	int ret = 0;
	while(max-1)
	{
		ret += n&1;
		ret<<=1;
		n >>=1;
		max >>= 1;
	}
	ret >>= 1
	return ret;
}
vector<int> breverse_i(vector<int> ret)
{
	int ni;
	for(int i=0;i<ret.size();i++)
	{
		ni = brev(i,ret.size());
		if(ni > i)
		{
			ret[i] += ret[ni];
			ret[ni] = ret[i]-ret[ni];
			ret[i] -= ret[ni];
		}
	}
	return ret;
}
 void vecprint(vector<int> v)
{
	for(int i=0;i<v.size();i++)
		cout  << v[i] << " ";
	cout << endl;
}

void tester()
{
	int num_of_tests;
	ifstream tfin("tests_4.txt");
	tfin >> num_of_tests;
	for(int test = 0;test<num_of_tests;test++)
	{	
		int length;
		tfin >> length;
		vector<int> arr(length), ans(length),ret;
		for(int i=0;i<length;i++)
			tfin >> arr[i];
		for(int i=0;i<length;i++)
			tfin >> ans[i];
		ret = breverse_i(arr);
		bool flag = true;
		cout << "test: ";
		vecprint(arr);
		cout << "retu: ";
		vecprint(ret);
		cout << "answ: ";
		vecprint(ans);
		if(ret.size() != length)
			flag = false;
		else
		{
			for(int i=0;i<length;i++)
				if(ret[i] != ans[i])
					flag = false;
		}
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