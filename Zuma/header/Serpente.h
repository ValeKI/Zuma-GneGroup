#ifndef SERPENTE_H
#define SERPENTE_H
#include "Pallina.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

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
        int getPoint() const;
        bool empty();
        void fixVelocita();
        void stop();
        void scoppiaPalline(int p);
        Serpente();
        bool collideInTesta(HitBox* pallina);
        int getPosizionePrimaPallina();
        void caricaCoordinate(const int& modalita, const int& numero);
        void generaPalline(const int& num, const int& tipi, const int& modalita, const int& numero);
        void stampa();
        ~Serpente();
        int getSizeCoordinate();
        bool toccaSparo(Pallina* sparo, int j);
        void gestisciMovimento();
        int cambiaDirezioneASinistraDi(int,DIREZIONE);
        int cambiaDirezioneADestraDi(int, DIREZIONE);
        int cercaIndice(int c, bool first);
        void cambiaDirVel( int , DIREZIONE, int );
};


#endif