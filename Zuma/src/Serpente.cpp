#include "../header/Serpente.h"

int coloriPalline;
vector<COLORE> tipi;

// restituisce il punteggio generato dagli scoppi
int Serpente::getPoint() const
{
    return point*10;
}

// verifica se due palline sono collegate
bool collegate(Pallina* p1,Pallina* p2,int d)
{   
    return (
    (p1->getPosizione()   -     p2->getPosizione() == d && p1->getPosizione()-p2->getPosizione() >=0)
    || 
    (p2->getPosizione()-p1->getPosizione() == d && p2->getPosizione()-p1->getPosizione() >=0));
}

// in caso di palline sovvrapposte porta la pallina più a destra (più vicino a 0) alla distanza giusta
void Serpente::fixVelocita()
{
    int sizeCoord = coordinate.size();
    for(int i=palline.size()-1;i>0;i--)
    {
        if(palline[i]->getPosizione()>=0 && palline[i]->getPosizione()<sizeCoord)
        {
            if(i!=0 && palline[i-1]->getPosizione()-palline[i]->getPosizione()<distanzaPalline)
            {
                palline[i-1]->setPosizione(palline[i]->getPosizione()+distanzaPalline+palline[i-1]->getVelocita());
            }
        }
    }

}

// legge il percorso e lo adatta allo schermo
void Serpente::caricaCoordinate(const int& modalita, const int& numero)
{
    ifstream in;
    string line;

    string percorso = "../Percorso/Percorso_"+ to_string(modalita) + "_" + to_string(numero) +".txt";

    in.open(percorso.c_str());
    int i=0,n1,n2;

    ALLEGRO_DISPLAY* display=al_get_current_display();
    int displayW= al_get_display_width(display);
    int displayH= al_get_display_height(display);
    int sx = displayW/wGlobal;
    int sy = displayH/hGlobal;
    int scale = min(sx,sy);


    while(getline(in,line))
    {
        string n;
        i=0;

        while(line[i]!='-')
        {
            n+=line[i++];
        }
        n1=atoi(n.c_str())*( (wGlobal*scale)/1024.);
        n="";
        i++;
        while(line[i]!='\0')
        {
            n+=line[i++];
        }
        n2=atoi(n.c_str())*( (hGlobal*scale)/768.);
        n="";

        coordinate.push_back(new pair<int,int>(n1,n2));
    }

    in.close();
}

// crea le palline in modo casuale
void Serpente::generaPalline(const int& num, const int& tipi, const int& modalita, const int& numero)
{
    caricaCoordinate(modalita, numero);
    srand(time(0));
    int pos=0;
    ::coloriPalline = tipi;
            
    for(int i=0; i<num; i++)
    {
        int x=rand()%tipi;
        //cout << "il rand " << x << endl;
        switch (x)
        {
            case 0:
                palline.push_back(new Pallina(ROSSO,pos));
            break;


            case 1:
                palline.push_back(new Pallina(BLU,pos));
            break;


            case 2:
                palline.push_back(new Pallina(VERDE,pos));
            break;


            case 3:
                palline.push_back(new Pallina(ARANCIONE,pos));
            break;

            case 4:
                palline.push_back(new Pallina(GIALLO,pos));
            break;

            case 5:
                palline.push_back(new Pallina(VIOLA,pos));
            break;
                
            default:
                break;
        }

        if(i==0)
            distanzaPalline = palline[0]->getLunghezza();

        pos-=distanzaPalline;
    } 
    
    palline.front()->movimento(*coordinate.at(palline.front()->getPosizione()));
}

// stampa le palline, ma prima applica un fix. Conta anche i colori ancora disponibili che serviranno a Rana
void Serpente::stampa()
{
    int p, sizeCoord=getSizeCoordinate();
    
    ::tipi.clear();

    if(!palline.empty())
    {
        fixVelocita();
        for(auto i:palline)
        { 
            if(find(::tipi.begin(), ::tipi.end(), i->getColore()) == ::tipi.end())
                ::tipi.push_back(i->getColore());
            i->Pallina::avanza();
            p=i->getPosizione();
            if(p>=0 && p<sizeCoord)
            {               
                i->Pallina::movimento(*coordinate[p]);
                i->stampa(1);
            }
        }
    }
    ::coloriPalline = tipi.size();    
}

