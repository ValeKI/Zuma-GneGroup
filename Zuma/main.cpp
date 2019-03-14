/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_primitives -o Zuma
*/
#define IMMAGINE_SFONDO "image/Sfondo.jpg"
#include "Buffer.h"
#include <string>
#include <allegro5/allegro5.h>



int main()
{


    if(!al_init())
    {
        cerr << "Failed to initialite allegro - 1";
        return -1;
    }
    
    if(!al_init_image_addon())
    {
        cerr << "Failed to initialite image addon - 2 ";
        return -1;
    }
    SFONDO lol; 
    BUFFER b(IMMAGINE_SFONDO);

    int x=0;
    for(;x<10; x++)
    {
        b.stampaSfondo();
        b.aggiungiImmagine((string("image/Classica_"+to_string(x%2)+".jpg")).c_str(),340,350,1);
        b.aggiungiImmagine((string("image/Tempo_"+to_string(x%2)+".jpg")).c_str(),340,450,1);
        b.aggiungiImmagine((string("image/Mosse_"+to_string(x%2)+".jpg")).c_str(),340,550,1);
        b.stampaBuffer();
        al_flip_display();
        al_rest(0.2);
    }




    return 0;
}