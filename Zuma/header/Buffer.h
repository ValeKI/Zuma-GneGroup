#ifndef BUFFER_H
#define BUFFER_H
#include "HitBox.h"




class BUFFER : public HitBox
{
    public:
        BUFFER(const char* immagine);
        BUFFER(string immagine);
        ~BUFFER();

        int getGlobalScale() const;
        
        // permettere di aggiungere un immagine al buffer
        void aggiungiImmagine(HitBox*);

        // stampa il buffer sullo sfondo
        void stampa(bool contr) override;

        // verifica la collisione col buffer
        bool collisione(const HitBox* obj) const override;
        
        // stampa l'immagine del buffer sul buffer
        bool stampaSfondo();
    
    private:
        ALLEGRO_BITMAP* buffer;

};
#endif
