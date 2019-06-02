#include "../header/GestoreSpari.h"

void GestoreSpari::inserisciSparo(PallinaRana* sparo)
{
    spari.push_back(sparo);
}

bool GestoreSpari::collisioneSparo(Serpente& serpy)
{
    for(int j=0; j<spari.size(); j++)
    {
        if(serpy.toccaSparo(spari[j]))
        {
            spari.erase(spari.begin()+j);
            return true;
        }
    }
    return false;
}

void GestoreSpari::stampa()
{
    for(auto i:spari)
    {
        i->movimento();
        i->stampa(1);
    }
}

void GestoreSpari::nelloSchermo(BUFFER& b)
{ 
   for(vector<PallinaRana*>::iterator it = spari.begin(); it!=spari.end(); ++it)
    {
        if(!b.collisione(*it) )
        {
            delete *it;
            it=spari.erase(it);
            break;
        }
    }
}  
    
    


GestoreSpari::~GestoreSpari()
{
    for(int i=0; i<spari.size(); i++)
        delete spari[i];
}