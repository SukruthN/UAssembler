#include<bits/stdc++.h>
using namespace std;

map<string, string> instructions;
map<string,string>register_map;
map<string,string>pseudo_instructions;
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


void build_pseudo_instructions()
{//bulding the pseudo_instructions map
	//cout<<3<<endl;
	pseudo_instructions.insert({"cmpd","cmp 0,1,"});
	pseudo_instructions.insert({"cmpdi","cmpi 0,1,"});
	pseudo_instructions.insert({"li","addi"});
	pseudo_instructions.insert({"lis","addis"});
	pseudo_instructions.insert({"la","addi"});
	pseudo_instructions.insert({"mr","or"});
	pseudo_instructions.insert({"subi","addi"});
	pseudo_instructions.insert({"subis","addis"});
	pseudo_instructions.insert({"sub","subf"});
	pseudo_instructions.insert({"xnop","xori"});
	/*pseudo_instructions.insert({"xor","X"});
	pseudo_instructions.insert({"xori","D"});
	pseudo_instructions.insert({"ld","DS"});
	pseudo_instructions.insert({"lwz","D"});
	pseudo_instructions.insert({"std","DS"});
	pseudo_instructions.insert({"stw","D"});
	pseudo_instructions.insert({"stwu","D"});
	pseudo_instructions.insert({"lhz","D"});
	pseudo_instructions.insert({"lha","D"});
	pseudo_instructions.insert({"sth","D"});
	pseudo_instructions.insert({"lbz","D"});
	pseudo_instructions.insert({"stb","D"});*/
	
	return;
}


void build_registers()
{//bulding the register map
	//cout<<2<<endl;
	register_map.insert({"1","00001"});
	register_map.insert({"2","00010"});
	register_map.insert({"3","00011"});
	register_map.insert({"4","00100"});
	register_map.insert({"5","00101"});
	register_map.insert({"6","00110"});
	register_map.insert({"7","00111"});
	register_map.insert({"8","01000"});
	register_map.insert({"9","01001"});
	register_map.insert({"10","01010"});
	register_map.insert({"11","01011"});
	register_map.insert({"12","01100"});
	register_map.insert({"13","01101"});
	register_map.insert({"14","01110"});
	register_map.insert({"15","01111"});
	register_map.insert({"16","10000"});
	register_map.insert({"17","10001"});
	register_map.insert({"18","10010"});
	register_map.insert({"19","10011"});
	register_map.insert({"20","10100"});
	register_map.insert({"21","10101"});
	register_map.insert({"22","10110"});
	register_map.insert({"23","10111"});
	register_map.insert({"24","11000"});
	register_map.insert({"25","11001"});
	register_map.insert({"26","11010"});
	register_map.insert({"27","11011"});
	register_map.insert({"28","11100"});
	register_map.insert({"29","11101"});
	register_map.insert({"30","11110"});
	register_map.insert({"31","11111"});
	register_map.insert({"0","00000"});
	register_map.insert({"CIA","00000"});
	register_map.insert({"NIA","00000"});
	register_map.insert({"SRR0","00000"});

	return;
}


void build_instructions()
{//bulding the instruction map
	//cout<<1<<endl;
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
int k=0;
string dir1;
char check(char input[])
{    //no unnecessary new lines are allowed
     //comments must start from the beginning of the line
	//.align should not be used
	//start from the beginig of the line
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

int eliminate_spaces(char input[],int s)
{
	int i;
	for(i=s;input[i];i++)
	{
		if(input[i]!=' ' && input[i]!=',')
			return i;
	}
}


void transalate(string ins,string format,char input[],int s)
{
int i,j;
    if(format=="X")
    {
    	struct X result;
    	if(ins=="and")
    	{
    		result.po="011111";
    		result.xo="0000011100";
    		result.rc="0";
            i=eliminate_spaces(input,s);
            string t="\0";
            t+=input[i];
           // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.ra<<endl;
            }
            i++;
            j=eliminate_spaces(input,i);
            t="\0";
            t+=input[j];
           // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rs=register_map[t];
            	//cout<<result.rs<<endl;
            }
            j++;
            i=eliminate_spaces(input,j);
            t="\0";
            t+=input[i];
           // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rb=register_map[t];
            	//cout<<result.rb<<endl;
            }
            i++;
           string fans=result.po+result.rs+result.ra+result.rb+result.xo+result.rc;
          // cout<<fans<<endl;//result to be added to output file


    	}

    	//similarly do for extsw,nand,or,xor,sld,srd,srad,cmp
    }

    else if (format=="XO")
    {
    	struct XO result;
    	if(ins=="add")
    	{
    		result.po="011111";
    		result.xo="100001010";
    		result.rc="0";
    		result.oe="0";
            i=eliminate_spaces(input,s);
            string t="\0";
            t+=input[i];
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rt=register_map[t];
            	//cout<<result.rt<<endl;
            }
            i++;
            j=eliminate_spaces(input,i);
            t="\0";
            t+=input[j];
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.ra<<endl;
            }
            j++;
            i=eliminate_spaces(input,j);
            t="\0";
            t+=input[i];
           //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rb=register_map[t];
            	//cout<<result.rb<<endl;
            }
            i++;
           string fans1=result.po+result.rt+result.ra+result.rb+result.oe+result.xo+result.rc;
           cout<<fans1<<endl;//result to be added to output file

    	}

    	//do for other XO instructions
    }

}

