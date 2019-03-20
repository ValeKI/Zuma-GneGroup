#ifndef BUFFER_H
#define BUFFER_H
#include "HitBox.h"




class BUFFER : public HitBox
{
    public:
    ~BUFFER()
    {
        if(buffer!=nullptr)
            al_destroy_bitmap(buffer);
    }


    void aggiungiImmagine(HitBox*);
    BUFFER(const char* immagine);
    BUFFER(string immagine);
    bool stampaSfondo();

    void stampa() override;
    
    protected:
        ALLEGRO_BITMAP* buffer;

};
#endif
