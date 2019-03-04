#include "Buffer.h"

bool BUFFER::stampaSfondo(ALLEGRO_DISPLAY* display)
{
    const char*& immagine=sfondo;
    ALLEGRO_BITMAP *load;
    
        if(!(buffer=al_create_bitmap(bufferL ,bufferA)   ) )
        {
            cerr << "Error to create buffer bitmap - 4";
            al_destroy_display(display);
            return 0;
        }
    
        if(!(load=al_load_bitmap(immagine)   ))
        {
            cerr << "Error to load the background - 5";
            al_destroy_bitmap(buffer);
            al_destroy_display(display);
            return 0;
        }

        ALLEGRO_BITMAP* prev_target=al_get_target_bitmap();
        al_set_target_bitmap(buffer);

        al_draw_scaled_bitmap
        (
            load,
            0, 0,                                // source origin
            al_get_bitmap_width(load),           // source width
            al_get_bitmap_height(load),          // source height
            0, 0,                                // target origin
            bufferL,
            bufferA,                        // target dimensions
            0                                    // flags
        );

        al_set_target_bitmap(prev_target); 
        al_destroy_bitmap(load);

}

bool BUFFER::stampaBuffer(ALLEGRO_DISPLAY* display)
{
    int displayW= al_get_display_width(display);
    int displayH= al_get_display_height(display);
    int sx = displayW/bufferL;
    int sy = displayH/bufferA;
    int scale = min(sx,sy);
    int scaleW= bufferL * scale;
    int scaleH= bufferA * scale;
    int scaleX= (displayW-scaleW)/2;
    int scaleY= (displayH-scaleH)/2;
    const char*& immagine=sfondo;
    

        al_draw_scaled_bitmap
        (
            buffer,
            0, 0,                                // source origin
            bufferL,                               // source width
            bufferA,                               // source height
            scaleX, scaleY,                      // target origin
            scaleW, scaleH,                      // target dimensions
            0                                    // flags
        );

        return 1;
}

BUFFER::BUFFER(const char* immagine)
{
    ALLEGRO_DISPLAY* display=al_get_current_display();
        sfondo=immagine;
        stampaSfondo(display);
        stampaBuffer(display);
}

bool BUFFER::aggiungiImmagine(const char* immagine, int X, int Y, float scale)
{
    ALLEGRO_BITMAP *load;
    if(!(load=al_load_bitmap(immagine)   ))
    {
        cerr << "Error to load an image - 62";
        return 0;
    }

    stampaSfondo(al_get_current_display());
    ALLEGRO_BITMAP* prev_target=al_get_target_bitmap();
    al_set_target_bitmap(buffer);

    al_draw_scaled_bitmap
    (
        load,
        0, 0,                                // source origin
        al_get_bitmap_width(load),           // source width
        al_get_bitmap_height(load),          // source height
        X, Y,                                // target origin
        al_get_bitmap_width(load)*scale,
        al_get_bitmap_height(load)*scale,        // target dimensions
        0                                    // flags
    );


    al_set_target_bitmap(prev_target); 
    al_destroy_bitmap(load);

    stampaBuffer(al_get_current_display());

    return 1;
}