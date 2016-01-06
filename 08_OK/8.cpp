#include<iostream>
#include<fstream>
#include<cstdio>
using namespace std;
class para
{
public:
	int a,b;
	para(){a=0;b=0;}
	para(int _a,int _b){              
		a = _a;
		b = _b;
	}
	bool operator<(para c){
		return a < c.a;
	}
	bool operator>(para c){
		return a > c.a;
	}
	bool operator<=(para c){
		return a <= c.a;
	}
	bool operator>=(para c)	{
		return a >= c.a;
	}
	bool operator!=(para c){
		return a != c.a;
	}
	bool operator==(para c){
		return a == c.a;
	}
	

	void print(){
		cout << a <<" " << b <<endl;
	}	
};
template<class T>
void swap(T* a,T* b)
{
	T c = *a;
	*a = *b;
	*b = c;
}
template<class T>
void qs(T* arr, int first, int last)
{
	while(last - first > 0)
	{
		int i = first,j = last;
		int cur = (first+last)/2;
		T x = arr[cur];
		do
		{
			while(arr[i] < x && i > first) i++;
			while(x <= arr[j] && j < last)
			{
				if(x == arr[j])
					cur = j;
			 	j--;
			}
			if(i<=j)
			{
				if(arr[j] < arr[i])
					swap<T>(arr+i,arr+j);
				i++;
				j--;      	
			}                     
	   	}
	   	while(i<=j);
	   	if(j<first)
	   	{
	   		if(arr[first] == x);
	   		else
	   			swap<T>(arr+first,arr+cur);
	   		first++;
	   	}
	   	else
	   	{
	   		if(last-i > j-first)
		   	{
		   		qs<T>(arr,first,j);
		   		first = i;
		   	}
		   	else
		   	{
		   		qs<T>(arr,i,last);
		   		last = j;
		   	}
		}
	}
}
void tester()
{   
	ifstream tfin("tests_8.txt");
	int tests;
	tfin >> tests;
	for(int t=0;t<tests;t++)
	{
		int n;
		tfin >> n;
		int arr[100];
		for(int i=0;i<n;i++)
		    tfin >> arr[i];
		qs<int>(arr,0,n-1);
		bool flag = true;
		for(int i=0;i<n-1;i++)       
			if(arr[i] > arr[i+1])
				flag = false;
		if(flag)
			printf("OK\n");
		else
			printf("NOT OK\n");
   }
   tfin.close();
}
int main()
{
	tester();
}                   `