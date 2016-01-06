#include<vector>
#include<utility>
#include<stack>
#include<cstdio>
#include<unordered_set>
#include<algorithm>
#include<iostream>
#define MAXN 40
using namespace std;



class hasher
{
public: size_t operator()(pair<int, int> key)
{
	int a = key.first;
	int b = key.second;
	a > b ? a ^= b ^= a ^= b : a = a;
	size_t n = (1 << 4 * sizeof(size_t) - 1);
	return ((n - 1)*n / 2 - (n - a - 1)*(n - a) / 2) + b - a - 1;
}
};
pair<int,int> stable_mkpair(int a,int b)
{
	a > b ? a ^= b ^= a ^= b : a = a;
	return pair<int,int>(a,b);
}
class equals
{
public: bool operator()(const pair<int, int>& k1,const pair<int, int>& k2)
{
	return ((k1.first == k2.first && k1.second == k2.second) || (k1.second == k2.first && k1.first == k2.second));
}
};


bool compare_edges(unordered_set<pair<int, int>, hasher, equals > edges1,
				   unordered_set<pair<int, int>, hasher, equals > edges2)
{
	if (edges1.size() != edges2.size())
		return false;
	for (unordered_set<pair<int, int> >::iterator it = edges1.begin();it != edges1.end();it++)
		if (edges2.find(*it) == edges2.end())
			return false;                      
	return true;
}


bool compare_cuts(unordered_set<int> verts1,unordered_set<int> verts2)
{	
	if (verts1.size() != verts2.size())
		return false;
	for (unordered_set<int>::iterator it = verts1.begin();it != verts1.end();it++)
		if (verts2.find(*it) == verts2.end())
			return false;
	return true;
}


bool compare_comps(vector<unordered_set<pair<int, int>, hasher, equals > > comps1, vector<unordered_set<pair<int, int>, hasher, equals > > comps2)
{
	if (comps1.size() != comps2.size())		return false;
	vector<bool> has_eq1(comps1.size(),false),
				 has_eq2(comps2.size(),false);	
	for (int i = 0;i<comps1.size();i++)
		for(int j = 0;j<comps2.size();j++)
			if(compare_edges(comps1[i], comps2[j]))
			{
				has_eq1[i] = true;
				has_eq2[j] = true;
			}	
	for(int i=0;i<comps1.size();i++)
		if(!has_eq1[i] || !has_eq2[i])
			return false;
	return true;
}


vector<int> g[MAXN];
bool used[MAXN];
int timer, number[MAXN], L[MAXN];
unordered_set<int> cutpoints;
unordered_set<pair<int, int>, hasher, equals > bridges, empty_uset;
stack<pair<int, int> > compbuf;
vector<unordered_set<pair<int, int>, hasher, equals > > components;
void dfs_cb(int curr, int prev = -1)
{
	used[curr] = true;
	number[curr] = L[curr] = timer++;
	int children = 0;
	equals eq;
	for(int i=0;i<g[curr].size();i++)
	{
		int to = g[curr][i];
		if(!used[to])
		{
			children++;
			compbuf.push(stable_mkpair(to,curr));
			dfs_cb(to,curr);
			L[curr] = min(L[curr],L[to]);
			if((L[to] >= number[curr] && prev != -1) || (prev == -1 && 
			children >= 2))
			{
				cutpoints.insert(curr);
				components.push_back(empty_uset);
				while(!eq(stable_mkpair(curr,to),compbuf.top()))
				{
					components[components.size()-1].insert(compbuf.top());
					compbuf.pop();
				}
				components[components.size()-1].insert(compbuf.top());
				compbuf.pop();
			}
			if(L[to] > number[curr])
				bridges.insert(stable_mkpair(to,curr));
			
		}
		else
		{
		
			if(number[to] < number[curr] && to != prev)
			{
				L[curr] = min(L[curr],number[to]);
				compbuf.push(stable_mkpair(to,curr));
			}
		}	
	}
		 
}
void solve()
{
	cutpoints.clear();
	bridges.clear();
	components.clear();
	//compbuf.clear();
	timer=0;
	for(int i=0;i<MAXN;i++)
	{	
		g[i].clear();
		used[i]=false;
		number[i]=0;
	    L[i]=0;
	}
	FILE* fin = fopen("input.txt", "r");
	int E, V;
	fscanf(fin, "%i%i", &E, &V);
	for (int i = 0;i<E;i++)
	{
		int a, b;
		fscanf(fin, "%i%i", &a, &b);
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs_cb(0);
	if(!compbuf.empty())
		components.push_back(empty_uset);
	while(!compbuf.empty())
	{
		components[components.size()-1].insert(compbuf.top());
		compbuf.pop();
	}	
}
void tester()
{
	FILE* tfin = fopen("tests_14.txt", "r");
	int tests;
	fscanf(tfin, "%i", &tests);
	for (int t = 0;t<tests;t++)
	{
		FILE* fout = fopen("input.txt", "w");
		int V, E;
		fscanf(tfin, "%i%i", &E, &V);
		fprintf(fout, "%i %i\n", E, V);
		for (int i = 0;i<E;i++)
		{
			int a, b;
			fscanf(tfin, "%i%i", &a, &b);
			fprintf(fout, "%i %i\n", a, b);
		}
		fclose(fout);
		solve();
		int ncuts, nbrids, ncomps;
		fscanf(tfin, "%i%i%i", &ncuts, &nbrids, &ncomps);
		unordered_set<int> anscuts;
		unordered_set<pair<int, int>, hasher, equals > ansbridges;
		vector<unordered_set<pair<int, int>, hasher, equals > > anscomps;
		//типа scan(anscuts);
		for (int i = 0;i<ncuts;i++)
		{
			int tmp;
			fscanf(tfin, "%i", &tmp);
			anscuts.insert(tmp);
		}
		//типа scan(ansbridges);
		for (int i = 0;i<nbrids;i++)
		{
			int tmp1, tmp2;
			fscanf(tfin, "%i%i", &tmp1, &tmp2);
			ansbridges.insert(stable_mkpair(tmp1, tmp2));
		}
		//типа scan(anscomps);
		for (int i = 0;i<ncomps;i++)
		{
			anscomps.push_back(tmp_edges);
			int ntmp;
			fscanf(tfin, "%i", &ntmp);
			for (int j = 0;j<ntmp;j++)
			{
				int tmp1, tmp2;
				fscanf(tfin, "%i%i", &tmp1, &tmp2);
				anscomps[anscomps.size() - 1].insert(stable_mkpair(tmp1, tmp2));
			}
		}
		if (compare_edges(bridges, ansbridges))
			printf("Test#%i: bridges OK | ", t + 1);
		else
			printf("Test#%i: bridges NOT OK | ", t + 1);
		if (compare_cuts(cutpoints, anscuts))
			printf("cutpoints OK | ");
		else
			printf("cutpoints NOT OK | ");
		if (compare_comps(components, anscomps))
			printf("components OK\n");
		else
			printf("components NOT OK\n");
	/*	for(int i=0;i<components.size();i++)
		{
			printf("%i\n",components[i].size());
			for(unordered_set<pair<int,int> >::iterator it = components[i].begin();it!= components[i].end();it++)
			   	printf("%i %i\n",it->first,it->second);
		} */
	}
	fclose(tfin);
}
int main()
{
	tester();
}
