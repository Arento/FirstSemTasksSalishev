#include<string>
#include<fstream>
#include<iostream>
using namespace std;
string cts(char a)
{
	string s = "s";
	s[0] = a;
	return s;
}
bool has_priority(char op2, char op1)
{
	if(op1 == '-')
		return (op2 == '-' || op2 =='+');
	if(op1 == '/')
		return true;
   	if(op1 == '+')
		return false;
	if(op1 == '*')
		return (op2 == '-' || op2 =='+' );
		 
}
class node
{
public:
	char sym;
	node* parent;
	node* left;
	node* right;
	node(node* _parent)
	{
		parent = _parent;
		left = NULL;
		right = NULL;
	}
	node()
	{
		parent = NULL;
		left = NULL;
		right = NULL;
	}


};

int construct(const string& s, int pos, node* n)
{
	n->sym = s[pos];
	if (s[pos] < 'a' || s[pos]>'z')
	{
		n->left = new node(n);
		n->right = new node(n);
		return construct(s, construct(s, pos + 1, n->left), n->right);
	}
	else return pos + 1;
}
string transform(node* root)
{
	if (root->sym < 'a' || root->sym > 'z')
	{
		if (root->parent != NULL && has_priority(root->sym, (root->parent)->sym))
			return '(' + transform(root->left) + root->sym + transform(root->right) + ')';
		else
			return transform(root->left) + cts(root->sym) + transform(root->right);
	}
	else
		return cts(root->sym);
}
string solve(string s)
{
	node* head = new node();
	construct(s,0,head);
	return transform(head);
}
void tester()
{
	ifstream fin("tests_10.txt");
	int n;
	fin >> n;
	string test;
	string ans;
	for(int i=0;i<n;i++)
	{
		fin >> test >> ans;
		if(solve(test) == ans)
			cout << "OK\n";
		else
			cout << "NOT OK:\n" << solve(test) <<endl << ans <<endl;
	}
	fin.close();
}
int main()
{                             /*
	node* head = new node();
	string s;
	cin >> s;
	construct(s, 0, head);
	cout << transform(head);*/
	tester();
}

















