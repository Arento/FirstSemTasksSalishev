#include<iostream>
#include<fstream>
#include<vector>
//#include<random>
using namespace std;
class list
{
	public: class node;
	 node* head; 
	class node
	{
		public:
		int data;
	    node* next;
	};
	node* last;
	


	list(){ head = NULL;last = head; }

	void push(int data)
	{	
		node* newnode = new node;
		newnode->data = data;
		newnode->next = head;
		head = newnode;
		if( last == NULL)
			last = head;
		//cout << this->top()<<" ";
	}
	          	
 	bool pop()
 	{
 		if(head == NULL)
 			return false;
 		//cout << this->top()<<" ";
		node* oldnode = head;
		head = oldnode->next;
		if( head == NULL)
			last = NULL;
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
	bool loop_check()
	{   
		bool hasloop = false; 
		node* slowptr = head;
		node* fastptr = head;
		
		while(slowptr && fastptr  && !hasloop)
		{   cout << fastptr <<" "<<slowptr << endl;
			fastptr = fastptr->next;
			if(fastptr != NULL)      
			{
				if(fastptr == slowptr)
					hasloop = true;
				fastptr = fastptr->next;
			}
			slowptr = slowptr->next;
			if(fastptr == slowptr)
				hasloop = true;
		}
		return hasloop;
	}

};

void tester()
{
	list head;
	list::node* el;
	for(int i=0;i<10;i++)	
	{
		head.push(i);
		if(i == 5)
		el = head.head;
	}
	if( head.loop_check())
		cout << "NOT OK\n";
	else
		cout << "OK\n"; 
	(head.last)->next = el;
	if(! head.loop_check())
		cout << "NOT OK\n";
	else
		cout << "OK\n";	
}	


						
int main()
{
	tester();	 
}



