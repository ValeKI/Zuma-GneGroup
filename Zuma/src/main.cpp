/*
    g++ *.cpp -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -o Zuma && ./Zuma
*/
#define IMMAGINE_SFONDO "image/Sfondo.jpg"
#include "../header/Sfondo.h"
#include "../header/Livello.h"
#include "../header/Suono.h"

// e' la width della 'risoluzione' scelta
int wGlobal=1024;

// e' la height della 'risoluzione' scelta
int hGlobal=768;


/*
    Gestisce la scelta dei menu e dei livelli
*/
void game()
{
    SFONDO sfondo;
    Menu* menu = new Menu();
    Livello* liv = new Livello();
    Suono* music = new Suono();
    
    // che livello scegli
    int numero = 0;

    // che modalita scegli
    int modalita = 0;
    
    // cosa succede/scegli dal livello
    int sceltaLivello = 0;
    
    music->playMenu();

    // schermata iniziale
    menu->zuma();

    while(true)
    {
        // switch modalita --- 0 torna al menu, 4 visualizza il tutorial, altro modalita livelli (CLASSICA, MOSSE, TEMPO)   
        switch (modalita)
        {
            case 0:
            // se il livello e' avviato dal menu si resettano i punteggi, le vite e la scelta del num del livello 
            liv->azzeraPunti();
            liv->resetVite();
            numero = 0;
            // dal menu principale si sceglie la modalità
            modalita = menu->menuPricipale(music); 
                break;

            // dopo il tutorial si torna al menu
            case 4:
            menu->tutorial();
            modalita = 0;
                break;

            default:
                switch (numero)
                {
                    // si sceglie il num del livello e alla prossima iterazione si vedrà qual e' la conseguenza
                    case 0:
                        numero = menu->menuLivelli();
                        break;
                    // rappresenta il torna indietro al menu principale
                    case 3:
                        modalita = 0;
                        numero = 0;
                        break;

                    default:
                        sceltaLivello = liv->livello_base(music,modalita,numero);
                        break;
                }
                break;
        }

        /* 
            TORNAMENU:
            nel caso il giocatore vince tutti i livelli oppure sceglie dal menu di pausa
            del livello di tornare al menu oppure finisce le vite

            VAIAVANTI:
            nel caso un giocatore vince un livello accede all'altro conservando punti e vite

            HAIPERSO:
            il gioco ricomincia con una vita in meno
        */
        switch (sceltaLivello)
        {
            case TORNAMENU:
            if(music->getMenu())
                al_rest(0.5);
            music->playMenu();
            modalita = 0; 
                break;

            case VAIAVANTI:
            numero++;
            if(numero == NUM_LIVELLI)
            { 
                modalita = 0;
                numero = 0;
            }
                break;
        
            case HAIPERSO:
            default:
                break;
        }
        
        sceltaLivello = 0;
    }
    
    delete menu;
    delete liv;
    delete music;
     
}

int init()
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
    if(!al_install_audio()){
      cerr << "failed to initialize audio!\n";
      return -1;
   }

   if(!al_init_acodec_addon()){
      cerr << "failed to initialize audio codecs!\n";
      return -1;
   }
	
   if (!al_reserve_samples(1)){
      cerr << "failed to reserve samples!\n";
      return -1;
   }
   return 0;
}

int main(int argc, char **argv)
{   
    /* ::wGlobal=800;
    ::hGlobal=600;  */

    if(init()==-1)
        return -1;
    
    game();
    return 0;
}

