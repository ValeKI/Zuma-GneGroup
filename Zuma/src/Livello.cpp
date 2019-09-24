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

void Livello::stampaScrittaPunteggio(const int& p, const double& tempo, const int& numMosse)
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

    stampa += "     Liv: " + to_string(numero) + "     Vita: " + to_string(vita) + "     Punti: " + to_string(puntiGioco + p) + "     Pausa: premi p     ";

    if(modalita == int(TEMPO))
    {
        stampa += "Tempo: " + to_string(int(tempo))+ "sec su 90sec";
    }
    else if(modalita == int(MOSSE))
    {
        stampa += "Mosse: " + to_string(numMosse) + " su 70";
    }

    al_draw_text(font, al_map_rgb(255,255,255), b->getX(), b->getY(), ALLEGRO_ALIGN_LEFT, stampa.c_str());
}

void Livello::datiLivello(const int& m,const int& n)
{
    modalita = MODALITA(m);
    numero = n;

    switch(numero)
    {
        case 1:
        numPalline = 35;
        numColori = 4;
            switch (modalita)
            {
                case 1:
                ranax = 504;
                ranay = 460;
                break;
            
                case 2:
                ranax = 482;
                ranay = 391;
                break;
                
                case 3:
                ranax = 588;
                ranay = 445;
                break;

                default:
                break;
            }
        break;


        case 2:
        numPalline = 45;
        numColori = 6;
            switch (modalita)
            {
                case 1:
                ranax = 484;
                ranay = 481;
                break;
            
                case 2:
                ranax = 516;
                ranay = 432;
                break;
                
                case 3:
                ranax = 579;
                ranay = 360;
                break;

                default:
                break;
            }
        break;

        default:
        break;
    }
}


int Livello::livello_base(Suono*& music ,const int& modalita, const int& numero)
{
    int numMosse = 0;
    int stampaBonus = 0;
    bool sceltaMenu = 0;
    int puntiAttuali = 0;
    bool redraw = 0;
    bool pausa = 0;

    datiLivello(modalita, numero);

    if(music->getMenu())
    {
        music->stopMenu();  
        music->playLevel1();  
    }

    
    
    event_queue.stop();
    serpy = new Serpente();
    gestoreSpari = new GestoreSpari();
    serpy->generaPalline(numPalline,numColori, modalita, numero);
    b = new BUFFER("../image/Livello_" + to_string(modalita) + "_" + to_string(numero) +".jpg");
    Rana rana(ranax,ranay);
    event_queue.start(60);
    int sizeCoord=serpy->getSizeCoordinate();
    ALLEGRO_EVENT ev; 
            
    b->stampaSfondo();
    menu = new Menu();

    double start = al_get_time();
    double end = start;
   
    while(gameOver(end-start,numMosse) && !serpy->empty() && serpy->getPosizionePrimaPallina()<sizeCoord && !sceltaMenu)
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
            
            stampaScrittaPunteggio(serpy->getPoint(), end-start, numMosse);
           
            rana.stampa(m.getX(), m.getY());  
            serpy->gestisciMovimento();

            gestoreSpari->collisioneSparo(*serpy);
            gestoreSpari->nelloSchermo(*b);
            
            gestoreSpari->stampa();       
            
            serpy->stampa();
            
            if(puntiGioco + serpy->getPoint() != puntiAttuali &&  puntiGioco + serpy->getPoint() !=0 && puntiGioco + serpy->getPoint() % 100 == 0 )
            {
                puntiAttuali = puntiGioco + serpy->getPoint();
                vita++;
                stampaBonus = 1;
            }
           
            if(stampaBonus!=0 && stampaBonus<40)
            {
                stampaBonus++;
                al_draw_text(font, al_map_rgb(0,0,0), b->getX()+b->getLunghezza()/2, b->getY()+b->getAltezza()/2, ALLEGRO_ALIGN_CENTER, "Vita Bonus: +1!");
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }

        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_P:
                    sceltaMenu = menu->menuPausa(music);
                    pausa = true;
                break;
                case ALLEGRO_KEY_SPACE:
                    if(pausa)
                    {  
                        pausa = false;
                        if(music->getMenu())
                        {
                            music->stopMenu();
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

    ESITO r = TORNAMENU;    
    if(!sceltaMenu)
    {
        music->stopLevel1();
        al_rest(0.5);

        if(serpy->empty())
        {
            stampaFinale(true,music);
            r = VAIAVANTI;
        }
            
        else
        {
            stampaFinale(false,music);
            if(vita > 0)
            {
                vita--;
                r = HAIPERSO;
            }
            music->playGameOver();
        }
    }
    
    endLivello(serpy->getPoint());
    return r;
}

void Livello::stampaFinale(const bool& vinto, Suono*& music)
{
    string imm;

    if(vinto)
    {  
        imm = "win.jpg";
        music->playWin();
    }
    else
    {    
        imm = "lost.png";
        music->playGameOver();
    }

    delete b;
    b = new BUFFER("../image/"+imm);
    b->stampaSfondo();
    b->stampa(1);
    al_flip_display();

    al_rest(7.1);
    music->playMenu();
}

void Livello::endLivello(const int& punti)
{
    puntiGioco+=punti;

    delete serpy; serpy = nullptr;
    delete gestoreSpari; gestoreSpari = nullptr;
}

bool Livello::gameOver(const double& tempo, const int& numMosse)
{
    switch (MODALITA(modalita))
    {
    case TEMPO:
        return (int(tempo)<=90);
        break;

    case MOSSE:
        return numMosse<=70;
    
    default:
        break;
    }

    return true;
}