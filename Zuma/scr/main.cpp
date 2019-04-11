/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_primitives -o Zuma && ./Zuma

    TO DO list:
    collisione


*/
#define IMMAGINE_SFONDO "image/Sfondo.jpg"
#include "../header/ScrittaMenu.h"
#include "../header/Menu.h"
#include "../header/Sfondo.h"
#include "../header/Livello.h"
#include <string>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>

int wGlobal=1024;
int hGlobal=768;

int main(int argc, char **argv)
{
/*     ::wGlobal=640;
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
    Livello prova;

    prova.livello_base();


  //  HitBox buh;
    
    return 0;
}