#ifndef LIVELLO_H
#define LIVELLO_H
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Event_queue.h"
#include "Buffer.h"
#include "Mouse.h"
#include "Rana.h"
#include "GestoreSpari.h"
#include "Serpente.h"
#include "PallinaRana.h"
class Livello 
{
    private:
        Serpente* serpy;
        GestoreSpari* gestoreSpari;

        
        vector<PallinaRana*> spari;
        
        Event_queue event_queue;
    public:
        Livello();
        ~Livello();

        void generaPalline(int,int);
        void caricaCoordinate();
        void livello_base();
};

#endif