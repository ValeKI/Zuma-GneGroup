#include "../header/GestoreSpari.h"

void GestoreSpari::inserisciSparo(PallinaRana* sparo)
{
    spari.push_back(sparo);
}

void GestoreSpari::collisioneSparo(Serpente& serpy)
{
    for(int j=0; j<spari.size(); j++)
        serpy.toccaSparo(spari[j]);
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
        if( !b.collisione(*it) )
        {
            delete *it;
            it=spari.erase(it);
            break;
        }  
    }
}