#include<bits/stdc++.h>
using namespace std;

map<string, string> instructions;
FILE *In;
FILE *Out;
struct X
{
	string po;
	string rs;
	string ra;
	string rb;
	string xo;
	string rc;
};

struct XS
{
	string po;
	string rs;
	string ra;
	string sh;
	string xo;
	string sh1;
	string rc;

};

struct D
{
	string po;
	string rt;
	string ra;
	string si;

};

struct M
{
	string po;
	string rs;
	string ra;
	string sh;
	string mb;
	string me;
	string rc;

};

struct B
{
	string po;
	string bo;
	string bi;
	string bd;
	string aa;
	string lk;

};

struct XO
{
	string po;
	string rt;
	string ra;
	string rb;
	string oe;
	string xo;
	string rc;

};
struct DS
{
	string po;
	string rt;
	string ra;
	string ds;
	string xo;
};
struct I
{
	string po;
	string li;
	string aa;
	string lk;
};


void build_instructions()
{//bulding the instruction map
	instructions.insert({"add","XO"});
	instructions.insert({"addi","D"});
	instructions.insert({"addis","D"});
	instructions.insert({"and","X"});
	instructions.insert({"andi","D"});
	instructions.insert({"extsw","X"});
	instructions.insert({"nand","X"});
	instructions.insert({"or","X"});
	instructions.insert({"ori","D"});
	instructions.insert({"subf","XO"});
	instructions.insert({"xor","X"});
	instructions.insert({"xori","D"});
	instructions.insert({"ld","DS"});
	instructions.insert({"lwz","D"});
	instructions.insert({"std","DS"});
	instructions.insert({"stw","D"});
	instructions.insert({"stwu","D"});
	instructions.insert({"lhz","D"});
	instructions.insert({"lha","D"});
	instructions.insert({"sth","D"});
	instructions.insert({"lbz","D"});
	instructions.insert({"stb","D"});
	instructions.insert({"rlwinm","M"});
	instructions.insert({"sld","X"});
	instructions.insert({"srd","X"});
	instructions.insert({"srad","X"});
	instructions.insert({"sradi","XS"});
	instructions.insert({"b","I"});
	instructions.insert({"bl","I"});
	instructions.insert({"bclr","XL"});
	instructions.insert({"bc","B"});
	instructions.insert({"bca","B"});
	instructions.insert({"cmp","X"});
	instructions.insert({"cmpi","D"});
	instructions.insert({"sc","SC"});

	return;
}

map<string,int>symtab;//symbol table
map<string,int>littab;//literal table
int countd=0;//keeping instruction count in the .data segment
int countt=0; //keeping instruction count in the .text segment

char check(char input[])
{    //no unnecessary new lines are allowed
     //comments must start from the beginning of the line
	//.align should not be used
	int i,j;
	if (input[0]=='#')
	{
		return 'c';
	}

	else if (input[0]=='.')
	{
		return 'd';
	}
	else if (input[i]=='\n')
	{
		return 'c';
	}
	for(i=0;input[i]==' ';i++);
	for(j=i+1;input[j]!=' ';j++)
	{
		if(input[j]==':')
			return 'l';
	}	
	


	return 'i';
}

void parse_file(FILE *fp,int n)
{  //pass 1
	// data segment before text segment
	int i,j;
	int k=0;
	string dir;
	if(n==1)
	{     
		int ch=getc(fp);
		if(ch==EOF)
			return;
		else
		{
          char input[128];
          input[0]='\0';
          fscanf(fp,"%[^\n]",input);
          char type=check(input);
          for(i=0;input[i];i++)
          	cout<<input[i];
          cout<<endl;
          cout<<type<<endl;
          
          if (type=='d')
          {
          	
          	dir='\0';
          	if(k<2)
          {	
          	for(i=0;input[i];i++)
          	{
          		dir+=input[i];
          	}
          	dir+='\0';
          }
          k++;
          cout<<dir<<endl;
           cout<<k<<endl;
          }
          /*else if (type=='l')
          {
          	  string label;
          	  label='\0';
          	  for(i=0;input[i]!=':';i++)
          	{
          		label+=input[i];
          	}
            label+='\0';
          	if(dir==".text")
          	{
          		symtab.insert({label,countt});
          	}
          	else
          	{
          		littab.insert({label,countd});
          	}
          }

          if(dir==".text")
          countt+=4;
          else 
          countd+=4;*/

        parse_file(fp,1);

}
      
	}
}




int main(int argc, char const *argv[])
{
	// Make sure correct number of arguments input
	if (argc != 3) 
	{
		cout<<"Incorrect number of arguments"<<endl;
	}

	else 
	{

		// Open I/O files
		// Check that files opened properly
		In = fopen(argv[1], "r");
		if (In == NULL) 
		{
			cout<<"Input file could not be opened."<<endl;
			exit(1);
		}

	
		Out = fopen(argv[2], "w");
		if (Out == NULL) 
		{
			cout<<"Output file could not opened."<<endl;
			exit(1);
		}

		build_instructions();

		// Parse in passes

		int passNumber = 1;
		FILE *fp;
		fp=In;
		parse_file( fp,passNumber);

		// Rewind input file & start pass 2
		//rewind(In);
		/*passNumber = 2;
		parse_file( passNumber);*/

		// Close files
		fclose(In);
		fclose(Out);
	}

		return 0;
	
	
}
