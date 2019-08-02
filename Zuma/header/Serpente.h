#ifndef SERPENTE_H
#define SERPENTE_H
#include "Pallina.h"
#include <string>
#include <fstream>
#include <vector>

class Serpente
{
    private:
        vector<Pallina*> palline;
        vector<pair<int, int>* > coordinate;
        Pallina* finta;
        int distanzaPalline;
        vector<pair<int, int>* > coppiaSpari;
    public:
        void stop();
        void scoppiaPalline(int p);
        Serpente();
        bool collideInTesta(HitBox* pallina);
        int getPosizionePrimaPallina();
        void caricaCoordinate();
        void generaPalline(int num, int tipi);
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