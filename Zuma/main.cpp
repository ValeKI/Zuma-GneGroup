/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_primitives -o Zuma
*/
#define IMMAGINE_SFONDO "image/Sfondo.jpg"
#define IMMAGINE_LOGO "image/Classica_"
#include "Buffer.h"
#include <string>



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
    for(;x<30; x++)
    {
        b.aggiungiImmagine(string(IMMAGINE_LOGO+to_string(x%2)+".jpg").c_str(),384,250,1);
    al_flip_display();
    al_rest(0.2);
    }




    return 0;
}