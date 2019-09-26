#ifndef MENU_H
#define MENU_H

#include "Event_queue.h"
#include "Buffer.h"
#include "Schermata.h"
#include "Suono.h"

/*
    Questa classe crea i vari menù presenti nel gioco,
    compresa la schermata di presentazione e di guida.
*/
class Menu : public Schermata
{
    private:
        vector<string> scelte;
    
    protected:
        int menu1();
        void menu2(string nomeImm, int tasto);
   
    public:
        Menu();
        ~Menu();
        
        void caricaFont() override;
        void tutorial();//metodo per la guida al gioco
        void zuma();//schermata iniziale di presentazione
        int menuPausa(Suono*);
        int menuPricipale(Suono* );//scelta della modalità
        int menuLivelli();
        //collisione della scelta con mouse e/o tastiera
        bool collideText(const int& mx, const int& my, string& s, const int& px, const int& py);
};

#endif