#include "merchant.h"

using namespace std;

//default constructor here
Merchant::Merchant()
{
    antiques = nullptr;
    quantities = nullptr;
    numAnt = 0;
    revenue = 0.0;
}

//constructor with only a float value
Merchant::Merchant(float r)
{
    revenue = r;
}

//destructor here; del ptr
Merchant::~Merchant()
{
    delete[] antiques;
    delete[] quantities;
}

//copy constructor
Merchant::Merchant(const Merchant &copy)
{
    revenue = copy.revenue;
    numAnt = copy.numAnt;
    antiques = new Antique[numAnt];
    quantities = new int[numAnt];
    for(int k=0; k<numAnt; k++)
    {
        antiques[k] = Antique(copy.antiques[k]);
        quantities[k] = copy.quantities[k];
    }
}

//==operator overload here, need flag bc bool func
bool Merchant::operator==(const Merchant& rhs)
{
    if(revenue == rhs.revenue)
    {
        for(int k=0; k<numAnt; k++)
        {
            if(quantities[k] != rhs.quantities[k])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}


//add antique here; TA: delete old anti and old quant, THEN save temps
void Merchant::addAntique(Antique items, int total)
{
    Antique* tempquan = new Antique[numAnt+1];
    int* tempanti = new int[numAnt+1];
    for(int k=0; k<numAnt; k++)
    {
        tempquan[k] = antiques[k];
        tempanti[k] = quantities[k];
    }
    tempquan[numAnt] = items;
    tempanti[numAnt] = total;
    
    delete[] antiques;
    delete[] quantities;
    
    antiques = tempquan;
    quantities = tempanti;
    //increment the size
    numAnt++;
}

Merchant &Merchant::operator=(const Merchant &kat)
{
    if(this != &kat)
    {
        revenue = kat.revenue;
        numAnt = kat.numAnt;
        if(antiques != nullptr)
        {
            delete[] antiques;
        }
        if(quantities != nullptr)
        {
            delete[] quantities;
        }
        antiques = new Antique[numAnt];
        quantities = new int[numAnt];
        for(int k=0; k<numAnt; k++)
        {
            antiques[k] = Antique(kat.antiques[k]);
            quantities[k] = kat.quantities[k];
        }
    }
    return *this;
}


