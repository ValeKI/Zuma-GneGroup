#ifndef SERPENTE_H
#define SERPENTE_H
#include "Pallina.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

enum{DESTRA = 0, SINISTRA = 1};

class Serpente
{
    private:
        vector<Pallina*> coloreUguale;
        vector<Pallina*> palline;
        vector<pair<int, int>* > coordinate;
        vector<pair<int, int>* > coppiaSpari;
        Pallina* finta;
        int distanzaPalline;
        int point = 0;
    public:
        Serpente();
        ~Serpente();

        int getPoint() const;
        int getPosizionePrimaPallina() const;
        int getSizeCoordinate() const;

        bool empty();
        void fixVelocita();
        void stop();
        void scoppiaPalline(int p);

        bool collideInTesta(HitBox* pallina);
        
        void caricaCoordinate(const int& modalita, const int& numero);
        void generaPalline(const int& num, const int& tipi, const int& modalita, const int& numero);
        void stampa();

        bool toccaSparo(Pallina* sparo, int j);
        void gestisciMovimento();
        int cambiaDirezioneASinistraDi(int,DIREZIONE);
        int cambiaDirezioneADestraDi(int, DIREZIONE);
        int cercaIndiceCoppiaSpari(const int& indice, const int& quale);
        void cambiaDirVel( int , DIREZIONE, int );
};


#endif