Serpente::~Serpente()
{
    for(int i=0; i<palline.size(); i++)
        delete palline[i];

    for(int i=0; i<coordinate.size(); i++)
        delete coordinate[i];

    for(int i=0; i<coppiaSpari.size(); i++)
        delete coppiaSpari[i];

    delete finta;

}

// restituisce quante coordinate sono state lette
int Serpente::getSizeCoordinate()
{
    return coordinate.size();
}

/* 
    cerca se la posizione di una pallina è stata salvata in coppiaSpari, se a SINISTRA sarà l'indice del vector di palline se DESTRA l'indice di GestoreSpari
    se non la trova restituisce -2
*/
int Serpente::cercaIndiceCoppiaSpari(const int& indice, const int& quale)
{
    for (int i = 0; i < coppiaSpari.size(); i++)
        if ((coppiaSpari[i]->first == indice && quale == SINISTRA ) || (coppiaSpari[i]->second == indice && quale == DESTRA)  )
            return i;

    return -2;
}

// si occupa di creare una pallina immaginaria
Serpente::Serpente()
{
    finta = new Pallina (COLORE(0), 0);
}

// crea una pallina immaginaria, serve per inserire una pallina in testa
bool Serpente::collideInTesta(HitBox* obj)
{
    if(!palline.empty())
    {    
        finta->setPosizione(palline.front()->getPosizione() + distanzaPalline);
        if(finta->getPosizione()<coordinate.size())
        {
            finta->Pallina::movimento(*coordinate[finta->getPosizione()]);
            return(finta->collisione(obj));
        }
    }
    return false;
}

// se è vuoto il vector palline
bool Serpente::empty()
{
    return palline.empty();
}

// first e' di palline, second è uno sparo

//ATTENZIONE QUESTA FUNZIONE PUO' DANNEGGIARE LA TUA VISTA, TENERE LONTANA ALLA PORTATA DEI BAMBINI
// restituisce se uno sparo è stato inserito. Gestisce anche il suo inserimento
bool Serpente::toccaSparo(Pallina* sparo, int j)
{ 
    if(!palline.empty())
    {
        // cerca in coppiaSparo l'indice dello sparo j-esimo
        int indiceCS = cercaIndiceCoppiaSpari(j, DESTRA);
        
        // se non e' stato trovato
        if (indiceCS==-2)
        {
            /* 
                se collide con la pallina immaginaria in testa (-1)
                oppure se collide con una pallina con una posizione visibile
                ferma lo sparo e crea una coppiaSpari con l'indice della pallina del Serpente e dello sparo in GestoreSpari
            */
            for(int i=-1; i<int(palline.size()); i++)
            {
                if(i==-1 && collideInTesta(sparo)||
                i!=-1 && palline[i]->getPosizione()>0 && palline[i]->collisione(sparo) )
                {                
                    sparo->setVelocita(0);
                    coppiaSpari.push_back(new pair<int, int> (i,j));
                    break;
                }
            }
            
        }
        else // se esiste già una coppiaSpari con quell'indice dello sparo j
        {
            int primo = coppiaSpari[indiceCS]->first; // pallina in serpente
            int secondo = coppiaSpari[indiceCS]->second; // j

            // se primo non e' l'ultimo ne la pallina immaginaria all'inizio
            if(primo != palline.size()-1 && primo!=-1)
            {
                // vedi la distanza con la sua pallina precedente (verso 0)
                int differenzaPosizioni = palline[primo]->getPosizione() - palline[primo+1]->getPosizione();
                int v =  Pallina::VELOCITA * 20;
            
                if ( (differenzaPosizioni + v ) > distanzaPalline*2)
                    v =  distanzaPalline*2 - differenzaPosizioni+Pallina::VELOCITA;
                
                // se ci entra una pallina
                if (differenzaPosizioni >= distanzaPalline*2)
                {
                    // resetta la velocita' alle palline
                    cambiaDirVel(primo, AVANTI,Pallina::VELOCITA);
                    
                    // toglie la coppia spari
                    delete coppiaSpari[indiceCS];
                    coppiaSpari.erase(coppiaSpari.begin() + indiceCS);
                    
                    //inserisce lo sparo
                    sparo->setPosizione(palline[primo+1]->getPosizione()+distanzaPalline);
                    sparo->setVelocita(Pallina::VELOCITA);
                    palline.insert(palline.begin()+(primo+1),dynamic_cast<Pallina*>(sparo));   

                    // vede se scoppia le palline vicine
                    scoppiaPalline(primo+1);
                
                    return true;
                } 
                else // se non ci entra la pallina aumenta la velocita' di quelle a destra di primo per farla entrare
                    cambiaDirVel(primo, AVANTI,v);
            }
            // se tocca l'ultima pallina inserisce in coda
            else if (primo == palline.size()-1) 
            {
                
                delete coppiaSpari[indiceCS];
                coppiaSpari.erase(coppiaSpari.begin() + indiceCS);
                
                sparo->setPosizione(palline[primo]->getPosizione()-distanzaPalline);
                sparo->setVelocita(Pallina::VELOCITA);

                palline.push_back(dynamic_cast<Pallina*>(sparo));

                scoppiaPalline(palline.size()-1);
                return true;
            }
            // se tocca la pallina immaginaria inserisce in testa
            else
            {
                delete coppiaSpari[indiceCS];
                coppiaSpari.erase(coppiaSpari.begin() + indiceCS);
                
                sparo->setPosizione(palline[0]->getPosizione()+distanzaPalline);
                sparo->setVelocita(Pallina::VELOCITA);

                palline.insert(palline.begin(),dynamic_cast<Pallina*>(sparo));
                scoppiaPalline(0);
            
                return true;
            }   
        }
    }
    return false;
}

