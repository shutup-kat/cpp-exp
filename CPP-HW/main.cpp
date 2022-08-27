#include <iostream>
#include "MerchantGuild.h"
#include "merchant.h"
#include "antique.h"
using namespace std;

int main() {

   cout << "KEY: " << "True is: " << true << "  False is: " << false << endl << endl;
   
   // antique tests
	Antique a1, a2;

	a1.setName("fork");
	a1.setPrice(3.25);
	a2.setName("knife");
	a2.setPrice(2.50);
	cout << "antique test" << endl;
	Antique a3 = a1 + a2;

	cout << a3.toString() << endl;
	cout << bool(a1 == a2) << " : Ans=0" << endl;
	cout << bool(a1 == a1) << " : Ans=1" << endl;
	
	// merchant tests
	Merchant m1(1.2), m2(2.5);
	cout << "merchant test" << endl;
	m1.addAntique(a1, 2);
	m1.addAntique(a2, 5);
	m2.addAntique(a3, 3);

	cout << bool(m1 == m2) << " : Ans=0" << endl;
	cout << bool(m1 == m1) << " : Ans=1" << endl;

	Merchant m3(m1);
	cout << bool(m3 == m1) << " : Ans=1" << endl;
	
	//merchant guild tests
	MerchantGuild mg1;
	cout << "merchant guild tests" << endl;

	mg1.addMember(m1);
	
	Merchant* tmp = mg1.getMembers();
	cout << bool(tmp[0] == m1) << " : Ans=1" << endl;
	
	mg1.addMember(m2);
	
	tmp = mg1.getMembers();
	cout << bool(tmp[0] == m1 && tmp[1] == m2) << " : Ans=1" << endl;

   return 0;
}