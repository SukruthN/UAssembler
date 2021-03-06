#include<bits/stdc++.h>
using namespace std;

map<string, string> instructions;
map<string,string>register_map;
map<string,string>pseudo_instructions;
FILE *In;
FILE *Out;
int z=0;// extra global variable 
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
		if(input[i]!=' ' && input[i]!=',' && input[i]!='(')
			return i;
	}
}

string get_string(char input[],string t,int s)
{
	int i;
	for(i=s;input[i];i++)
	{
		if(input[i]!=' ' && input[i]!=','&& input[i]!='(' && input[i]!=')')
			t+=input[i];
		else
			break;
	}
	z=i;
	return t;

}

string convert_li(int n,char t)
{
	string res;
	res="\0";
	
	 for (int i = 23; i >= 0; i--) 
	 { 
        int k = n >> i; 
        if(i==1&&t=='s')
        res+='1' ;
        else
        {
        if (k & 1) 
            res+="1";
        else
            res+="0";
         }

    } 
   // cout<<res<<endl;
    return res;
}
string convert_i_li(string d)
{
	string res;
	res="\0";
	int n=stoi(d);
	 for (int i = 23; i >= 0; i--) 
	 { 
        int k = n >> i;
        
        if (k & 1) 
            res+="1";
        else
            res+="0";
    
    } 
   // cout<<res<<endl;
    return res;
}
string convert_d_ui(string d)
{
	string res;
	res="\0";
	int n=stoi(d);
	 for (int i = 15; i >= 0; i--) 
	 { 
        int k = n >> i; 
        if (k & 1) 
            res+="1";
        else
            res+="0";
    } 
   // cout<<res<<endl;
    return res;
}

string convert_d_si(string d)
{
	string res;
	res="\0";
	int n=stoi(d);
	 for (int i = 15; i >= 0; i--) 
	 { 
        int k = n >> i; 
        if (k & 1) 
            res+="1";
        else
            res+="0";
    } 
   // cout<<res<<endl;
    return res;
}

string convert_ds(string ds)
{
	string res;
	res="\0";
	int n=stoi(ds);
	 for (int i = 13; i >= 0; i--) 
	 { 
        int k = n >> i; 
        if (k & 1) 
            res+="1";
        else
            res+="0";
    } 
   // cout<<res<<endl;
    return res;
}
string convert_dsi(int n)
{
	string res;
	res="\0";
	 for (int i = 13; i >= 0; i--) 
	 { 
        int k = n >> i; 
        if (k & 1) 
            res+="1";
        else
            res+="0";
    } 
   // cout<<res<<endl;
    return res;
}

