#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<vector>  
#include<stack>
using namespace std;

 
void dfs_ts(int v,vector<int> *ans,vector<int> *colour, const vector<vector<int> >& graph)
{   
	stack<int> s;
	s.push(v);
	while(!s.empty())
	{
	    v = s.top();
	    if(colour->at(v) == 2)
	   	{
	   		ans->push_back(v);
	   		s.pop();
	   		continue;
	   	}
		for (size_t i=0; i<graph[v].size();i++) 
		{
			int to = graph[v][i];
			if (colour->at(to) == 0)
			{
				s.push(to);	
				break;
			}
			if(i == graph[v].size()-1)
				(*colour)[v] = 2;
	   	}
	   	if(0 == graph[v].size())
				(*colour)[v] = 2;
	}
}
 
void topsort(const vector<vector<int> >& graph, vector<int>* ans) 
{   
	int n = graph.size();
	ans->clear();
	vector<int> used(n,0);
	for (int i=0; i<n; i++)
		if (used[i] == 0)
			dfs_ts(i,ans,&used,graph);
	
	reverse (ans->begin(), ans->end());
}
bool dfs_check(int v,vector<bool>* used,
			const vector<vector<int> >& graph, 
			const vector<bool>& checked)
{
	(*used)[v]  = true;
	for(int i=0;i<graph[v].size();i++)
	{
		int to = graph[v][i];
		if(!checked[to])
			return false;
		if(!used->at(to))
			if(!dfs_check(to,used,graph,checked))
				return false;
	}
	return true;
}
			
bool check_ts(const vector<vector<int> > graph,const vector<int>& ts)
{   
	int n = graph.size();
	vector<bool> checked(n,false);
	for(int i=n-1;i>=0;i--)
	{
		vector<bool> used(n,false);
		if(!dfs_check(ts[i],&used,graph,checked))
			return false;
		checked[ts[i]] = true;
	}
	return true;
}
void solve_and_test()
{
	ifstream tfin("tests_15.txt");
	int tests;
	tfin >> tests;
	for(int t=0;t<tests;t++)
	{
		int n,m;
		tfin >> n >> m;
		vector<vector<int> > graph(n);
		vector<int> weight(n);
		for(int i=0;i<m;i++)
		{
			int a,b;
			tfin >> a >> b;
			a--;
			b--;
			graph[a].push_back(b);
	   	}
	   	for(int i=0;i<n;i++)
	   		tfin >> weight[i];
//	   	printf("Test#%i read\n",t+1);
	   	vector<int> ret;
	   	topsort(graph,&ret);
//	   	printf("Test#%i done\n",t+1);
	   	ofstream fout("output.txt");
	   	int time=0;
	   	for(int i=0;i<n;i++)
	   	{
			fout << ret[i]+1 << " " << time << endl;
			time += weight[ret[i]];
		}
		fout.close();
		printf("Test#%i result: ",t+1);
	   	if(check_ts(graph,ret))
	   		printf("OK\n");
	   	else
	   		printf("NOT OK\n");
	}
	tfin.close();
}	

int main()
{
	solve_and_test();
}