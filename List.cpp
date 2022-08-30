/********************************************************************************* 
* List ADT for BigInteger.cpp
*********************************************************************************/

#include<string>
#include<iostream>
#include<stdexcept>
#include"List.h"

// Node constructor 
List::Node::Node(ListElement x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}

//class contructors and decontructors
//allocaitng front and back dummy
//front and back dummy pointing to each
List::List() {
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

//Destructor
//calling clear to remove nodes
//deleting front and back
List::~List() {
	if(length() > 0) {
		clear();
	}
	frontDummy->next = NULL;
	frontDummy->prev = NULL;

	backDummy->next = nullptr;
	backDummy->prev = nullptr;

	delete frontDummy;
	delete backDummy;
}

//Copy constructor
List::List(const List& L) {

	//same info from constructor
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;

	//if L is nonempty, load elements
	//new allocates and inits object
	if(L.length() != 0) {
		Node *N = L.frontDummy->next;
		insertBefore(N->data);
		while(length() != L.length()) {
			N = N->next;
			insertBefore(N->data);
		}
	}
	moveFront();
}

//combines 2 lists starting with first
List List::concat(const List& L) const {
	List A;

	//getting data form first list
	if(this->num_elements != 0) {
		Node *N = this->frontDummy->next;
		A.insertBefore(N->data);
		while(A.length() != this->num_elements) {
			N = N->next;
			A.insertBefore(N->data);
		}
	}

	//getting info from second list
	if(L.length() != 0) {
		Node *N = L.frontDummy->next;
		A.insertBefore(N->data);
		while(A.length() != (this->num_elements + L.length())) {
			N = N->next;
			A.insertBefore(N->data);
		}
	}
	A.moveFront();
	return A;
	
}

//return length
int List::length() const {
	return(num_elements);
}

//return data of first element
ListElement List::front() const {
	if(length() == 0) {
		throw std::length_error("List: front(): empty List");
	}
	return(frontDummy->next->data);
}

//return data of back element
ListElement List::back() const {
	if(length() == 0) {
		throw std::length_error("List: back: empty List");
	}
	return(backDummy->prev->data);
}

//return position
int List::position() const {
	return(pos_cursor);
}

//getting the thing after the cursor
//by accessing after cursor
ListElement List::peekNext() const {
	if(position() >= length()) {
		throw std::domain_error("List: peekNext: position >= length");
	}
	return (afterCursor->data);
}

//getting the thing before the cursor
//by accessing beire cursor
ListElement List::peekPrev() const {
	if(position() <= 0) {
		throw std::domain_error("List: peekPrev: position <= 0");
	}
	return (beforeCursor->data);
}

//setting before, after and pos cursor to front
//after cursor is next of before 
void List::moveFront() {
	beforeCursor = frontDummy;
	afterCursor = beforeCursor->next;
	pos_cursor = 0;
}

//setting before, after and pos cursor to back
//before cursor is prev of before 
void List::moveBack() {
	afterCursor = backDummy;
	beforeCursor = afterCursor->prev;
	pos_cursor = length();
}

//moves before, after and pos cursor to next
//sets before cursor to after
//sets after to after next
//adds 1 to pos_cursor
ListElement List::moveNext() {
	if(position() >= length()) {
		throw std::domain_error("List: moveNext: position >= length");
	}
	beforeCursor = afterCursor;
	afterCursor = afterCursor->next;
	pos_cursor += 1;
	return beforeCursor->data;
}

//moves before, after and pos cursor to prev
//sets after cursor to before
//sets before to before prev
//subs 1 to pos_cursor
ListElement List::movePrev() {
	if(position() <= 0) {
		throw std::domain_error("List: movePrev: position <= 0");
	}
	afterCursor = beforeCursor;
	beforeCursor = beforeCursor->prev;
	pos_cursor -= 1;
	return afterCursor->data;
}

//inserts elements after cursor;
//ex 8|4 inserting 3 would be 8|34
void List::insertAfter(ListElement x) {
	Node *N = new Node(x);
	
	Node *M = beforeCursor->next;
	beforeCursor->next = N;
	N->prev = beforeCursor;
	N->next = M;
	M->prev = N;
	afterCursor = N;

	num_elements += 1;
}

//inserts elements before cursor;
//ex 8|4 inserting 3 would be 83|4
void List::insertBefore(ListElement x) {
	Node *N = new Node(x);
	afterCursor->prev = N;
	N->next = afterCursor;
	N->prev = beforeCursor;
	beforeCursor->next = N;
	beforeCursor = N;

	pos_cursor +=1;
	num_elements +=1;
}

//sets after cursor data to x
void List::setAfter(ListElement x) {
	if(position() >= length()) {
		throw std::domain_error("List: setAfter: position >= length");
	}
	afterCursor->data = x;
}

//sets before cursor data to x
void List::setBefore(ListElement x) {
	if(position() <= 0) {
		throw std::domain_error("List: setBefore: position <= 0");
	}
	beforeCursor->data = x;
}

//erases thing after cursor ie. after cursor
void List::eraseAfter() {
	if(position() >= length()) {
		throw std::domain_error("List: eraseAfter: position >= length");
	}
	Node *S = afterCursor;
	Node *A = afterCursor->next;

	beforeCursor->next = A;
	A->prev = beforeCursor;
	afterCursor = A;

	num_elements -= 1;
	delete S;
}

//erases thing before cursor ie. before cursor
void List::eraseBefore() {
	if(position() <= 0) {
		throw std::domain_error("List: eraseBefore: position <= 0");
	}
	Node *S = beforeCursor;
	Node *A = beforeCursor->prev;

	afterCursor->prev = A;
	A->next = afterCursor;
	beforeCursor = A;

	num_elements -= 1;
	pos_cursor -= 1;
	delete S;
}

//finds next element that matches input
//if length of list less than 0, return -1;
//move next and if found, place cursor after
int List::findNext(ListElement x) {
	if(length() >0) {
		while(position() < length()){
			if(afterCursor->data == x) {
				moveNext();
				return position();
			}
			moveNext();
		}
	}
	return -1;
}

//finds elements moving from back of list
//move prev and if found, place cursor before
int List::findPrev(ListElement x) {
	if(length() > 0) {
		while(position() > 0){
			if(beforeCursor->data == x) {
				movePrev();
				return position();
			}
			movePrev();
		}
	}
	return -1;
}

//removes duplicates from list
//and places cursor in spot relative to orig list
//uses dynamic index to check if dup before cursor
//if before, move pos cursor prev
//once program done, shift before and after curs to approp place
void List::cleanup() {
	Node *N = nullptr;
	Node *M = nullptr;
	int index = 0;
	int distance = 0;
	for(N=frontDummy->next; N != backDummy; N=N->next) {
		index = distance;
		for(M=N->next; M!=backDummy; M=M->next) {
			index += 1;
			if(M->data == N->data) {
				Node *P = M->prev;
				Node *T = M->next;
				P->next = T;
				T->prev = P;
				if(index < pos_cursor) {
					pos_cursor -=1;
					index -=1;	
				}

				delete M;
				num_elements -=1;
				M = P;
			}
		}
		distance +=1;
	}
	int data = pos_cursor;
	moveFront();
	while(pos_cursor != data) {
		moveNext();
	}
}

//to string function to print int format:
//(4, 5, 6, 7, 8)
//empty list should be ()
std::string List::to_string() const{
	Node *N = nullptr;
	std::string s ="(";
	if(length() == 0 ) {
		s += ")";
		return s;
	}
	for(N=frontDummy->next; N!=backDummy->prev; N=N->next)  {
		s += std::to_string(N->data) + ", ";
	}
		s += std::to_string(N->data) + ")";
	return s;
}

//clears all nodes in list
//leaves front and back dummy
void List::clear() {
	if(length() != 0) {
		while(length() > 0) {
			Node *N = backDummy->prev->prev;
			Node *P = backDummy->prev;
			N->next = backDummy;
			backDummy->prev = N;
			num_elements -= 1;

			delete P;
		}
		pos_cursor = 0;
	}
}

//checks if 2 lists equal
//sets node to first element in first list
//sets other node to first element in second
bool List::equals(const List& R) const {
	bool eq = (length() == R.length());
	Node *N = nullptr;
	Node *M = nullptr;
	if(eq) {
		N = this->frontDummy->next;	
		M = R.frontDummy->next;
		while(eq && N!= backDummy) {
			eq = (N->data == M->data);
			N = N->next;
			M = M->next;
		}
	}
	return eq;
}

//operator()
//inserts string rep of L
std::ostream& operator<< (std::ostream& stream, const List& L) {
	return stream << L.List::to_string();
}

//calls equal operator and overrides ==
bool operator== (const List& A, const List& B) {
	return A.List::equals(B);
}

//overrides = by swapping all values
List& List::operator= (const List& L) {
	if(this != &L) {
		List temp = L;

		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(num_elements, temp.num_elements);
	}
	return *this;
}


