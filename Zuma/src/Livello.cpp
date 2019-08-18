#include "../header/Livello.h"

extern int wGlobal;
extern int hGlobal;

Livello::Livello():Schermata()
{
    menu = nullptr;
    b = nullptr;
    font = nullptr;
    caricaFont();
}

Livello::~Livello()
{
    if(menu!=nullptr)
        delete menu; 
}

void Livello::caricaFont()
{
    font = al_load_font("../ttf/Lato-Black.ttf", 26*wGlobal/1024., ALLEGRO_KEEP_BITMAP_FORMAT);
}


void Livello::stampaScrittaPunteggio(const int& p, const int& modalita, const double& tempo)
{
    string stampa = "Point: " + to_string(p+0) + " Pause: press p";

    if(modalita == int(TEMPO))
    {
        stampa += " Tempo: " + to_string(int(tempo));
    }

    al_draw_text(font, al_map_rgb(255,255,255), b->getX(), b->getY(), ALLEGRO_ALIGN_LEFT, stampa.c_str());
}

int Livello::livello_base(const int& modalita, const int& numero)
{
    event_queue.stop();
    serpy = new Serpente();
    gestoreSpari= new GestoreSpari();

    serpy->generaPalline(40,6, modalita, numero);


    bool redraw=0;
    b = new BUFFER("../image/Sfondo.jpg");

    Rana rana(512,384);
    
    event_queue.start(60);
    

    int sizeCoord=serpy->getSizeCoordinate();
    
    ALLEGRO_EVENT ev; 
    bool pausa = 0;
    int sceltaMenu=0;
            
    b->stampaSfondo();
    menu = new Menu();

    double start = al_get_time();
    double end = start;

    while(serpy->getPosizionePrimaPallina()<sizeCoord && sceltaMenu!=2)
    {     
        cout << "Tempo: " << end-start << endl;
        
        ev = event_queue.evento();


        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            m.setX(ev.mouse.x);
            m.setY(ev.mouse.y);           
        }
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(pausa)
                pausa = 0;
            else
                gestoreSpari->inserisciSparo(rana.getPallina());
        }

        if(redraw && event_queue.empty())
        {  
            redraw=0;
                    
            b->stampa(1);    
            
            stampaScrittaPunteggio(serpy->getPoint(), modalita, end-start);

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
                case ALLEGRO_KEY_P:
                    sceltaMenu = menu->menuPausa();
                    pausa = 1;
                break;
                case ALLEGRO_KEY_SPACE:
                    gestoreSpari->inserisciSparo(rana.getPallina());
                break; 
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
        
        end = al_get_time();
    }

    delete serpy; serpy = nullptr;
    delete gestoreSpari; gestoreSpari = nullptr;

    return sceltaMenu;
}