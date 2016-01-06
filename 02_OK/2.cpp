#include<iostream>
#include<fstream>
#include<vector>
//#include<random>
using namespace std;
class list
{
	public: class node;
	private: node* head;
public: 
	class node
	{
		public:
		int data;
	    node* next;
	};
	


	list()
	{
		head = NULL;
		last = NULL;
	}
	void push(int data)
	{	
		node* newnode = new node;
		newnode->data = data;
		newnode->next = head;
		head = newnode;
		//cout << this->top()<<" ";
	}
	          	
 	bool pop()
 	{
 		if(head == NULL)
 			return false;
 		//cout << this->top()<<" ";
		node* oldnode = head;
		head = oldnode->next;
		delete oldnode;
		return true;
	}

	int top()
	{
		return head->data;
	}

	void reverse()
	{
		node* newHead = NULL;		
		while(head != 0)
		{
		    node* cur = head;
		    head = head->next;
		    cur->next = newHead;
		    newHead = cur;
		}        
		head = newHead;
	}
};

void tester()
{
	ifstream fin("tests_2.txt");
	int n = 1;
	fin >> n;
	for(int t=0;t<n;t++)
	{
		bool passed = true;
		int length;
		fin >> length;
		vector<int> test(length,0);
		list head;
		for(int i=0;i<length;i++)
		{
			fin >> test[i];
			head.push(test[i]);
		}
		head.reverse();
		//cout << endl;
		for(int i=0;i<length;i++)
		{
			if(head.top() != test[i])
			{
				passed = false;
				break;
			}
			if(!head.pop())
			{
				passed = false;
				break;
			}
		}
		if(passed)
			cout << "OK\n";
		else
			cout << "NOT OK\n"; 
	}
	fin.close();
}	


						
int main()
{
	tester();
	list head;	
}

	