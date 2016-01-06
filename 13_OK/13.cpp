#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<functional>
using namespace std;


class graph
{	
	class hasher	
	{	
		public: size_t operator()(pair<int,int> key)	
		{   	
			int a = key.first;
			int b = key.second;
			a > b ? a ^= b ^= a ^= b : a = a;
			size_t n = (1 << 4*sizeof(size_t)-1);
			return ((n-1)*n/2-(n-a-1)*(n-a)/2)+b-a-1;
		}	                                  
	};
	class equal_to
	{
		public: bool operator()(pair<int,int> k1,pair<int,int> k2)
		{
			return ((k1.first == k2.first && k1.second == k2.second) ||	(k1.second == k2.first && k1.first == k2.second));
		}
	}; 
public:	
	unordered_set<pair<int,int>,hasher,equal_to > edges;
	int add(int a,int b)
	{
		int ret = edges.find(pair<int,int>(a,b)) != edges.end() ? 1 : 0;
        edges.insert(pair<int,int>(a,b));
        return ret;
    }
    int rm(int a,int b)
	{
		int ret = edges.find(pair<int,int>(a,b)) != edges.end() ? 1 : 0;
        edges.erase(pair<int,int>(a,b));
        return ret;
    }
    int find(int a,int b)
	{
		return  edges.find(pair<int,int>(a,b)) != edges.end() ? 1 : 0;
    }
	int do_req(int mode,int a,int b)
	{
		switch(mode)
		{
			case 0: return add(a,b);
			case 1: return rm(a,b);
			case 2: return find(a,b);
			default:
				printf("WRONG MODE\n");
				return -1;	
		}
   }
};
void tester()
{
	ifstream tfin("tests_13.txt");
	int tests;
	tfin >> tests;
	graph g1;
	for(int t=0;t<tests;t++)
	{
		int mode, a, b, ans;
		tfin >> mode >> a >> b >> ans;
		int res = g1.do_req(mode,a,b);
		if(res == ans)
			printf("OK\n");
		else
			printf("NOT OK\n");
	}
    tfin.close();
};

int main()
{
	tester();	
}          
                 