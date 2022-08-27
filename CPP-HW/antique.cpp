#include "antique.h"

using namespace std;

void Antique::setName(string NAME) {
	name = NAME;
}

void Antique::setPrice(float PRICE) {
	price = PRICE;
}

string Antique::getName() const {
	return name;
}

float Antique::getPrice() const {
	return price;
}

string Antique::toString() {
	//string price_s;
	ostringstream streamObj;

	streamObj << fixed;
	streamObj << setprecision(2);

	streamObj << price;
	return name + ": $" + streamObj.str();
}

Antique::Antique() {
	name = "";
	price = 0;
}

//put == operator overload here
bool Antique::operator==(const Antique &other)
{
    return(name==other.getName()) && (price==other.getPrice());
}

//put + operator overload here
Antique Antique::operator+(const Antique &other)
{
    Antique temp;
    
    temp.price = price+other.price; //(temp.Price + temp.getPrice);
    temp.name = name+" and "+other.name; //(temp.Name + " and " + other.getName);
    return temp;
}

