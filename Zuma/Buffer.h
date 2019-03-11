#ifndef BUFFER_H
#define BUFFER_H
#include "Sfondo.h"
class BUFFER
{
    public:
    ~BUFFER()
    {
        al_destroy_bitmap(buffer);
    }

    bool aggiungiImmagine(const char* immagine, int X, int Y, float scale);
    BUFFER(const char* immagine);
    bool stampaSfondo();
    bool stampaBuffer();
    
    protected:
        int bufferL=1024, bufferA=768;
        ALLEGRO_BITMAP* buffer;
        const char* sfondo;
};


#endif