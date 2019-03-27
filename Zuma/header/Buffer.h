#ifndef BUFFER_H
#define BUFFER_H
#include "HitBox.h"




class BUFFER : public HitBox
{
    public:
    ~BUFFER();
    void aggiungiImmagine(HitBox*);
    BUFFER(const char* immagine);
    BUFFER(string immagine);
    bool stampaSfondo();
    void stampa(bool contr) override;
    
    protected:
        ALLEGRO_BITMAP* buffer;

};
#endif
