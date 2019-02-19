/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_primitives -o Zuma prova
*/
#define IMMAGINE_SFONDO "sfondo.jpg"
#include "Buffer.h"



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
    BUFFER b(lol.getDisplay(), IMMAGINE_SFONDO);
    al_flip_display();
    al_rest(5);

    return 0;
}   

