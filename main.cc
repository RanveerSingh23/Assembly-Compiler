#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <deque>
using namespace std;

void die(int line_no = 0) {
	cout << "Syntax Error on line " << line_no << endl;
	exit(1);
}

int main(int argc, char **argv) {
	//If we pass any parameters, we'll just generate an assembly file 
	//Otherwise we will generate an assembly file, assemble it, and run it
	bool assemble_only = false;
	if (argc > 1) assemble_only = true;
	ofstream outs("main.s"); //This is the assembly file we're creating
	if (!outs) {
		cout << "Error opening file.\n";
		return -1;
	}
	outs << ".global main\nmain:\n"; //Get the file ready to rock
	outs << "\tPUSH {LR}\n\tPUSH {R4-R12}\n\n";
	vector <string> data;
	data.push_back(".data\n" );
	int line_no = 0;
	while (cin) {
		string s;
		getline(cin,s);
		line_no++;
		if (!cin) break;
		transform(s.begin(), s.end(), s.begin(), ::toupper); //Uppercaseify
		auto it = s.find("QUIT"); //TERMINATE COMPILER
		if (it != string::npos) break;
		stringstream ss(s); //Turn s into a stringstream
		int label;
		ss >> label;
		if (!ss) die(line_no);
		outs << "line_" << label << ":\n"; //Write each line number to the file ("line_20:")
		string command;
		ss >> command;
		if (!ss) die(line_no);

		if (command == "REM") {
			continue;
		}
		else if (command == "GOTO") {
			int target;
			ss >> target;
			if (!ss) die(line_no);
			outs << "\tBAL line_" << target << endl;
			continue;
		}
		else if (command == "EXIT") {
			outs << "\tBAL quit\n";
			continue;
		}
		//YOU: Put all of your code here, interpreting the different commands in BB8
		else if (command == "PRINT"){
			string is_int;
			ss >> is_int;
			deque<string> deq;
			while(ss){
				string s;
				ss >> s;
				deq.push_back(s);
			}
			if (deq.size() > 1){
				string temp2 = " .asciz ";
				string temp3 = is_int;
				temp3.erase(0,1);
				temp3.pop_back();
				for(auto i : deq){
					string temp = deq.front();
					deq.pop_front();
					is_int = is_int+ " "+  temp ;
					temp.clear();
				}	
				//temp3.pop_back();
				int counter = 0;
				string label = "label";
				if (counter == 1){ label += "a";counter++;}
				outs << "\tLDR R0, =" << label << endl;
				//temp3 = temp3 + ": ";
				label = label + ": ";

				outs << "\tBL print_string" << endl;
				//string fina =  temp3 + temp2 + is_int;
				string fina =  label + temp2 + is_int;
				
				data.push_back(fina);
			}
			else{
				string reg = deq.front();
				//cerr << "DEQ FRONT: " << deq.front() << endl;
				if (is_int == "Q") die(line_no);
				if (is_int == "A") reg = "R4";
				if (is_int == "B") reg = "R5";
				if (is_int == "C") reg = "R6";
				if (is_int == "I") reg = "R7";
				if (is_int == "J") reg = "R8";
				if (is_int == "X") reg = "R9";
				if (is_int == "Y") reg = "R10";
				if (is_int == "Z") reg = "R11";
				outs << "\tMOV R0, " << reg << endl;
				outs << "\tBL print_number" << endl;
			}
			continue;
		}
		else if (command == "LET"){
			string sud = s;
			sud.erase(0,2);
			unordered_map<char,int> hash;
			for(auto i : sud)
				hash[i]++;
			deque<string> deq;
			while(ss){
				string s;
				ss >> s;
				deq.push_back(s);
			}
			string var1 = " ";
			string var2 = " ";
			string var3 = " ";
			bool isin = false;
			for(auto i : hash){
				if (isdigit(i.first)){
					isin = true;
				}
			}
			string tesq;
			//int tes;
			string tes;
			if (isin){
				deq.pop_back();
				tesq = deq.at(deq.size()-1);
				//tes = stoi(tesq);
				tes = tesq;
			}
			if(hash.find('A') != hash.end()) {
				if(var1 == " ")
					var1 = "R4";
				else if(var2 == " ") var2 = "R4";
				else var3 = "R4";
			}	
			if(hash.find('B') != hash.end()) {
				if(var1 == " ")
					var1 = "R5";
				else if(var2 == " ") var2 = "R5";
				else var3 = "R5";
			}	
			if(hash.find('C') != hash.end()) {
				if(var1 == " ")
					var1 = "R6";
				else if(var2 == " ") var2 = "R6";
				else var3 = "R6";
			}	
			if(hash.find('I') != hash.end()) {
				if(var1 == " ")
					var1 = "R7";
				else if(var2 == " ") var2 = "R7";
				else var3 = "R7";
			}	
			if(hash.find('J') != hash.end()) {
				if(var1 == " ")
					var1 = "R8";
				else if(var2 == " ") var2 = "R8";
				else var3 = "R8";
			}	
			if(hash.find('X') != hash.end()) {
				if(var1 == " ")
					var1 = "R9";
				else if(var2 == " ") var2 = "R9";
				else var3 = "R9";
			}	
			if(hash.find('Y') != hash.end()) {
				if(var1 == " ")
					var1 = "R10";
				else if(var2 == " ") var2 = "R10";
				else var3 = "R10";
			}	
			if(hash.find('Z') != hash.end()) {
				if(var1 == " ")
					var1 = "R11";
				else if(var2 == " ") var2 = "R11";
				else var3 = "R11";
			}	

			string function = " ";
			if(hash.find('+') != hash.end()) {
				function = "ADD"; 
			}	
			if(hash.find('-') != hash.end()) {
				function = "SUB"; 
			}	
			if(hash.find('*') != hash.end()) {
				function = "MUL"; 
			}	
			if (function == " ") {
				function = "MOV";
				if(isin){
					outs << function <<" "<< var1 << ", # " << tes << endl;
				}
				else
					outs << function << " " << var1 << ", " << var2 << endl;
			}
			else {
				if(var3 == " " and var1 == "R7" and var2 == "R11" ) outs << function << " " << var2 << ", " << var2 << ", " << var1 << endl;
				else if (var3 == " ")
					outs << function << " " << var1 << ", " << var1<< ", "<< var2 << endl;
				else 
					outs << function << " " << var3 << ", " << var1<< ", " <<var2 <<endl;
			}
			function = " ";
			var1 = " ";
			var2 = " ";

		}	
		else if (command == "IF"){
			deque<string> deq;
			while(ss){
				string s;
				ss >> s;
				deq.push_back(s);
			}
			unordered_map<string,int> hash;
			
			bool elses = false;
			string reg1 = " ";
			string reg2 = " ";
			string op = " ";
			for (auto i : deq){
				hash[i]++;
			}
			for (auto i : deq){
				
				if (i == "A" and reg1 == " ")
					reg1= "R4";
				else reg2 = "R4";

				if (i == "B" and reg1 == " ")
					reg1= "R5";
				else reg2 = "R5";

				if (i == "C" and reg1 == " ")
					reg1= "R6";
				else reg2 = "R6";

				if (i == "I" and reg1 == " ")
					reg1= "R7";
				else reg2 = "R7";

				if (i == "J" and reg1 == " ")
					reg1= "R8";
				else reg2 = "R8";

				if (i == "X" and reg1 == " ")
					reg1= "R9";
				else reg2 = "R9";

				if (i == "Y" and reg1 == " ")
					reg1= "R10";
				else reg2 = "R10";
				
				if (i == "Z" and reg1 == " ")
					reg1= "R11";
				else reg2 = "R11";
				if (i == "&&") die(line_no);

			}
			for (auto i : deq){
				if (i == "ELSE")
					elses = true;
				if (i == ">")
					op = ">";
				if (i == ">=")
					op = ">=";
				if (i == "<")
					op = "<";
				if (i == "<=")
					op = "<=";
				if (i == "==")
					op = "==";
				if (i == "!=")
					op = "!=";
				if (i == "&&") die(line_no);
		/*		if (i == "A" and reg1 == " ")
					reg1= "R4";
				else reg2 = "R4";

				if (i == "B" and reg1 == " ")
					reg1= "R5";
				else reg2 = "R5";

				if (i == "C" and reg1 == " ")
					reg1= "R6";
				else reg2 = "R6";

				if (i == "I" and reg1 == " ")
					reg1= "R7";
				else reg2 = "R7";

				if (i == "J" and reg1 == " ")
					reg1= "R8";
				else reg2 = "R8";

				if (i == "X" and reg1 == " ")
					reg1= "R9";
				else reg2 = "R9";

				if (i == "Y" and reg1 == " ")
					reg1= "R10";
				else reg2 = "R10";
				
				if (i == "Z" and reg1 == " ")
					reg1= "R11";
				else reg2 = "R11";

*/
			}
			//cerr << "THIS IS REG 1: " << reg1 << endl;
			//cerr << "THIS IS REG 2: " << reg2 << endl;
			int target2 = 0;
			string target;
			//outs << "\tBAL line_" << target << endl;

			for(int i =0 ; i<deq.size();i++){
				if (deq.at(i) == "GOTO"){
					string temp = deq.at(i+1);
					target = temp;
				}
			//	if(deq.at(i) == "ELSE"){
			//		string temp = deq.at(i+1);
			//		target2 = stoi(temp);
			//	}
			}
			if (op == "<"){
				if(reg1 == "R4" and reg2 == "R11") {
				outs <<"\tCMP " << "R4" << ", " << "R9" << endl;
				outs <<"\tBLT line_" << target << endl; //TODO get line number
				}
				else
				outs <<"\tCMP " << reg1 << ", " << reg2 << endl;
				outs <<"\tBLT line_" << target << endl; //TODO get line number
				if(elses == true){
					outs<<"\tBGE line_"<<target2 << endl;//TODO get line number
				}
			}
			if (op == ">"){
				outs <<"\tCMP " << reg1 << ", " << reg2 << endl;
				outs <<"\tBGT line_" << target << endl; //TODO get line number
				if(elses == true){
					outs<<"\tBLE line_"<<target2 << endl;//TODO get line number
				}
			}
			if (op == "<="){
				outs <<"\tCMP " << reg1 << ", " << reg2 << endl;
				outs <<"\tBLT line_" << target << endl; //TODO get line number
				if(elses == true){
					outs<<"\tBGT line_"<<target2 << endl;//TODO get line number
				}
			}
			if (op == ">="){
				outs <<"\tCMP " << reg1 << ", " << reg2 << endl;
				outs <<"\tBGE line_" << target << endl; //TODO get line number
				if(elses == true){
					outs<<"\tBLT line_"<<target2 << endl;//TODO get line number
				}
			}
			if (op == "=="){
				outs <<"\tCMP " << reg1 << ", " << reg2 << endl;
				outs <<"\tBEQ line_" << target << endl; //TODO get line number
				if(elses == true){
					outs<<"\tBNE line_"<<target2 << endl;//TODO get line number
				}
			}
			if (op == "!="){
				outs <<"\tCMP " << reg1 << ", " << reg2 << endl;
				outs <<"\tBNE line_" << target << endl; //TODO get line number
				if(elses == true){
					outs<<"\tBEQ line_"<<target2 << endl;//TODO get line number
				}
			}
		
			reg1 = " ";
			reg2 = " ";
			op = " ";
			continue;
		}







	}

	//Clean up the file at the bottom
	outs << "\nquit:\n\tMOV R0, #42\n\tPOP {R4-R12}\n\tPOP {PC}\n"; //Finish the code and return
	for(auto i : data){
		outs << i  << endl;
	}
	outs.close(); //Close the file

	if (assemble_only) return 0; //When you're debugging you should run bb8 with a parameter

	//print.o is made from the Makefile, so make sure you make your code
	if (system("g++ main.s print.o")) { //Compile your assembler code and check for errors
		cout << "Assembling failed, which means your compiler screwed up.\n";
		return 1;
	}
	//We've got an a.out now, so let's run it!
	cout << "Compilation successful. Executing program now." << endl;
	execve("a.out",NULL,NULL);
}
