/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_primitives -o Zuma && ./Zuma

    TO DO list:
    event_queue ---  
    collisione
    menu


*/
#define IMMAGINE_SFONDO "image/Sfondo.jpg"
#include "ScrittaMenu.h"
#include "Buffer.h"
#include "Event_queue.h"
#include "Sfondo.h"
#include <string>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>

int wGlobal=1024;
int hGlobal=768;

int main(int argc, char **argv)
{
   /* ::wGlobal=640;
    ::hGlobal=480; */

    if(!al_init())
    {
        cerr << "Failed to initialishishte allegro - 1";
        return -1;
    }
    
    if(!al_init_image_addon())
    {
        cerr << "Failed to initialite image addon - 2 ";
        return -1;
    }


    SFONDO sfondo;
    BUFFER b(IMMAGINE_SFONDO);
    HitBox* tempo= new ScrittaMenu("image/1_Tempo.jpg",300,300,1);
    HitBox* classica = new ScrittaMenu("image/1_Classica.jpg",300,425,1);
    HitBox* mosse = new ScrittaMenu("image/1_Mosse.jpg",300,560,1);
    //cout << ciao->getY();
for(int i=0; i<30; i++)
{
    b.stampaSfondo();

    dynamic_cast<ScrittaMenu*>(tempo)->reazione();
    dynamic_cast<ScrittaMenu*>(classica)->reazione();
    dynamic_cast<ScrittaMenu*>(mosse)->reazione();

    b.aggiungiImmagine(tempo);
    b.aggiungiImmagine(classica); 
    b.aggiungiImmagine(mosse); 
    
    b.stampa(1);
    b.stampa(1);
    b.stampa(1);
   

    al_flip_display();

    al_rest(0.1);
}
    delete tempo;
    delete classica;
    delete mosse;
    return 0;
}