/********************************************************************************* 
* BigInteger ADT
*********************************************************************************/

#include <cmath>
#include <cstring>
#include "BigInteger.h"

//power and base
uint64_t POWER = 9;
long BASE = pow(10, POWER);

//defining local functions
void negateList(List& L);
void sumList(List& S, List A, List B, int sign);
void shiftList(List& L, int p);
void scalarMultList(List& L, ListElement m);

//default constructor
//setting sign to 0
//init digits
BigInteger::BigInteger() {
	signum = 0;
	List digits;
}

//checks if user input is valid
//checks for sign, and if present, store and remove
//check each char to see if digit
int trueInput(std::string& s, int& sign) {
	if(s[0] == '+' || s[0] == '-') {
		if(s[0] == '-') {
			sign = -1;
		}
		s.erase(0, 1); //erase sign if exists
	}

	//if length of string after sign removal 0
	//return 0
	if (s.length() == 0){
		return 0;
	}

	//erase leading zeros
	s.erase(0, s.find_first_not_of('0'));

	//if numbers all zeros, sest sign to 0
	//return 1 because 0 valid input
	if (s.length() == 0){
		sign = 0;
		return 1;
	}

	//check if each char in string a digit
	for(auto &num : s) {
		if(std::isdigit(num) == 0) {
			return 0;
		}
	}
	return 1;
}

//BigInt constructor using string as input
BigInteger::BigInteger(std::string s) {
	signum = 1;

	//calls trueInput and checks if length 0
	if(s.length() == 0 || !trueInput(s, signum)) {
		throw std::invalid_argument("BigInteger: Contructor: non-numeric string");
	}

	std::string c = s;
	int lower = c.length();
	int upper = lower - POWER;
	long num;

	//if substring relating to power until evenly divided
	while(c.length() > 0 && c.length() >= POWER) {
		std::string sub = c.substr(upper, lower+1);
		c.erase(upper, POWER); //erase sign if exists
		lower = c.length()-1;
		upper = c.length() - POWER;
		num = std::stol(sub);
		digits.insertAfter(num);

	}

	//odd divided inserted at end
	if(c.length() > 0) {
		num = std::stol(c);
		digits.insertAfter(num);
		//c.erase();  not needed but...
	}
}


//to string function to print BigInt
std::string BigInteger::to_string() {

	//creates empty string
	//also checks if negative, print "-"
	std::string bigInt = "";
	if(signum == -1) {
		bigInt += "-";
	}

	//creating str to store number in node
	int num = 0;
	std::string str = "";
	digits.moveFront();

	//creates string and add to zeros
	//zeros makes sure to return exact amount of zeros in original
	//because if power is 3 and "000" is just 0 in node
	//and won't return original number
	if(digits.length() == 0) {
		return "0";
	}

	//creates BigInt based on string input
	do {
		std::string zeros = "";
		num = digits.moveNext();
		str = std::to_string(num);
		if(str.length() < POWER && digits.position() > 1) { 
			std::string zeros(POWER - str.length(), '0');
			bigInt += zeros;
		}
		zeros += str;
		bigInt += zeros;
	}while(digits.position() < digits.length());
	return bigInt;
}

//copy constructor
BigInteger::BigInteger(const BigInteger &N) {

	//copying because can't change orig Int
	signum = N.signum;
	digits = N.digits;
	
}

//retuns sign of BigInt
int BigInteger::sign() const{
	return signum;
}

//clears BigInt to only return empty string
//sets sign to 0 state
void BigInteger::makeZero() {
	digits.clear();
	signum = 0;
}

//negates number by negating sign
void BigInteger::negate() {
	if(digits.length() == 0) {
		return;
	}
	signum *= -1;
}

//compares if BigInt M greater (1), less, (-1) or equal (0) to N
int BigInteger::compare(const BigInteger& N) const{

	//return if diff sign
	if(signum > N.signum) {
		return 1;
	}
	if(signum < N.signum) {
		return -1;
	}

	//if same sign, check length and return
	if(digits.length() > N.digits.length()) {
		return 1;	
	}
	if(digits.length() < N.digits.length()) {
		return -1;	
	}

	if(digits.length() == 0 && N.digits.length() == 0) {
		return 0;
	}
	
	//if same sign and length, loop through both lists
	int nInt, otherInt = 0;
	List tempN = N.digits;
	List other = digits;
	tempN.moveFront();
	other.moveFront();
	
	//check each number starting from most significant
	while(other.position() < tempN.length()) {
		nInt = tempN.moveNext();
		otherInt = other.moveNext();
		if(otherInt > nInt) {
			return (1*signum);
		}
		else if(otherInt < nInt) {
			return (-1*signum);
		}
	}
	return 0;
}

