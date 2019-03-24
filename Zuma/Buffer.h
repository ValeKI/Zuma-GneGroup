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
    BUFFER():HitBox("",0,0,1){buffer=nullptr;}
    BUFFER(const char* immagine);
    BUFFER(string immagine);
    bool stampaSfondo();

    void stampa(bool contr) override;
    
    protected:
        ALLEGRO_BITMAP* buffer;

};
#endif