// restituisce la posizione della prima pallina, e se non ci sono palline restituisce la size delle coordinate * 5 (l'importante è che sia più grande)
int Serpente::getPosizionePrimaPallina()
{
    if(!palline.empty())
        return palline[0]->getPosizione();
    
    return getSizeCoordinate()*5;
}

// cambia sia direzione che velocita' alle palline che si trovano alla destra dell'i-esima (tendenzialmente 0)
void Serpente::cambiaDirVel(int i, DIREZIONE d, int v)
{
    if(i>=0 && i<=palline.size())
    {
         // alla prima pallina cambia direzione e velocita' 
        palline[i]->setDirezione(d);
        palline[i]->setVelocita(v);

        // controlla per ogni pallina successiva da n verso 0 (i-1) se sono collegate e cambia direzione e velocita
        for(;((i<palline.size())  && (i>0)&&(collegate(palline[i],palline[i-1],distanzaPalline)));i--)
        {
            palline[i]->setDirezione(d);
            palline[i]->setVelocita(v);
        }

         // per l'ultima pallina se collegata con la precedente da n verso 0 (i+1) cambia direzione e velocita
        if(i<palline.size() && collegate(palline[i],palline[i+1],distanzaPalline))
        {
            palline[i]->setDirezione(d);
            palline[i]->setVelocita(v);
        }
    
    }
}

// a partire dalla pallina p-esima vedi a destra e a sinistra le palline hanno lo stesso colore e falle esplodere
void Serpente::scoppiaPalline(int p)
{
    COLORE colore = palline[p]->getColore();
    int in=p;
    int fin=p;

    // vede a destra e sinistra
    for(;in>=0 && palline[in]->getColore()==colore ;in--);
    for(;fin<palline.size() && palline[fin]->getColore()==colore; fin++);

    // esplodono se la loro differenza è maggiore di 2
    in++;
    fin--;
    if(in!=fin && fin-in>=2)
    {
        for(int i=in; i<=fin && i>=0 && i<palline.size(); i++)
        {
            delete palline[i];
        } 

        palline.erase(palline.begin()+in,palline.begin()+(fin+1));
        point += (fin-in)+1;
    }
}

