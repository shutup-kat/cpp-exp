#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

#ifndef antique_h
#define antique_h

class Antique {
private:
    string name;
    float price;
public:
    Antique();
    bool operator==(const Antique &other);
    Antique operator+(const Antique &other);
    string toString();
    void setName(string NAME);
    void setPrice(float PRICE);
    string getName() const;
    float getPrice() const;
};

#endif /* antique_h */
