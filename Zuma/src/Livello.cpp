#include "../header/Livello.h"

extern int wGlobal;
extern int hGlobal;

const int VELOCITAGIOCO = 60;

const int BONUSVITA = 800;
const int TEMPOADISP = 90;
const int NUMMOSSE = 70;

const int NUMPALLINE_1 = 35;
const int NUMPALLINE_2 = 45;

const int NUMCOLORI_1 = 4;
const int NUMCOLORI_2 = 6;

const int RANAX_1_1 = 504; const int RANAY_1_1 = 460;
const int RANAX_1_2 = 484; const int RANAY_1_2 = 481;

const int RANAX_2_1 = 482; const int RANAY_2_1 = 391;
const int RANAX_2_2 = 516; const int RANAY_2_2 = 432;

const int RANAX_3_1 = 588; const int RANAY_3_1 = 445;
const int RANAX_3_2 = 579; const int RANAY_3_2 = 360;

// costruttori

// carica il font
Livello::Livello():Schermata()
{
    caricaFont();
}

// distruttore

// se non si è distrutto qualcosa se ne occupa
Livello::~Livello()
{
    if(serpy!=nullptr)
        delete serpy;

    if(gestoreSpari!=nullptr)
        delete gestoreSpari;

    if(menu!=nullptr)
        delete menu; 
}

// funzioni protected

// stampa hai vinto-hai perso e lancia il suono
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

/*
    inizializza i dati a secondo del livello scelto
    si possono modificare:
        - il numero delle palline
        - quanti colori di palline si vogliono (da 1 a 6)
        - la posizione della rana
*/
void Livello::datiLivello(const int& m,const int& n)
{
    modalita = MODALITA(m);
    numero = n;

    switch(numero)
    {
        case 1:
        numPalline = NUMPALLINE_1;
        numColori = NUMCOLORI_1;
            switch (modalita)
            {
                case 1:
                ranax = RANAX_1_1;
                ranay = RANAY_1_1;
                break;
            
                case 2:
                ranax = RANAX_2_1;
                ranay = RANAY_2_1;
                break;
                
                case 3:
                ranax = RANAX_3_1;
                ranay = RANAY_3_1;
                break;

                default:
                break;
            }
        break;


        case 2:
        numPalline = NUMPALLINE_2;
        numColori = NUMCOLORI_2;
            switch (modalita)
            {
                case 1:
                ranax = RANAX_1_2;
                ranay = RANAY_1_2;
                break;
            
                case 2:
                ranax = RANAX_2_2;
                ranay = RANAY_2_2;
                break;
                
                case 3:
                ranax = RANAX_3_2;
                ranay = RANAY_3_2;
                break;

                default:
                break;
            }
        break;

        default:
        break;
    }
}

// stampa la scritta del punteggio secondo la mod e il liv
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
            stampa+= "Tempo";
        break;
        
        default: 
        break;
    }

    stampa += "     Liv: " + to_string(numero) + "     Vita: " + to_string(vita) + "     Punti: " + to_string(puntiGioco + p) + "     Pausa: premi p     ";

    if(modalita == int(TEMPO))
        stampa += "Tempo: " + to_string(int(tempo))+ "sec su " + to_string(TEMPOADISP) + " sec";
    else if(modalita == int(MOSSE))
        stampa += "Mosse: " + to_string(numMosse) + " su " + to_string(NUMMOSSE);
    
    al_draw_text(font, al_map_rgb(255,255,255), b->getX(), b->getY(), ALLEGRO_ALIGN_LEFT, stampa.c_str());
}

void Livello::endLivello()
{
    puntiGioco+=serpy->getPoint();

    delete serpy; serpy = nullptr;
    delete gestoreSpari; gestoreSpari = nullptr;
}

// sceglie i criteri in piu' per chiudere un livello
bool Livello::gameOver(const double& tempo, const int& numMosse)
{
    switch (modalita)
    {
    case TEMPO:
        return (int(tempo)<=TEMPOADISP);
        break;

    case MOSSE:
        return numMosse<=NUMMOSSE;
    
    default:
        break;
    }

    return true;
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

/* 
    gestisce gli eventi del livello e restistuisce l'esito
*/
int Livello::livello_base(Suono*& music ,const int& modalita, const int& numero)
{
    // il numero delle mosse/palline usate nel livello
    int numMosse = 0;
    
    // serve per stampare la scritta del bonus della vita
    int stampaBonus = 0;

    // se si scegli di andare al menu
    bool sceltaMenu = 0;

    // quanti punti si avevano al momento del bonus
    int puntiAttuali = 0;

    // se disegnare il livello
    bool redraw = 0;

    // se richiesta la pausa
    bool pausa = 0;

    datiLivello(modalita, numero);

    if(music->getMenu())
    {
        music->stopMenu();  
        music->playLevel1();  
    }

    // inizializzazione dell'event_queue, Serpente, Buffer, Rana
    event_queue.stop();
    serpy = new Serpente();
    gestoreSpari = new GestoreSpari();
    serpy->generaPalline(numPalline,numColori, modalita, numero);
    b = new BUFFER("../image/Livello_" + to_string(modalita) + "_" + to_string(numero) +".jpg");
    Rana rana(ranax,ranay);
    event_queue.start(VELOCITAGIOCO);

    // quante sono le coordinate del livello, serve per identificare quando la prima pallina finisce il percorso
    int sizeCoord=serpy->getSizeCoordinate();
    ALLEGRO_EVENT ev; 
            
    b->stampaSfondo();
    // menu usato per stampare la schermata di pausa
    menu = new Menu();

    // tempo di inizio del livello
    double start = al_get_time();

    // tempo di fine/in corso
    double end = start;
   
    /* 
        il livello continua fino a quando:
            non succede una fine particolare a seconda della modalita (finisce tempo/mosse)
            non ci sono più palline
            si sceglie dal menu di pausa di tornare al menu principale
    */
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
            // riprende la musica
            if(pausa)
            { 
                pausa = false;
                if(music->getMenu())
                {
                    music->stopMenu();
                    music->playLevel1();
                }
            }
            else // se sparo col mouse
            {
                numMosse++;
                gestoreSpari->inserisciSparo(rana.getPallina());
            }
        }

        if(redraw && event_queue.empty())
        {  
            redraw = false;
                    
            b->stampa(1);    
            
            stampaScrittaPunteggio(serpy->getPoint(), end-start, numMosse);
           
            rana.stampa(m.getX(), m.getY());

            // gestisce prima il Serpente e poi gli spari  
            serpy->gestisciMovimento();
            gestoreSpari->collisioneSparo(*serpy);
            gestoreSpari->nelloSchermo(*b);
            
            gestoreSpari->stampa();       
            serpy->stampa();
            
            // bonus vite
            if(puntiGioco + serpy->getPoint() != puntiAttuali &&  puntiGioco + serpy->getPoint() !=0 && puntiGioco + serpy->getPoint() % BONUSVITA == 0 )
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
            redraw = true;
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
    
    endLivello();
    return r;
}

