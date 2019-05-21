#ifndef BUFFER_H
#define BUFFER_H
#include "HitBox.h"




class BUFFER : public HitBox
{
    public:
        //BUFFER();
        BUFFER(const char* immagine);
        BUFFER(string immagine);
        ~BUFFER();

        void aggiungiImmagine(HitBox*);
        bool stampaSfondo();
        void stampa(bool contr) override;
        
    
    private:
        ALLEGRO_BITMAP* buffer;

};
#endif
