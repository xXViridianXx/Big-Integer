/********************************************************************************* 
* BigIntegerTest file
*********************************************************************************/
#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "BigInteger.h"
#include "List.h"

using namespace std;

int main() {
   string num1 = "232456789876543567898765434567890876543456789876543567897654345678";
   string num2 = "-7426527652476543765050627483965748365247695764204572620856082745678260824576";
   string num3 = "000000000000000000";
   string num4 = "89827435629874569284566538374957473847464747";

   //BigIntegers being created;
   BigInteger A = BigInteger(num1);
   BigInteger B = BigInteger(num2);
   BigInteger C = BigInteger(num3);
   BigInteger D = BigInteger(num4);

   cout << endl << endl;
	
   //prinint out BigInts
   cout << "A:  " << A << endl;
   cout << "B:  " << B << endl;
   cout << "C:  " << C << endl;
   cout << "D:  " << D << endl;
   cout << endl << endl;
	
   //ops
   BigInteger E = A + C;
   BigInteger F = A - B;
   BigInteger G = B - B; // equals 0
   BigInteger H = D - A;
   BigInteger I = C * D;
   BigInteger J = A * D;
   BigInteger K = C * C;
	
   //printing out ops
   cout << " A + C: " << A + C << endl;
   cout << " A - B: " << A - B << endl;
   cout << " B - B: " << B - B << endl;
   cout << " D - A: " << D - A << endl;
   cout << " C * D: " << C * D << endl;
   cout << " A * D: " << A * D << endl;
   cout << " C * C: " << C * C << endl <<endl;

   cout << " A * B: " << A * B << endl;
   cout << " B * B: " << B * B << endl;
   cout << " D * A: " << D * A << endl;
   cout << " D * D: " << D * D << endl;
   cout << " D * B: " << D * B << endl;
	
   //testing comparisons
   cout << "(A == C): " << ((A == C)?"True":"False") << endl;
   cout << "(C < A):  " << ((C < A)? "True":"False") << endl;
   cout << "(A <= B): " << ((A <= B)?"True":"False") << endl;
   cout << "(C == C):  " << ((C == C)? "True":"False") << endl;
   cout << "(A > D): " << ((A > D)?"True":"False") << endl;
   cout << "(B >= D):  " << ((B >= D)? "True":"False") << endl;
   cout << "(D >= D): " << ((D >= D)?"True":"False") << endl << endl;

   cout << "(C * C == C) = " << ((K==C)?"True":"False") << endl;
   cout << "(A + C > C) = " << ((E>C)?"True":"False") << endl << endl;
	
   //testing ops=
   C += D;
   B *= A;
   D *= B;
   cout << "C = " << C << endl;
   cout << "B = " << B << endl;
   cout << "D = " << D << endl;
   cout << endl;

   //creating huge number
   cout << "A*B*D*F*H*J: "<<A*B*D*F*H*J << endl << endl;
   cout << "A*B*C*D*F*G*H*I*J*K: "<<A*B*C*D*F*G*H*I*J*K << endl << endl; //should be 0

   cout << endl;

   // tests with try and catch
   try{
      BigInteger T = BigInteger("");
   }
   catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing on" << endl;
   }
   try{
      BigInteger T = BigInteger("-");
   }
   catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing on" << endl;
   }
   try{
      BigInteger T = BigInteger("45678987876578976589656886g654789876578965");
   }
   catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing on" << endl;
   }
   try{
      BigInteger T = BigInteger("0000000000000000000000000000000024f");
   }
   catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing on" << endl;
   }

   cout << endl;

   return EXIT_SUCCESS;

	return 0;
}

