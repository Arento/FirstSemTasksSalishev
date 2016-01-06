#include<cstdio>
class stack
{
private:
	int _max_size;
	int _size;
	int file_size;
	int _full_size;
	unsigned char *head,*headbuf;
	FILE* filebuf;
public:
	stack(int n,const char* filename)
	{
		_size = 0;
		_max_size = n;
		head = new unsigned char[_max_size];
		headbuf = new unsigned char[_max_size];
		filebuf = fopen(filename, "rb+");
	}
	void swap_heads(){
		unsigned char* buf;
		buf = head;
		head = headbuf;
		headbuf = buf;
	}	
	int size(){
		return _size;
	}
	int max_size(){
		return 2*_max_size;
	}
	int full_size(){
		return _full_size;
	}
	void flush()
	{
		//fseek (S->file, S->N * S->file_n, SEEK_SET); // сдвинулись на начало нового блока
		fwrite(headbuf, sizeof(unsigned char),_max_size,filebuf);
		swap_heads();
		file_size += _max_size;
		_size -= _max_size;
	}
	void raise()
	{   
	    fseek (filebuf, _max_size * (file_size/_max_size - 1), SEEK_SET);
		fread(head, sizeof(unsigned char), _max_size, filebuf);
		//return 1;
	}
	int top()
	{
		if(_size == 0)
			return -1;
		return *(head+((_size-1) % _max_size));
	}
	void push(unsigned char c)
	{
		if(_size == _max_size)
			swap_heads();
		if(_size == 2*_max_size)
			flush();
		_size++;
		_full_size++;
		*(head+((_size-1) % _max_size)) =  c;
    }
	int pop()
	{   if(_full_size== 0)
			return 0;
		if(_size == 0)
			raise();
		_size--;
		_full_size--;
		if(_size == _max_size)
			swap_heads();
	}
	int do_req(int mode,int a)
	{
		switch(mode)
		{
			case 0:
				push(a);
				return full_size();
			case 1:
				pop();
				return full_size();
			case 2:
				 return top();
		}
	}	
	~stack()
	{
		delete[] headbuf;
		delete[] head;
		fclose(filebuf);
	}
};
void tester()
{
	FILE* tfin = fopen("tests_7.txt","r");
	int tests;
	int n;
	fscanf(tfin,"%i%i",&tests,&n);
	stack st(n,"buf");
	for(int t=0;t<tests;t++)
	{
		int mode,a,ans;
		fscanf(tfin,"%i%i%i",&mode,&a,&ans);
		
		if(st.full_size() == ans)
			printf("OK\n");
		else
		{
			printf("vse slomalos\'");
			return;
		}
	}
	fclose(tfin);
}	

int main()
{
	tester();
}	