//helper function to negate numbers in List
//used for substraction
void negateList(List& L) {
	L.moveFront();
	int num = 0;
	do {
		num = -1 * L.moveNext();
		L.setBefore(num);

	}while(L.position() < L.length());
}

//pass in copies for A and B
void sumList(List& S, List A, List B, int sign) {
	bool rmZero;

	//checks is both empty a.k.a 0 then return
        if(A.length() == 0 && B.length() == 0) {
                List empty;
                S = empty;
                return;
        }

	//if B is zero, set S to A
        if(B.length() == 0) {
                S = A;
                return;
        }

	//if A is zero, set S to B
        if(A.length() == 0) {
                S = B;
                if(sign == -1) {
                        negateList(S); //check this again
                }
                return;
        }
        A.moveFront();
        B.moveFront();
        S.moveFront();
        long numA, numB = 0;

	//start adding from most significant digit
	//this is so that you can remove leading zeros
	//if A larger, insert/set delete before
	//if B larger, insert/set delete before
	//if equal move cursor same time
        if(A.length() > B.length()) {
		rmZero = true;
                do {
                        numA = A.moveNext();
			A.eraseBefore();
			if(numA == 0 && rmZero) {
				continue;
			}
			rmZero = false;
			if(S.length() > 0 && S.position() < S.length()) {
				S.moveNext();
				S.setBefore(numA);
			} 
			else {
                        	S.insertBefore(numA);
			}
                }while(A.length() != B.length());
        }
        else if(B.length() > A.length()) {
		rmZero = true;
                do {
                        numB = B.moveNext();
			B.eraseBefore();
			if(numB == 0 && rmZero) {
				continue;
			}
			rmZero = false;
			if(S.length() > 0 && S.position() < S.length()) {
				S.moveNext();
				S.setBefore(sign*numB);
			} 
			else {
                        	S.insertBefore(sign*numB);
			}
                }while(B.length() != A.length());
        }

	//if equal length move cursor same time
	rmZero = true;
        do {
                numA = A.moveNext();
                numB = B.moveNext();
		if(numA + (sign*numB) == 0 && rmZero) {
			continue;
		}
		rmZero = false;
		if(S.length() > 0 && S.position() < S.length()) {
			S.moveNext();
                	S.setBefore(numA + (sign*numB));
		} 
		else {
                	S.insertBefore(numA + (sign*numB));
		}
        }while(A.position() < A.length() && B.position() < B.length());
}

//performs carries and returns sign of number
int normalizeList(List& L) {
	
	//if length of L 0, don't normalize
	//and return 0
	if(L.length() == 0) {
		return 0;
	}
        int sign = 0;
        long num = 0;
        long carry = 0;
        L.moveBack();

	//conducts carry method based on if number is pos or negative
	//if number pos and greater than base, do num / BASE to get carry
	//if neg, do -1*((num))/BASE + 1 because want to make number positive
        do {
                num = L.movePrev();
                if(num > 0 && num >= BASE) {
                        carry = num / BASE;
                        L.setAfter(num - (carry * BASE));
			
                        if(L.position() == 0 && carry != 0) {
                                L.insertAfter(carry);
                                break;
                        }
			else {
                        	L.setBefore(L.peekPrev() + carry);
			}
                }
                else if(num < 0 && L.position() != 0) {
                        carry = ((-1*num) / BASE) + 1;
                        L.setAfter(num + (carry * BASE));
                        if(L.position() == 0 && carry != 0) {
                                L.insertAfter(-1*carry);
                                break;
                        }
                        else {
				
                                L.setBefore(L.peekPrev()- carry);
                        }
                }

		//deletes front zero if any
                if(L.position() == 0 && L.front() == 0) {
                        L.eraseAfter();
                        break;
                }
                carry = 0;
        }while(L.position() > 0);

	//if front number negate, negate and return sign
	//otherwise make sign pos
        if(L.front() < 0) {
                sign = -1;
                negateList(L);
        }
        else if(L.front() > 0) {
                sign = 1;
        }
        return sign;
}

//shits list p times, by appending 0 at end
void shiftList(List& L, int p) {
	if(L.length() == 0) {
		return;
	}
	L.moveBack();
	for(int i = 0; i < p; i++) {
		L.insertAfter(0);		
	}
}

