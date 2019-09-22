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

void Livello::azzeraPunti()
{
    puntiGioco=0;
}

void Livello::resetVite()
{
    vita = 3;
}

void Livello::stampaScrittaPunteggio(const int& num, const int& p, const int& modalita, const double& tempo, const int& numMosse)
{
    string stampa = "Mod: ";

    switch(modalita)
    {
        case 1:
            stampa += "Classica";
        break;


        case 2:
            stampa+="Mosse";
        break;


        case 3:
            stampa += "Tempo";
        break;
        
        default: 
        break;
    }

    stampa = " Liv: " + to_string(num) + "     Vita: " + to_string(vita) + "                 Punti: " + to_string(puntiGioco + p) + "            Pausa: premi p         ";

    if(modalita == int(TEMPO))
    {
        stampa += "Tempo: " + to_string(int(tempo))+ "sec su 90sec";
    }
    else if(modalita == int(MOSSE))
    {
        stampa += "Mosse: " + to_string(numMosse) + " su 65";
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
    int numPalline;
    int numColori;

    event_queue.stop();
    serpy = new Serpente();
    gestoreSpari= new GestoreSpari();

    switch(numero)
    {
        case 1:
        numPalline = 35;
        numColori = 4;
        break;


        case 2:
        numPalline = 45;
        numColori = 6;
        break;

        default:
        break;
    }
    serpy->generaPalline(numPalline,numColori, modalita, numero);


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
    int puntiAttuali = 0;

    while(gameOver(numero,modalita,end-start,numMosse) && !serpy->empty() && serpy->getPosizionePrimaPallina()<sizeCoord && sceltaMenu!=2)
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
            
            stampaScrittaPunteggio(numero, serpy->getPoint(), modalita, end-start, numMosse);
            if(puntiGioco + serpy->getPoint() != puntiAttuali &&  puntiGioco + serpy->getPoint() !=0 && puntiGioco + serpy->getPoint() % 800 == 0 )
            {
                puntiAttuali = puntiGioco + serpy->getPoint();
                al_draw_text(font, al_map_rgb(255,255,255), b->getX()+b->getLunghezza()/2, b->getY()+b->getAltezza()/2, ALLEGRO_ALIGN_CENTER, "Vita Bonus: +1!");
                vita++;
            }
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

    int r=2;

    if(sceltaMenu!=2)
    {
        music->stopLevel1();
        al_rest(0.5);
        if(serpy->empty())
        {
            r=3;
            music->playWin();
            delete b;
            b = new BUFFER("../image/win.jpg");
            b->stampaSfondo();
            b->stampa(1);
            al_flip_display();
            al_rest(5.0);

            //cout << bool(music->getMenu()) << endl;
        }
            
        else
        {
            if(vita > 0)
            {
                vita--;
                r = 4;
            }

            music->playGameOver();
            delete b;
            b = new BUFFER("../image/lost.png");
            b->stampaSfondo();
            b->stampa(1);
            al_flip_display();
            
        }
        al_rest(2.1);
        music->playMenu();
    }
    //if(music->getMenu())
    
    puntiGioco+=serpy->getPoint();

    delete serpy; serpy = nullptr;
    delete gestoreSpari; gestoreSpari = nullptr;

    

    return r;
}

bool Livello::gameOver(const int& num, const int& modalita, const double& tempo, const int& numMosse)
{
    switch (MODALITA(modalita))
    {
    case TEMPO:
        return (int(tempo)<=90);
        break;

    case MOSSE:
        return numMosse<=66;
        default:
        break;
    }

    return true;
}