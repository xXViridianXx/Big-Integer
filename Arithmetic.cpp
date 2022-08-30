/********************************************************************************* 
* Main file for BigInteger ADT
*********************************************************************************/
#include "List.h"
#include "BigInteger.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(int argc, char **argv) {

	//creates input and output files
	ifstream in;
	ofstream out;

	//checks if 3 arguments entered
	if(argc != 3) {
		cerr << "Usage: " << argv[0] <<" <input file>, <output file>" << endl;
		return(EXIT_FAILURE);
	}
	
	//open input file, if empty, return error
	in.open(argv[1]);
	if(!in.is_open()) {
		cerr << "Unable to open "<< argv[1]<<" for reading" << endl;
		return(EXIT_FAILURE);
	}
	
	//open output file, if empty, return error
	out.open(argv[2]);
	if(!in.is_open()) {
		cerr << "Unable to open "<< argv[2]<<" for writing" << endl;
		return(EXIT_FAILURE);
	}

	string num1;
	string num2;
	string newLine;
	
	//read in from input file
	//which is number
	//new line
	//number
	getline(in, num1);
	getline(in, newLine);
	getline(in, num2);

	BigInteger A(num1);
	BigInteger B(num2);
	BigInteger C;
	

	//conduct operations on BigInts
	out << A << endl << endl;
	out << B << endl << endl;

	out << A + B << endl << endl;

	out << A - B << endl << endl;

	out << A - A << endl << endl;

	BigInteger three("3");
	BigInteger two("2");
	

	three = three * A;
	two *= B;

	out << three - two << endl << endl;

	out << A * B << endl << endl;

	out << A * A << endl << endl;

	out << B * B << endl << endl;

	BigInteger A4;
	BigInteger B5;
	BigInteger nine("9");
	BigInteger sixteen("16");

	A4 = A * A * A * A;
	B5 = B * B * B * B * B;

	A4 *= nine;
	B5 *= sixteen;

	out << A4 + B5 << endl << endl;
	
	return 0;
}