//multiplies while list by m
void scalarMultList(List& L, ListElement m) {
 	if(L.length() == 0) {
		return;
	}
	L.moveFront();
	long num = 0;
	do {
		num = m * L.moveNext();
		L.setBefore(num);
	
	}while(L.position() < L.length());
}

//adds 2 big integers together
BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger S;
	int addSign = 0;
	int compare = this->compare(N);
	int sign = 0;
	List A;
	List B;	
	
	//set A to larger number when comparing this and N
	if(compare == 1 || compare == 0) {
		A = digits;
		B = N.digits;	
		addSign = N.signum;
	}
	else if(compare == -1) {
		A = N.digits;	
		B = digits;
		addSign = signum;
	}

	//if both signs negative, make addsign pos
	//because negative + negative is addition
	//then change sign at end
	if(signum == -1 && N.signum == -1) {
		addSign = signum * N.signum;
	}

	//call sumList and if sum 0
	//return S
	sumList(S.digits, A, B, addSign);
	if(S.digits.length() == 0) {
		S.signum = 0;
		return S;
	}

	//otherwise normalize
	sign = normalizeList(S.digits);
	//if sign -1, noramlize again
	if (sign == -1) {
		normalizeList(S.digits);
	}

	//if both signs neg, set sign to pos
	if(signum == -1 && N.signum == -1) {
		S.signum = signum * N.signum;
	}
	else {
		S.signum = sign;
	}

	//more sign conditions
	if(signum == -1 && N.signum == -1) {
		S.signum = -1;
	}

	//if the front is 0, then clear BigInt
	if(S.digits.front() == 0) {
		S.makeZero();
	}
	return S;
}

//subtracts 2 BigInts by negating B then calling add
BigInteger BigInteger::sub(const BigInteger& N) const {
	BigInteger A = *this;
	BigInteger B = N;
	BigInteger S;

	int compare = this->compare(N);

	//if both numbers same, then return 0
	if(compare == 0) {
		S.signum = 0;
		return S;
	}

	//otherwise negate B, and add
	B.negate();
	S = A.add(B);

	//if this smaller, set sign to -1
	if(signum == -1 && N.signum == 1 && compare == -1) {
		S.signum = -1;
	}
	return S;
}

//multiplies 2 BigInts 
BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger A = N;
	int num = 0;
	BigInteger C;

	//if either 0, return 0;
	if(A.signum == 0 || N.signum == 0) {
		C.signum = 0;
		return C;
	}
	A.signum = 1;
	
	//copy first list, this, and scalar mult with number from N
	//then shift if first number and add using add function
	for (A.digits.moveBack(); A.digits.position() > 0; A.digits.movePrev()) {
		BigInteger B = *this;
		B.signum = 1;
		num = A.digits.peekPrev();
		scalarMultList(B.digits, num);
		if(A.digits.position() < A.digits.length()) {
			shiftList(B.digits, A.digits.length() - A.digits.position());
		}
		C = C.add(B);
	}
	C.signum = this->signum * N.signum;
	return C;
}


//operator overloading
std::ostream& operator<< (std::ostream& stream, BigInteger N) {
	return stream << N.BigInteger::to_string(); 
}

bool operator== (const BigInteger& A, const BigInteger& B) {
	return (A.BigInteger::compare(B) == 0);
}

bool operator< (const BigInteger& A, const BigInteger& B) {
	return (A.BigInteger::compare(B) == -1);
}
bool operator<=(const BigInteger& A, const BigInteger& B) {
	int compare = A.BigInteger::compare(B);
	return (compare == -1) || (compare == 0);
}

bool operator> (const BigInteger& A, const BigInteger& B) {
	return (A.BigInteger::compare(B) == 1);
}
bool operator>=(const BigInteger& A, const BigInteger& B) {
	int compare = A.BigInteger::compare(B);
	return (compare == 1) || (compare == 0);
}
BigInteger operator+(const BigInteger& A, const BigInteger& B) {
	return A.BigInteger::add(B);
}
BigInteger operator+=(BigInteger& A, const BigInteger& B) {
	A = A.BigInteger::add(B);
	return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
	return A.BigInteger::sub(B);
}
BigInteger operator-=(BigInteger& A, const BigInteger& B) {
	A = A.BigInteger::sub(B);
	return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
	return A.BigInteger::mult(B);
}
BigInteger operator*=(BigInteger& A, const BigInteger& B) {
	A = A.BigInteger::mult(B);
	return A;
}