// ferma tutte le palline
void Serpente::stop()
{
    for(int i=0; i<palline.size(); i++)
        palline[i]->setDirezione(FERMO);
}

// gestisce il criterio con il quale le palline si muovono. In caso di palline precedentemente staccate che si riattacano verifica se possono esplodere, ma dello stesso colore
void Serpente::gestisciMovimento()
{
    stop();
    if(!palline.empty())
    {
        // tutte le palline del primo blocco del serpente vanno avanti, come se l'ultima pallina fosse spinta da qualcosa
        cambiaDirezioneADestraDi(palline.size()-1, AVANTI);

        for(int i=0;i<palline.size()-1;i++)
        {
            palline[i]->setVelocita(Pallina::VELOCITA);
            // se una pallina non è immischiata in uno sparo e non è collegata con la precedente (i+1) e hanno lo stesso colore
            if(cercaIndiceCoppiaSpari(i,SINISTRA)==-2 && !collegate(palline[i],palline[i+1],distanzaPalline)  && palline[i]->getColore() == palline[i+1]->getColore() )
            {
                // inseriscila tra le papabili per quanto si attaccano dei colori uguali che potrebbero esplodere
                if(find(coloreUguale.begin(), coloreUguale.end(), palline[i]) == coloreUguale.end())
                    coloreUguale.push_back(palline[i]);
                // fai muovere tutte quelle attaccate a i verso l'indietro del percorso
                cambiaDirezioneADestraDi(i,DIETRO);
                // fai stare ferme le palline precedenti a i (da i+1 fino a quanto sono attaccate)
                i=cambiaDirezioneASinistraDi(i+1,FERMO);
            }

            // se le palline precedentemente scollegate e con lo stesso colore si sono attaccate cerca di farle esplodere
            for(int j=0; j<coloreUguale.size(); j++)
                if(coloreUguale[j] == palline[i] && collegate(palline[i],palline[i+1],distanzaPalline))
                {    
                    scoppiaPalline(i);
                    coloreUguale.erase(coloreUguale.begin()+j);
                    // se questo svuota palline il livello si puo' considerare finito, così come questa funzione
                    if(palline.empty())
                        return;
                }
        }
    }
}

// setta la direzione data alle palline collegate a partire da 'in' verso destra (tendenzialmente 0)
int Serpente::cambiaDirezioneADestraDi(int in ,DIREZIONE d) // piu' grande
{
    int i=in;
    
    if(i>=0 && i<=palline.size())
    {  
        // alla prima pallina cambia direzione
        palline[i]->setDirezione(d);

        // controlla per ogni pallina successiva da n verso 0 (i-1) se sono collegate e cambia la direzione
        for(;((i<palline.size())  && (i>0) && (collegate(palline[i] ,palline[i-1], distanzaPalline)));i--)
            palline[i]->setDirezione(d);
    
        // per l'ultima pallina se collegata con la precedente da n verso 0 (i+1)
        if(i<palline.size()-1 && i>=0 && collegate(palline[i],palline[i+1],distanzaPalline))
            palline[i]->setDirezione(d);
        
    }

    return i;

}

// setta la direzione data alle palline collegate a partire da 'in' verso sinistra (tendenzialmente palline.size())
int Serpente::cambiaDirezioneASinistraDi(int fin, DIREZIONE d) // piu' piccolo
{
    int i=fin;

    if(i>=0 && i<=palline.size())
    {    
        // alla prima pallina cambia direzione
        palline[i]->setDirezione(d);

        // controlla per ogni pallina precedente da n verso 0 (i+1) se sono collegate e cambia la direzione
        for(;(  (i>=0)  && (i<palline.size()-1) &&(collegate(palline[i],palline[i+1],distanzaPalline)));i++)
            palline[i]->setDirezione(d);

        // per l'ultima pallina se collegata con la successiva da n verso 0 (i+1)
        if(i>0 && collegate(palline[i],palline[i-1],distanzaPalline))
            palline[i]->setDirezione(d);
    }
    return i;
}