void transalate(string ins,string format,char input[],int s)
{
int i,j;
    if(format=="X")
    {
    	struct X result;
    	result.rb="00000";
    	if(ins=="and")
    	{
    		result.po="011111";
    		result.xo="0000011100";
    		result.rc="0";
    	}
    	
    	else if(ins=="extsw")
    	{
    		result.po="011111";
    		result.xo="1111011010";
    		result.rc="0";
    	}

    	else if(ins=="nand")
    	{
    		result.po="011111";
    		result.xo="0111011100";
    		result.rc="0";
    	}
 
    	else if(ins=="or")
    	{
    		result.po="011111";
    		result.xo="0110111100";
    		result.rc="0";
    	}
   
    	else if(ins=="xor")
    	{
    		result.po="011111";
    		result.xo="0100111100";
    		result.rc="0";
    	}

    	else if(ins=="sld")
    	{
    		result.po="011111";
    		result.xo="0000011011";
    		result.rc="0";
    	}

    	else if(ins=="srd")
    	{
    		result.po="011111";
    		result.xo="1000011011";
    		result.rc="0";
    	}

    	else if(ins=="srad")
    	{
    		result.po="011111";
    		result.xo="1100011010";
    		result.rc="0";
    	}

    	

           z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.ra<<endl;
            }
            i++;
            z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
            t=get_string(input,t,z);
            j=z;
           // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rs=register_map[t];
            	//cout<<result.rs<<endl;
            }
            j++;
            z=0;
    		i=eliminate_spaces(input,j);
    		z=i;
             t="\0";
            t=get_string(input,t,z);
            i=z;
           // cout<<t<<endl;
            if(t!="extsw")
        {        
            if(register_map.find(t)!=register_map.end())
            {
            	result.rb=register_map[t];
            	//cout<<result.rb<<endl;
            }
        }
            i++;

            if(ins=="cmp")
    	{
    		result.po="011111";
    		result.xo="0000000000";
    		result.rc="0";
    		z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
          // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rs=register_map[t];
            	//cout<<result.ra<<endl;
            }
            i=eliminate_spaces(input,i);
            z=i;
            t=get_string(input,t,z);
            i=z;
            i++;
            z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
            t=get_string(input,t,z);
            j=z;
           //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.rs<<endl;
            }
            j++;
             z=0;
    		i=eliminate_spaces(input,j);
    		z=i;
             t="\0";
            t=get_string(input,t,z);
            i=z;
           // cout<<t<<endl;
            
             
            if(register_map.find(t)!=register_map.end())
            {
            	result.rb=register_map[t];
            	//cout<<result.rb<<endl;
            }
        
            i++;
    	}
           string fans=result.po+result.rs+result.ra+result.rb+result.xo+result.rc;
           for(i=0;fans[i];i++)
           {
           	putc(fans[i],Out);
           }
           putc('\n',Out);
         // cout<<fans<<endl;//result to be added to output file

    }

    else if (format=="XO")
    {
    	struct XO result;
    	if(ins=="add")
    	{
    		result.po="011111";
 			result.oe="0";
    		result.rc="0";
    		result.xo="100001010";
    	}

    	else if(ins=="subf")
    	{
    		result.po="011111";
    		result.oe="0";
    		result.rc="0";
    		result.xo="000101000";
    	}

            z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
           // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rt=register_map[t];
           //cout<<result.rt<<endl;
            }
            i++;
            z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
            t=get_string(input,t,z);
            j=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
         // 	cout<<result.ra<<endl;
            }
            j++;
            z=0;
    		i=eliminate_spaces(input,j);
    		z=i;
             t="\0";
            t=get_string(input,t,z);
            i=z;
        // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rb=register_map[t];
           //cout<<result.rb<<endl;
            }
            i++;
           string fans1=result.po+result.rt+result.ra+result.rb+result.oe+result.xo+result.rc;
            for(i=0;fans1[i];i++)
           {
           	putc(fans1[i],Out);
           }
           putc('\n',Out);
           //cout<<fans1<<endl;//result to be added to output file

    }

    else if(format == "XS")
    {    //doubt in format
    	struct XS result;

    	if(ins == "sradi")
    	{
    		result.po="011111";
    		result.xo="110011101";
    		result.sh1="0";
    		result.rc="0";
    	}

    		z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.rt<<endl;
            }
            i++;
            z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
            t=get_string(input,t,z);
            j=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rs=register_map[t];
            	//cout<<result.ra<<endl;
            }
            j++;
            z=0;
    		i=eliminate_spaces(input,j);
    		z=i;
             t="\0";
            t=get_string(input,t,z);
            i=z;
           //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.sh=register_map[t];//this is wrong
            	//cout<<result.rb<<endl;
            }
            i++;
            string fans2 = result.po + result.rs + result.ra + result.sh + result.xo + result.sh1 + result.rc;
            //cout << fans2 << endl;
             for(i=0;fans2[i];i++)
           {
           	putc(fans2[i],Out);
           }
            putc('\n',Out);
    }

    else if(format == "D")
    {
    	struct D result;

    	if(ins == "addi")
    	{
    		result.po = "001110";
    	}

    	else if(ins == "addis")
    	{
    		result.po = "001111";
    	}

    	else if(ins == "andi")
    	{
    		result.po = "011100";
    	}

    	else if(ins == "ori")
    	{
    		result.po = "011000";
    	}

    	else if(ins == "lwz")
    	{
    		result.po = "100000";
    	}

    	else if(ins == "stw")
    	{
    		result.po = "100100";
    	}

    	else if(ins == "stwu")
    	{
    		result.po = "100101";
    	}

    	else if(ins == "lhz")
    	{
    		result.po = "101000";
    	}

    	else if(ins == "lha")
    	{
    		result.po = "101010";
    	}

    	else if(ins == "sth")
    	{
    		result.po = "101100";
    	}

    	else if(ins == "lbz")
    	{
    		result.po = "100010";
    	}

    	else if(ins == "stb")
    	{
    		result.po = "100110";
    	}

    /*	else if(ins == "cmpi")
    	{
    		result.po = "001011";
    	}*/
        if(ins=="addi" || ins=="addis")
        {    	

    		z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
           // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rt=register_map[t];
            	//cout<<result.rt<<endl;
            }
            i++;
            z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
             t=get_string(input,t,z);
             j=z;
           // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.ra<<endl;
            }
            j++;
            z=0;
            i=eliminate_spaces(input,j);
            z=i;
            t="\0";
            t=get_string(input,t,z);
            i=z;
           //cout<<t<<endl;
            //convert to si
            result.si=convert_d_si(t);
            i++;

        } 

        else if(ins=="andi" || ins=="ori"||ins=="xori")
        {    	

    		z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.rt<<endl;
            }
            i++;
            z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
             t=get_string(input,t,z);
             j=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rt=register_map[t];
            	//cout<<result.ra<<endl;
            }
            j++;
            z=0;
            i=eliminate_spaces(input,j);
            z=i;
            t="\0";
            t=get_string(input,t,z);
            i=z;
           //cout<<t<<endl;
            //convert to si

            result.si=convert_d_ui(t);
            i++;

        }   


        else
        {    	

    		z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
           // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rt=register_map[t];
            	//cout<<result.rt<<endl;
            }
            i++;
            z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
             t=get_string(input,t,z);
             j=z;
            //cout<<t<<endl;
           //convert to si
             result.si=convert_d_si(t);
            j++;
            z=0;
            i=eliminate_spaces(input,j);
            z=i;
            t="\0";
            t=get_string(input,t,z);
            i=z;
           //cout<<t<<endl;
             if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.ra<<endl;
            }
            
            i++;

        } 
            string fans3 = result.po + result.rt + result.ra + result.si;
            //cout << fans3 << endl;
             for(i=0;fans3[i];i++)
           {
           	putc(fans3[i],Out);
           }
         putc('\n',Out);
    }

    else if(format == "M")
    {
    	struct M result;
    	if(ins == "rlwinm")
    	{
    		result.po = "010101";
    		result.rc = "0";
    	}

    		z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.rt<<endl;
            }
            i++;
             z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
             t=get_string(input,t,z);
             j=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rs=register_map[t];
            	//cout<<result.ra<<endl;
            }
            j++;
            z=0;
            i=eliminate_spaces(input,j);
            z=i;
            t="\0";
            t=get_string(input,t,z);
            i=z;
           //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.sh=register_map[t];
            	//cout<<result.rb<<endl;
            }
            i++;
           z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
             t=get_string(input,t,z);
             j=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.mb=register_map[t];
            	//cout<<result.ra<<endl;
            }
            j++;
            z=0;
            i=eliminate_spaces(input,j);
            z=i;
            t="\0";
            t=get_string(input,t,z);
            i=z;
           //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.me=register_map[t];
            	//cout<<result.rb<<endl;
            }
            i++;
    		//rs,ra,sh,mb,me
    		string fans4 = result.po + result.rs + result.ra + result.sh + result.mb + result.me;
    		//cout << fans4 << endl;
    		 for(i=0;fans4[i];i++)
           {
           	putc(fans4[i],Out);
           }
           putc('\n',Out);
    }
    //b is wrong

    else if(format == "B")
    {
    	struct B result;
    	//po,bo,bi,bd,aa,lk
    	if(ins == "bc")
    	{
    		result.po = "010011";
    		result.aa = "0";
    		result.lk = "0";
    	}

    	else if(ins == "bca")
    	{
    		result.po = "010011";
    		result.aa = "1";
    		result.lk = "0";
    	}
            z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.bo=register_map[t];
            	//cout<<result.rt<<endl;
            }
            i++;
            z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
             t=get_string(input,t,z);
             j=z;
            //cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.bi=register_map[t];
            	//cout<<result.ra<<endl;
            }
            j++;
           z=0;
            i=eliminate_spaces(input,j);
            z=i;
            t="\0";
            t=get_string(input,t,z);
            i=z;
           //cout<<t<<endl;
            //check from symbol table or literal table
             if(symtab.find(t)!=symtab.end())
            {
                   result.bd=convert_dsi(symtab[t]);
            }
            else if (littab.find(t)!=littab.end())
            {
            	/* code */
            	result.bd=convert_dsi(littab[t]);
            }
            else
            {
            	result.bd=convert_ds(t);
            	//cout<<result.rt<<endl;
           }
            	
            	//cout<<result.rb<<endl;
            
            i++;
            string fans5 = result.po + result.bo + result.bi + result.bd + result.aa + result.lk;
            //cout << fans5 << endl;
             for(i=0;fans5[i];i++)
           {
           	putc(fans5[i],Out);
           }
           putc('\n',Out);
    }

    else if(format == "DS")
    {
    	//po,rt,ra,ds,xo
    	struct DS result;

    	if(ins == "ld")
    	{
    		result.po = "111010";
    		result.xo = "00";
    	}

    	else if(ins == "std")
    	{
    		result.po = "111110";
    		result.xo = "00";
    	}
    	    z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
           // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.rt=register_map[t];
            	//cout<<result.rt<<endl;
            }
            i++;
            z=0;
            j=eliminate_spaces(input,i);
            z=j;
            t="\0";
             t=get_string(input,t,z);
             j=z;
            //cout<<t<<endl;
            
            	result.ds=convert_ds(t);
            	//cout<<result.ra<<endl;
            
            j++;
            z=0;
            i=eliminate_spaces(input,j);
            z=i;
            t="\0";
            t=get_string(input,t,z);
            i=z;
          // cout<<t<<endl;
            if(register_map.find(t)!=register_map.end())
            {
            	result.ra=register_map[t];
            	//cout<<result.rb<<endl;
            }
            i++;
            string fans6 = result.po + result.rt + result.ra + result.ds + result.xo;
            //cout << fans6 << endl;
             for(i=0;fans6[i];i++)
           {
           	putc(fans6[i],Out);
           }
           putc('\n',Out);
    }

    else if(format == "I")
    {
    	struct I result;
    	//po, li, aa ,lk
    	if(ins == "b")
    	{
    		result.po = "010010";
    		result.aa = "0";
    		result.lk = "0";
    	}

    	else if(ins == "bl")
    	{
    		result.po = "010010";
    		result.aa = "0";
    		result.lk = "1";
    	}

    		 z=0;
    		i=eliminate_spaces(input,s);
    		z=i;
            string t="\0";
            t=get_string(input,t,z);
            i=z;
            //cout<<t<<endl;
           //check symbol table or literal table
            if(symtab.find(t)!=symtab.end())
            {
                   result.li=convert_li(symtab[t],'s');
            }
            else if (littab.find(t)!=littab.end())
            {
            	/* code */
            	result.li=convert_li(littab[t],'l');
            }
            else
            {
            	result.li=convert_i_li(t);
            	//cout<<result.rt<<endl;
           }
            i++;

            string fans7 = result.po + result.li + result.aa + result.lk;
             for(i=0;fans7[i];i++)
           {
           	putc(fans7[i],Out);
           }
           putc('\n',Out);
    }
      //do for other instruction types
    	// X, XO, XS, D, M, B, DS, I
}

