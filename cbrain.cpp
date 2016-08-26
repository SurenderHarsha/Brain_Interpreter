#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define t_m 20
int* mem;
char *buffer;
char semantics[]={'+','-','<','>','.',',','[',']','*','^','/','~',';'};
int *loop_stack;
int loop_s_top=0;
int subroutine_false=1;
char* output_buffer;
int out_length=0;
int out_pointer=0;
/*
	5 new Optional symbols are introduced to make life easier. They are optional to use and this interpreter supports them
	
   *  -> increments the current cell by 10
   /  -> decrements the current cell by 10
   ^  -> jumps to the first memory cell
   ~   -> Starts from the first cell and searches every cell until it finds 0 and stop at that cell
   ;   -> starts from the first cell and stops at the first non zero cell.

*/
class Brain
{
	int pc=0;
	int pointer=0;
	string each_line;
	ifstream FileRead;
	int data_length;
	int loop_count=0;
	public:
	Brain(char* filename)
	{
		try{
		
		buffer=new char[10000];
		int read_no=1;
		FileRead.open(filename);
		while(!FileRead.eof())
		{

			getline(FileRead,each_line);

			for(int i=0;i<each_line.length();i++)
			{

				if(in_semantic(each_line[i]))
				{
					buffer[pc++]=each_line[i];
					if(each_line[i]=='[')loop_count++;
					if(each_line[i]=='.')out_length++;
				}
			}
		}
		data_length=pc;
		loop_stack=new int[loop_count+1];
		pc=0;
	}
	catch(...)
	{
		cout<<"An Error Occured when reading the file, try again later!"<<endl;
		pc=-2;
		return;
	}
	}
	int in_semantic(char c)
	{
		for(int i=0;i<13;i++)
		{
			if(c==semantics[i])
			{
				return 1;
			}
		}
		return 0;
	}
	void prog_output()
	{
		for(int i=0;i<out_pointer;i++)
		{
			cout<<output_buffer[i];
		}
	}
	void output_file()
	{
		for(int i=0;i<data_length;i++)
		{
			cout<<buffer[i];
		}
		cout<<endl;
	}
	void print_mem(char input)
	{
		cout<<"|";
		for(int i=0;i<t_m;i++)
		{
			cout<<mem[i]<<"|";
		}
		cout<<"P="<<pointer<<" Symbol:"<<input<<" Read:"<<pc<<endl;
	}
	void execute()
	{
		cout<<"Do you want to display memory?(y/n):";
		char choice;
		cin>>choice;
		mem=new int[t_m]();
		output_buffer=new char[out_length+1];
		//print_mem();
		while(pc<data_length){
		char input=buffer[pc];
		//cout<<"DEBUG1:"<<input<<endl;
		if(choice=='y'||choice=='Y')
		print_mem(input);
		switch(input)
		{
			case '+':{
				
					inc();break;


			}
			case '-':{
				
					dec();break;


			}
			case '>':{
				
					mov_r();break;


			}
			case '<':{
				
					mov_l();break;


			}
			case '.':{
				
					out();break;


			}
			case ',':{
				
					inp();break;


			}
			case '*':{
			
					mul();break;


			}
			case '/':{
				
					div();break;


			}
			case '^':{
				
					jump_zero();break;


			}
			case '~':{
				
					search_zero();break;


			}
			case ';':{
				
					search_nonzero();break;


			}
			case '[':{
				
					loop_start();break;


			}
			case ']':{
				
					loop_end();break;


			}
		}
		pc++;
}
}
	
	
	
	
	/*Here start the functions of each of the basic symbols, it is recommended not to modify them, but new symbols with their functions can be added below*/
	void inc()
	{
		if(mem[pointer]==255)
		{
			mem[pointer]=0;
			return;
		}
		mem[pointer]++;
	}
	void dec()
	{
		if(mem[pointer]==0)
		{
			mem[pointer]=255;
			return;
		}
		mem[pointer]--;
	}
	void mov_r()
	{
		if(pointer==t_m-1)
		{
			pointer=0;
			return;
		}
		pointer++;
	}
	void mov_l()
	{
		if(pointer==0)
		{
			pointer=t_m-1;
			return;
		}
		pointer--;
	}
	void inp()
	{
		char c;
		cin>>c;
		mem[pointer]=(int)c;
		
	}
	void out()
	{
		output_buffer[out_pointer++]=(char)mem[pointer];
	}
	void mul()
	{
		for(int i=0;i<10;i++)
			inc();
	}
	void div()
	{
		for(int i=0;i<10;i++)
		dec();
	}
	void search_zero()
	{
		for(pointer=0;pointer<t_m;pointer++)
		{
			if(mem[pointer]==0)
			{
				break;
			}
		}
		return;
	}
	void search_nonzero()
	{
		for(pointer=0;pointer<t_m;pointer++)
		{
			if(mem[pointer]!=0)
			break;
		}
	}
	void jump_zero()
	{
		pointer=0;
	}
	void loop_start()
	{
		if(mem[pointer]==0)
		{
			
			//subroutine_false=0;
			//loop_stack[loop_s_top++]=pc;
			int remember=pc;
			for(int i=pc;;i++)
			{
				if(i==data_length)break;
				if(buffer[i]=='[')
				{
					loop_stack[loop_s_top++]=i;
					
				}
				if(buffer[i]==']')
				{
					if(remember==loop_stack[loop_s_top-1])
					{
						loop_s_top--;
						pc=i;
						break;
					}
					else
					{
						loop_s_top--;
					}
				}
			}
			return;
		}
		loop_stack[loop_s_top++]=pc;
		
	}
	void loop_end()
	{
		try{
		if(subroutine_false==0)
		{
			--loop_s_top;
			subroutine_false=1;
			return;
		}
		
		pc=loop_stack[--loop_s_top]-1;
		
	}
	catch(...)
	{
		cout<<"Something went wrong check the syntax of the program and try again!"<<endl;
		return;
	}
	}

};




int check_extension(string c)
{
	try{

	string check="shb";
	int lit=0;
	for(int i=c.length()-1;i>=c.length()-3;i--)
	{
		if(check[lit++]!=c[i])
		{
			return 0;
		}
	}
	return 1;
}
catch(...)
{
	return 0;
}
}






int main()
{
	string name;
	cout<<"Enter a bhs File Name:";
	cin>>name;
	if(check_extension(name))
	{
		try{

		char* fname=new char[name.length()+1];
		strcpy(fname,name.c_str());
		Brain bhs(fname);
		bhs.output_file();
		bhs.execute();
		bhs.prog_output();
		
		
	}catch(...){ cout<<"File Not Found? Try Again!"<<endl;
	return 0;
	}}
	else{
		cout<<"The File Extension is invalid, Please use a '.bhs'' extension"<<endl;
	}
	return 0;
}

