#include<bits/stdc++.h>
using namespace std;

map<string, string> instructions;


void build_instructions()
{
	instructions.insert{"add","XO"};
	instructions.insert{"addi","D"};
	instructions.insert{"addis","D"};
	instructions.insert{"and","X"};
	instructions.insert{"andi","D"};
	instructions.insert{"extsw","X"};
	instructions.insert{"nand","X"};
	instructions.insert{"or","X"};
	instructions.insert{"ori","D"};
	instructions.insert{"subf","XO"};
	instructions.insert{"xor","X"};
	instructions.insert{"xori","D"};
	instructions.insert{"ld","DS"};
	instructions.insert{"lwz","D"};
	instructions.insert{"std","DS"};
	instructions.insert{"stw","D"};
	instructions.insert{"stwu","D"};
	instructions.insert{"lhz","D"};
	instructions.insert{"lha","D"};
	instructions.insert{"sth","D"};
	instructions.insert{"lbz","D"};
	instructions.insert{"stb","D"};
	instructions.insert{"rlwinm","M"};
	instructions.insert{"sld","X"};
	instructions.insert{"srd","X"};
	instructions.insert{"srad","X"};
	instructions.insert{"sradi","XS"};
	instructions.insert{"b","I"};
	instructions.insert{"bl","I"};
	instructions.insert{"bclr","XL"};
	instructions.insert{"bc","B"};
	instructions.insert{"bca","I"};
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
		FILE *In;
		In = fopen(argv[1], "r");
		if (In == NULL) 
		{
			cout<<"Input file could not be opened."<<endl;
			exit(1);
		}

		FILE *Out;
		Out = fopen(argv[2], "w");
		if (Out == NULL) 
		{
			cout<<"Output file could not opened."<<endl;
			exit(1);
		}

		build_instructions();

		// Parse in passes

		int passNumber = 1;
		parse_file(In, passNumber);

		// Rewind input file & start pass 2
		rewind(In);
		passNumber = 2;
		parse_file(In, passNumber);

		// Close files
		fclose(In);
		fclose(Out);
	}

		return 0;
	
	
}