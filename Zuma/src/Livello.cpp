#include "../header/Livello.h"

extern int wGlobal;
extern int hGlobal;

Livello::Livello(){}

Livello::~Livello()
{
    delete serpy;
    delete gestoreSpari;
}

void Livello::livello_base()
{
    serpy = new Serpente();
    gestoreSpari= new GestoreSpari();

    serpy->generaPalline(100,6);


    bool redraw=0;
    BUFFER b("../image/Sfondo.jpg");
            
    Mouse m;
    Rana rana(512,384);
    
    event_queue.start(30);
    
    
    int flushh=0,  sizeCoord=serpy->getSizeCoordinate();
    
    ALLEGRO_EVENT ev; 
    bool ESCIPLS=0;
            
    b.stampaSfondo();
    
    while(serpy->getPosizionePrimaPallina()<sizeCoord)
    {            
        ev = event_queue.evento();

        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            m.setX(ev.mouse.x);
            m.setY(ev.mouse.y);           
        }
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            gestoreSpari->inserisciSparo(rana.getPallina());
        }

        if(redraw && event_queue.empty())
        {  
            redraw=0;
                    
            b.stampa(1);    

            rana.stampa(m.getX(), m.getY());  

            serpy->gestisciMovimento();
            gestoreSpari->collisioneSparo(*serpy) ;
            

            
            gestoreSpari->nelloSchermo(b);
            gestoreSpari->stampa();       
            
            
            
            serpy->stampa();
            
                 
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }

        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    event_queue.stop();
                    exit(0);
                break;
            }
        }
        
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw=1;
        }
                
        if((flushh++)%400==0)
            event_queue.flusha();
                
                 
               
    }

        event_queue.stop();
}