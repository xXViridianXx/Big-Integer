/********************************************************************************* 
* Aniket Pratap, anpratap
* 2022 Spring CSE101 PA5
* ListTest.cpp
* Test file for List ADT
*********************************************************************************/

#include<string>
#include<iostream>
#include<stdexcept>
#include"List.h"

using namespace std;

int main() {
	List L = List();

	//creating List L
	cout << "pos = " << L.position() << endl;
	cout << "L = " << L << endl;
	L.insertAfter(420);
	cout << "pos = " << L.position() << endl;
	cout << "L = " << L << endl;
	L.insertAfter(99);
	cout << "pos = " << L.position() << endl;
	cout << "L = " << L << endl;
	L.insertAfter(44);
	cout << "pos = " << L.position() << endl;
	cout << "L = " << L << endl;
	L.insertAfter(86);
	cout << "pos = " << L.position() << endl;
	cout << "L = " << L << endl;
	L.insertAfter(69);
	cout << "pos = " << L.position() << endl;
	cout << "L = " << L << endl;
	L.insertAfter(420);
	L.moveNext();
	cout << "pos = " << L.position() << endl;
	cout << "L = " << L << endl;
	L.setAfter(99);
	cout << "L = " << L << endl;
	cout << "pos = " << L.position() << endl;

	int s = 86;
	int finding = L.findNext(s);
	int backwards = L.findPrev(s);
	
	//finding 86
	cout <<s<< " found at " << finding<< endl;
	cout <<s<< " backwards found at " << backwards<< endl;

	//cleaning L
	L.cleanup();
	cout << "L = " << L << endl;

	//copying 
	List G = L;
	G.insertAfter(11);
	cout << "G = " << G << endl;

	// A concat
	List A = G.concat(L);
	cout << "A = " << A << endl;

	//cleaning A
	A.cleanup();
	cout << "A = " << A << endl;

	//checking if A equals G
	bool equals = G.equals(A);
	cout << "A == G:  = " << equals << endl;
	A.moveNext();
	cout << "inserting " << equals << endl;
	A.insertAfter(21);
	cout << "A = " << A << endl;
	equals = (G == A);

	//checking if A equals G
	cout << "A == G: " << equals << endl;
	cout << "Clearing L: "<< endl;
	L.clear();
	cout << "L = " << L << endl;
	
	//creating List D
	List D = List();
	cout << "pos = " << D.position() << endl;
	cout << "D = " << D << endl;
	D.insertBefore(6);
	cout << "pos = " << D.position() << endl;
	cout << "D = " << D << endl;
	D.insertBefore(8);
	cout << "pos = " << D.position() << endl;
	cout << "D = " << D << endl;
	D.insertBefore(44);
	cout << "pos = " << D.position() << endl;
	cout << "D = " << D << endl;
	D.insertBefore(86);
	cout << "pos = " << D.position() << endl;
	cout << "D = " << D << endl;
	D.insertBefore(69);
	cout << "pos = " << D.position() << endl;
	cout << "D = " << D << endl;
	D.insertBefore(420);
	cout << "pos = " << D.position() << endl;
	cout << "D = " << D << endl;
	D.clear();
	cout << "D = " << D << endl;
	return 0;
}
