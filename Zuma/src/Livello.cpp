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


void Livello::stampaScrittaPunteggio(const int& p, const int& modalita, const double& tempo, const int& numMosse)
{
    string stampa = "Point: " + to_string(p+0) + " Pause: press p ";

    if(modalita == int(TEMPO))
    {
        stampa += "Tempo: " + to_string(int(tempo))+ "sec su 60sec";
    }
    else if(modalita == int(MOSSE))
    {
        stampa += "Mosse: " + to_string(numMosse) + " su 50";
    }

    al_draw_text(font, al_map_rgb(255,255,255), b->getX(), b->getY(), ALLEGRO_ALIGN_LEFT, stampa.c_str());
}

int Livello::livello_base(  Suono*& music ,const int& modalita, const int& numero)
{
    if(music->getMenu())
    {
        music->stopMenu();
        //al_rest(2.0);
        music->playLevel1();
    }
   
    int numMosse = 0;


    event_queue.stop();
    serpy = new Serpente();
    gestoreSpari= new GestoreSpari();

    serpy->generaPalline(40,6, modalita, numero);


    bool redraw=0;
    b = new BUFFER("../image/Livello_" + to_string(modalita) + "_" + to_string(numero) +".jpg");

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

    while(gameOver(modalita,end-start,numMosse) && !serpy->empty() && serpy->getPosizionePrimaPallina()<sizeCoord && sceltaMenu!=2)
    {     
        ev = event_queue.evento();

        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            m.setX(ev.mouse.x);
            m.setY(ev.mouse.y);           
        }
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(pausa)
            { 
                pausa = 0;
                if(music->getMenu())
                {
                 music->stopMenu();
                //al_rest(2.0);
                music->playLevel1();
                }
            }
                
            else
            {
                numMosse++;
                gestoreSpari->inserisciSparo(rana.getPallina());
            }
        }

        if(redraw && event_queue.empty())
        {  
            redraw=0;
                    
            b->stampa(1);    
            
            stampaScrittaPunteggio(serpy->getPoint(), modalita, end-start, numMosse);

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
                    sceltaMenu = menu->menuPausa(music);
                    pausa = 1;
                break;
                case ALLEGRO_KEY_SPACE:
                    if(pausa)
                    {  
                        pausa = 0;
                        if(music->getMenu())
                        {
                        music->stopMenu();
                        //al_rest(2.0);
                        music->playLevel1();
                        }  
                    }
                    else
                    {
                        numMosse++;
                        gestoreSpari->inserisciSparo(rana.getPallina());
                    }
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

    if(sceltaMenu!=2)
    {
        music->stopLevel1();
        al_rest(0.5);
        if(serpy->empty())
        {
            music->playWin();
            cout << "Hai vinto!\n";
            
        }
            
        else
        {
            music->playGameOver();
            cout << "Hai perso!\n";
            
        }
        al_rest(2.5);
        music->playMenu();
    }
    //if(music->getMenu())
    
    
    event_queue.flusha();
    
     
   
    delete serpy; serpy = nullptr;
    delete gestoreSpari; gestoreSpari = nullptr;

    return 2;
}

bool Livello::gameOver(const int& modalita, const double& tempo, const int& numMosse)
{
    switch (MODALITA(modalita))
    {
    case TEMPO:
        return (int(tempo)<=60);
        break;

    case MOSSE:
        return numMosse<=50;
    
    default:
        break;
    }

    return true;
}