void transalate_pseudo(string ins,string act_ins,char input[],int s)
{
    //pseudo instructions remaining and output to be included in a file
    int i,j;
      string res;
        res="\0";
          if(ins=="li"||ins=="lis")
          {
              // cout<<1<<endl; 
             res+=act_ins;
              for(i=s;input[i]!=',';i++)
              {
              	res+=input[i];
              }
              res+=", 0";
              for(j=i;input[j];j++)
              {
              	res+=input[j];
              }
             // cout<<res<<endl;
        string format=instructions[act_ins];
           		//cout<<ins<<endl;
        for(i=0;res[i]!=' ';i++);
        	char res1[1000];
        for(j=0;res[j];j++)
        {
             res1[j]=res[j];
              
         }

          //cout<<act_ins<<endl;
         // cout<<format<<endl;
         // cout<<i<<endl;
           		transalate(act_ins,format,res1,i);
        
             
          }
          else if (ins=="la")
         {

         	//cout<<1<<endl; 
             res+=act_ins;
              for(i=s;input[i]!=',';i++)
              {
              	res+=input[i];
              }
              res+=",";
              int p=i;
              for(j=i;input[j]!='(';j++);
              	for(i=j+1;input[i]!=')';i++)
              	{
              		res+=input[i];
              	}
              	//cout<<res<<endl;
              	//res+=",";
              	for(i=p;input[i]!='(';i++)
              	{
              		res+=input[i];
              	}
             
           //  cout<<res<<endl;
        string format=instructions[act_ins];
           		//cout<<ins<<endl;
        for(i=0;res[i]!=' ';i++);
        	char res1[1000];
        for(j=0;res[j];j++)
        {
             res1[j]=res[j];
              
         }

         // cout<<act_ins<<endl;
          //cout<<format<<endl;
         // cout<<i<<endl;
           		transalate(act_ins,format,res1,i);
          	
          }


          else if(ins=="mr")
          {
          	//cout<<1<<endl; 
             res+=act_ins;
             string res2="\0";
             int count=0;
              for(i=s;input[i];i++)
              {

              	if(input[i]=='#')
              		break;
              	res+=input[i];
              	if(input[i]==',')
              		count++;
              	if(count==1 )
              		res2+=input[i];

              }
              
              
              //res+=",";
              res+=res2;
             // cout<<res2<<endl;
              //cout<<res<<endl;
        string format=instructions[act_ins];
           		//cout<<ins<<endl;
        for(i=0;res[i]!=' ';i++);
        	char res1[1000];
        for(j=0;res[j];j++)
        {
             res1[j]=res[j];
              
         }

         // cout<<act_ins<<endl;
         //cout<<format<<endl;
         // cout<<i<<endl;
           		transalate(act_ins,format,res1,i);

          }

          else if(ins=="subi" || ins=="subis")
          {
          	cout<<1<<endl; 
             res+=act_ins;
             //string res2="\0";
             int count=0,c=0;
              for(i=s;input[i];i++)
              {

              	if(input[i]=='#')
              		break;
              	if(count==2 &&c==0)
              	{

              		res+='-';
              		c++;
              	}
              	res+=input[i];
              	if(input[i]==',')
              		count++;
              	

              }
              
              
              //res+=",";
             // res+=res2;
             // cout<<res2<<endl;
              cout<<res<<endl;
        string format=instructions[act_ins];
           		//cout<<ins<<endl;
        for(i=0;res[i]!=' ';i++);
        	char res1[1000];
        for(j=0;res[j];j++)
        {
             res1[j]=res[j];
              
         }

          cout<<act_ins<<endl;
         cout<<format<<endl;
          cout<<i<<endl;
           		transalate(act_ins,format,res1,i);
          }

          else if (ins=="sub")
          {
          	
          	 // cout<<1<<endl; 
             res+=act_ins;
             string res2="\0";
              for(i=s;input[i]!=',';i++)
              {
              	res+=input[i];
              }
              //cout<<res<<endl;
              
              for(j=i+1;input[j]!=',';j++)
              {
              	res2+=input[j];
              }
             //cout<<res2<<endl;
              for(i=j;input[i];i++)
              {
              	
              	if(input[i]=='#')
              		break;
              	res+=input[i];
              }
              res+=',';
              res+=res2;
             // cout<<res2<<endl;
             cout<<res<<endl;
        string format=instructions[act_ins];
           		//cout<<ins<<endl;
        for(i=0;res[i]!=' ';i++);
        	char res1[1000];
        int e=0;
        for(j=0;res[j];j++)
        {     
             res1[j]=res[j];
        // cout<<res1[j];
         
              
         }

         //cout<<act_ins<<endl;
         // cout<<format<<endl;
         //cout<<i<<endl;
           		transalate(act_ins,format,res1,i);
        
          }
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
          		if(type=='i')
          countd+=4;
               else if (type=='l')
               {
               	string data_type="\0";
               	for(i=0;input[i];i++)
               	{
               		if(input[i]=='.')
               			break;
               	}
               	for(j=i+1;input[j];j++)
               	{
               		if(input[j]==' ')
               			break;
               		data_type+=input[j];

               	}
               //	cout<<data_type<<endl;
               	if(data_type=="word")
               		{
               			countd+=4;
               			//cout<<1<<endl;
               		}
               	else if(data_type=="doubleword")
               		countd+=8;
               	else if(data_type=="halfword")
               		countd+=2;
               	else if(data_type=="byte")
               		countd+=1;
               	else if(data_type=="asciiz")
               		countd+=1;

               }
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
           		string error="Invalid instruction";
           		for(i=0;error[i];i++)
           		{
           			putc(error[i],Out);

           		}
           		putc('\n',Out);
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
