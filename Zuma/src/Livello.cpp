#include "../header/Livello.h"

extern int wGlobal;
extern int hGlobal;

Livello::Livello():Schermata()
{
    caricaFont();
}

Livello::~Livello()
{
    
}

void Livello::caricaFont()
{
    font = al_load_font("../ttf/Lato-Black.ttf", 26*wGlobal/1024., ALLEGRO_KEEP_BITMAP_FORMAT);
}


void Livello::stampaScrittaPunteggio(const int& p)
{
    string stampa = "Point: " + to_string(p+0) + " Pause: press p";
    al_draw_text(font, al_map_rgb(255,255,255), b->getX(), b->getY(), ALLEGRO_ALIGN_LEFT, stampa.c_str());
}

void Livello::livello_base()
{
    serpy = new Serpente();
    gestoreSpari= new GestoreSpari();

    serpy->generaPalline(40,6);


    bool redraw=0;
    b = new BUFFER("../image/Sfondo.jpg");

    Rana rana(512,384);
    
    event_queue.start(60);
    

    int flushh=0,  sizeCoord=serpy->getSizeCoordinate();
    
    ALLEGRO_EVENT ev; 
    bool ESCIPLS=0;
            
    b->stampaSfondo();
    
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
                    
            b->stampa(1);    
            
            stampaScrittaPunteggio(serpy->getPoint());

            rana.stampa(m.getX(), m.getY());  
            serpy->gestisciMovimento();

            gestoreSpari->collisioneSparo(*serpy);
            gestoreSpari->nelloSchermo(*b);
            
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
    delete serpy; serpy = nullptr;
    delete gestoreSpari; gestoreSpari = nullptr;
    
    //delete b;

}