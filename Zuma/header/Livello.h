#ifndef LIVELLO_H
#define LIVELLO_H
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string> 
#include "Rana.h"
#include "GestoreSpari.h"
#include "Menu.h"

enum MODALITA{CLASSICA=1, MOSSE=2, TEMPO=3};

class Livello : public Schermata
{
    private:
        Menu* menu;
        Serpente* serpy;
        GestoreSpari* gestoreSpari;
        vector<PallinaRana*> spari;
    public:
        const int NUM_LIVELLI = 3;
        Livello();
        ~Livello();
        void caricaFont() override;

        void creaScrittaPunteggio();
        void stampaScrittaPunteggio(const int& p, const int& modalita, const double& tempo, const int& numMosse);
        void generaPalline(int,int);
        void caricaCoordinate();
        int livello_base(const int& modalita=1, const int& numero=1);
        bool gameOver(const int& modalita=1, const double& tempo=0, const int& numMosse=0);
};

#endif