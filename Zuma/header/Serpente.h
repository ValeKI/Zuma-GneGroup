#ifndef SERPENTE_H
#define SERPENTE_H
#include "Pallina.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

enum{DESTRA = 0, SINISTRA = 1};
/*Questa classe rappresenta l'insieme di palline */
class Serpente
{
    private:
        /* 
            insieme di palline sulle quali sara' tentato uno scoppiaPalline 
            quando si riuniranno con una dello stesso colore
        */
        vector<Pallina*> coloreUguale;
        vector<Pallina*> palline;
        vector<pair<int, int>* > coordinate;
        /* 
            coppia di indici:
                - first rappresenta l'indice di una pallina del serpente 
                        che è stata toccata da uno sparo;
                - second l'indice dello sparo
            lo sparo sara' inserito dopo la pallina
        */
        vector<pair<int, int>* > coppiaSpari;
        Pallina* finta;
        int distanzaPalline;
        int point = 0;

        int numColoriDisponibili = 6;
        bool coloriDisponibili[NUMCOLORI]{false};
    protected:

        // resetta i colori a disposizione per la rana
        void azzeraColori();

        // in caso di palline sovvrapposte porta la pallina più a destra (più vicino a 0) alla distanza giusta
        void fixVelocita();
        
        // a partire dalla pallina p-esima vedi a destra e a sinistra le palline hanno lo stesso colore e falle esplodere
        void scoppiaPalline(int p);
        
        // crea una pallina immaginaria, serve per inserire una pallina in testa
        bool collideInTesta(HitBox* pallina);

        // setta la direzione data alle palline collegate a partire da 'in' verso sinistra (tendenzialmente palline.size())
        int cambiaDirezioneASinistraDi(int,DIREZIONE);

        // setta la direzione data alle palline collegate a partire da 'in' verso destra (tendenzialmente 0)
        int cambiaDirezioneADestraDi(int, DIREZIONE);
        
        /* 
            cerca se la posizione di una pallina è stata salvata in coppiaSpari, se a SINISTRA sarà l'indice del vector di palline se DESTRA l'indice di GestoreSpari
            se non la trova restituisce -2
        */
        int cercaIndiceCoppiaSpari(const int& indice, const int& quale) const;
        
        // cambia sia direzione che velocita' alle palline che si trovano alla destra dell'i-esima (tendenzialmente 0)
        void cambiaDirVel( int , DIREZIONE, int );

        // legge il percorso e lo adatta allo schermo
        void caricaCoordinate(const int& modalita, const int& numero);
    public:
        Serpente();
        ~Serpente();

        bool* getColoriDisponibili();
        int getNumColoriDisponibili();

        // restituisce il punteggio generato dagli scoppi
        int getPoint() const;

        // restituisce la posizione della prima pallina, e se non ci sono palline restituisce la size delle coordinate * 5 (l'importante è che sia più grande)
        int getPosizionePrimaPallina() const;

        // restituisce quante coordinate sono state lette
        int getSizeCoordinate() const;

        // ferma tutte le palline
        void stop();

        // stampa le palline, ma prima applica un fix. Conta anche i colori ancora disponibili che serviranno a Rana
        void stampa();

        // crea le palline in modo casuale
        void generaPalline(const int& num, const int& tipi, const int& modalita, const int& numero);
        
        // gestisce il criterio con il quale le palline si muovono. In caso di palline precedentemente staccate che si riattacano verifica se possono esplodere, ma dello stesso colore
        void gestisciMovimento();

        // se è vuoto il vector palline
        bool empty();

        // restituisce se uno sparo è stato inserito. Gestisce anche il suo inserimento        
        bool toccaSparo(Pallina* sparo, int j);
};


#endif