void transalate_pseudo(string ins,string act_ins,char input[],int s)
{

}

void parse_file(FILE *fp,int n)
{  //pass 1
	// data segment before text segment
	int i,j;
	
	string dir;
	if(n==1)
	{     
		int ch=getc(fp);
		if(ch==EOF)
			return;
		else
		{  string copy;
			copy="\0";
          char input[10000];
          input[0]='\0';
          fscanf(fp,"%[^\n]",input);

          char type=check(input);

          for(i=0;input[i];i++)
          	{
          		copy+=input[i];
          //cout<<input[i];
          	}
        //  cout<<endl;
        // cout<<type<<endl;
          
         if (type=='d')
          {
          	
          	
          	if(k<2)
          {	
          	dir="\0";
          	dir=copy;
          	//dir+='\0';
          }
          k++;
          if(dir!="\0")
          	dir1=dir;
        // cout<<dir1<<endl;
          // cout<<k<<endl;
          }
          else if (type=='l')
          {
          	  string label;
          	  label="\0";

          	  for(i=0;input[i]!=':';i++)
          	{
          		label+=input[i];
          	}

            label+='\0';

          	if(dir1==".text")
          	{
          		symtab.insert({label,countt});
          	}


          	else if(dir1==".data")
          	{
          		littab.insert({label,countd});
          	}


          }

          if(dir1==".text")
          	{
          		if(type=='l'||type=='i')
          countt+=4;
              }
          else if(dir1==".data") 
          	{
          		if(type=='l'||type=='i')
          countd+=4;
            }
     // cout<<"countt="<<countt<<' '<<"countd="<<countd<<endl;

        parse_file(fp,1);

}
      
	}


	else
	{
        int ch=getc(fp);
		if(ch==EOF)
			return;
		else
		{    int ex=0;
			string copy;
			copy="\0";
          char input[10000];
          input[0]='\0';
          fscanf(fp,"%[^\n]",input);

          char type=check(input);
         // cout<<type<<endl;

          for(i=0;input[i];i++)
          	{
          		copy+=input[i];
          //cout<<input[i];
          	}
           //cout<<endl;
           if(type=='i')
           {  ex+=4;
           if(ex==countt-4)
           return; 
           	i=eliminate_spaces(input,0);
           	string ins;
           	ins="\0";
           	for(j=i;input[j]!=' ';j++)
           	{
           		ins+=input[j];
           	}

           	//cout<<ins<<endl;
           	if(instructions.find(ins)!=instructions.end())
           	{
           		string format=instructions[ins];
           		//cout<<ins<<endl;
           		transalate(ins,format,input,j);
           	}
           	else if(pseudo_instructions.find(ins)!=pseudo_instructions.end())
           	{
           		string act_ins=pseudo_instructions[ins];
           		//cout<<ins<<endl;
           		transalate_pseudo(ins,act_ins,input,j);

           	}
           	else
           	{  //push this into  output file
           		cout<<"Invalid instruction"<<endl;
           	}

           }
           else if(type=='d')
           {
           	ex+=4;
           	if(ex==countt-4)
           return; 
           }            


parse_file(fp,2);

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
		build_registers();
		build_pseudo_instructions();

		// Parse in passes

		int passNumber = 1;
		FILE *fp;
		fp=In;
		parse_file( fp,passNumber);

		// Rewind input file & start pass 2
		rewind(In);
		FILE *fp1;
		fp1=In;
		passNumber = 2;
		parse_file( fp1,passNumber);

		// Close files
		fclose(In);
		fclose(Out);
	}

		return 0;
	
	
}
