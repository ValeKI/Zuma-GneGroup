/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_primitives -o Zuma
*/
#define IMMAGINE_SFONDO "menu.png.jpeg"
#define IMMAGINE_LOGO "image/Moon.jpg"
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
    BUFFER b(IMMAGINE_SFONDO);

    b.aggiungiImmagine(IMMAGINE_LOGO,900,5,0.5);
    al_flip_display();
    al_rest(2);

    return 0;
}