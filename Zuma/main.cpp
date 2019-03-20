/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_primitives -o Zuma && ./Zuma
*/
#define IMMAGINE_SFONDO "image/Sfondo.jpg"
#include "ScrittaMenu.h"
#include "Buffer.h"
#include "Sfondo.h"
#include <string>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>

int wGlobal=1024;
int hGlobal=768;

const float FPS = 60;
enum MYKEYS{KEY_UP, KEY_DOWN, KEY_LEFT,KEY_RIGHT};
int main()
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
    HitBox* ciao= new HitBox("image/Moon.jpg",100,100,1);

    //cout << ciao->getY();

    b.stampaSfondo();
    b.aggiungiImmagine(ciao);
    b.stampa(1);
    al_flip_display();
    al_rest(1);

    delete ciao;
    return 0;
}