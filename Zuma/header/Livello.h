#ifndef LIVELLO_H
#define LIVELLO_H
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string> 
#include "Event_queue.h"
#include "Buffer.h"
#include "Mouse.h"
#include "Rana.h"
#include "GestoreSpari.h"
#include "Serpente.h"
#include "PallinaRana.h"
#include "Schermata.h"
class Livello : public Schermata
{
    private:
        Serpente* serpy;
        GestoreSpari* gestoreSpari;
        vector<PallinaRana*> spari;
    public:
        Livello();
        ~Livello();
        void caricaFont() override;
        void creaScrittaPunteggio();
        void stampaScrittaPunteggio(const int& p);
        void generaPalline(int,int);
        void caricaCoordinate();
        void livello_base();
};

#endif