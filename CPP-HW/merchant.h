
#include "antique.h"
#include <iostream>
#include <fstream>

using namespace std;

#ifndef merchant_h
#define merchant_h

class Merchant {
private:
    Antique* antiques;
    int* quantities;
    int numAnt;
    float revenue;
public:
	Merchant();
	Merchant(float r);
	~Merchant();
	Merchant(const Merchant &copy);
	//== operator overload here; addAntique function here
    bool operator==(const Merchant& rhs);
    Merchant& operator=(const Merchant &kat);
    void addAntique(Antique object, int quantity);
};


#endif /* merchant_h */
