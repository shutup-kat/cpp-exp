#include "MerchantGuild.h"
using namespace std;

MerchantGuild::MerchantGuild(int size)
{
    numMem = 0;
    guildSize = size;
    members = new Merchant[guildSize];
    if(guildSize < 1)
    {
        guildSize = 10;
    }
}

MerchantGuild::MerchantGuild(const MerchantGuild &copy)
{
    numMem = copy.numMem;
    guildSize = copy.guildSize;
    members = new Merchant[guildSize];
    for(int k=0; k<numMem; k++)
    {
        members[k] = Merchant(copy.members[k]);
    }
}

MerchantGuild::~MerchantGuild()
{
    delete[] members;
}

MerchantGuild &MerchantGuild::operator=(const MerchantGuild &other)
{
    if(this != &other)
    {
        guildSize = other.guildSize;
        numMem = other.numMem;
        if(members != nullptr)
        {
            delete[] members;
            members = new Merchant[guildSize];
            for(int k=0; k<numMem; k++)
            {
                members[k] = Merchant(other.members[k]);
            }
        }
    }
    return *this;
}

void MerchantGuild::addMember(Merchant newM)
{
   if(numMem < guildSize)
   {
       members[numMem] = newM;
       numMem++;
   }
   else{
       cout << "Guild is full." << endl;
   }
}


Merchant *MerchantGuild::getMembers()
{
    return members;
}

