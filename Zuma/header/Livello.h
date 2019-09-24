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
#include "Suono.h"

enum MODALITA{CLASSICA=1, MOSSE=2, TEMPO=3};
enum ESITO{TORNAMENU = 1, VAIAVANTI = 2, HAIPERSO = 3};

class Livello : public Schermata
{
    private:
        Menu* menu;
        Serpente* serpy;
        GestoreSpari* gestoreSpari;
        vector<PallinaRana*> spari;

        int numPalline;
        int numColori;
        int ranax;
        int ranay;
        int numero;
        MODALITA modalita;

        int vita = 3;
        int puntiGioco = 0;
    public:
        const int NUM_LIVELLI = 3;
        Livello();
        ~Livello();

        void stampaFinale(const bool& vinto, Suono*& music);

        void datiLivello(const int& m,const int& n);
        void caricaFont() override;
        void azzeraPunti();
        void resetVite();
        void creaScrittaPunteggio();
        void stampaScrittaPunteggio(const int& p, const double& tempo, const int& numMosse);
        void generaPalline(int,int);
        void caricaCoordinate();
        void endLivello(const int& puntiGioco);
        int livello_base(Suono*&,const int& modalita =1 , const int& numero = 1);
        bool gameOver(const double& tempo=0, const int& numMosse=0);
};

#endif