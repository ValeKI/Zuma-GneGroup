#include "../header/Serpente.h"

bool collegate(Pallina* p1,Pallina* p2,int d)
{   
    return (
    (p1->getPosizione()   -     p2->getPosizione() == d && p1->getPosizione()-p2->getPosizione() >=0)
    || 
    (p2->getPosizione()-p1->getPosizione() == d && p2->getPosizione()-p1->getPosizione() >=0));
}


void Serpente::caricaCoordinate()
{
    ifstream in;
    string line;
    in.open("../Percorso/Percorso_0.txt");
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



void Serpente::generaPalline(int num, int tipi)
{
    caricaCoordinate();
    srand(time(0));
    int pos=0;
            
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
            distanzaPalline = palline[0]->getStampaL();

        pos-=distanzaPalline;
    } 
    
    palline.front()->movimento(*coordinate.at(palline.front()->getPosizione()));
}

void Serpente::stampa()
{
    int p, sizeCoord=getSizeCoordinate();
    
    //gestisciMovimento();

    
    for(auto i:palline)
    {
        

        i->avanza();
        p=i->getPosizione();
                        
        if(p>=0 && p<sizeCoord)
        {
            i->movimento(*coordinate[p]);
            i->stampa(1);
        }
    }
            
}

Serpente::~Serpente()
{
    for(int i=0; i<palline.size(); i++)
        delete palline[i];
            
    for(int i=0; i<coordinate.size(); i++)
        delete coordinate[i];
}

int Serpente::getSizeCoordinate()
{
    return coordinate.size();
}
bool Serpente::cercaIndice(int c, bool first)
{
    for (auto i: coppiaSpari)
        if ((i->first == c && first ) || (i->second == c && !first)  )
            return true;
    return false;
}
bool Serpente::toccaSparo(Pallina* sparo, int j)
{ 
    if (!cercaIndice(j, false))
    {
        for(int i=0; i<palline.size(); i++)
         if(!cercaIndice(i, true)&&  palline[i]->getPosizione()>0 && palline[i]->collisione(sparo) )
        {
            coppiaSpari.push_back(new pair<int, int> (i,j));
            return true;
            //inserimento           
        } 
    } 
    return false;
}

int Serpente::getPosizionePrimaPallina()
{
    return palline[0]->getPosizione();
}

void Serpente::cambiaDirVel(int i, DIREZIONE d, int v)
{
    if(i>=0 && i<=palline.size())
    {
        palline[i]->setDirezione(d);
        palline[i]->setVelocita(v);

        for(;((i<palline.size())  && (i>0)&&(collegate(palline[i],palline[i-1],distanzaPalline)));i--)
        {
            palline[i]->setDirezione(d);
            palline[i]->setVelocita(v);
        }

        if(i<palline.size() && collegate(palline[i],palline[i+1],distanzaPalline))
        {
            palline[i]->setDirezione(d);
            palline[i]->setVelocita(v);
        }
    
    }
}





void Serpente::gestisciMovimento()
{
    for(int i=cambiaDirezioneADestraDi(palline.size()-1, AVANTI);i<palline.size()-1;i++)
        if(!collegate(palline[i],palline[i+1],distanzaPalline) && palline[i]->getColore() == palline[i+1]->getColore() )
        {
            cambiaDirezioneADestraDi(i,DIETRO);
            i=cambiaDirezioneASinistraDi(i+1,FERMO);
        }
    
    for(int i = 0; i < coppiaSpari.size(); i++)
    {
        int primo = coppiaSpari[i]->first;
        int secondo = coppiaSpari[i]->second;

        if(primo != coppiaSpari.size()-1)
    {
        int differenzaPosizioni = palline[primo]->getPosizione() - palline[primo+1]->getPosizione();
        



        int v =  Pallina::VELOCITA * 3;
        
        if ( (differenzaPosizioni + v ) > distanzaPalline)
            v = differenzaPosizioni - distanzaPalline;
        


        if (differenzaPosizioni == distanzaPalline)
        {
            coppiaSpari.erase(coppiaSpari.begin() + i--);

             
        } 
        else cambiaDirVel(primo, AVANTI,v);


    }


    }    
}

int Serpente::cambiaDirezioneADestraDi(int in ,DIREZIONE d) // piu' grande
{
    int i=in;

    //cout << "A destra di " << i << endl;

    if(i>=0 && i<=palline.size())
    {    palline[i]->setDirezione(d);

    for(;((i<palline.size())  && (i>0)&&(collegate(palline[i],palline[i-1],distanzaPalline)));i--)
        palline[i]->setDirezione(d);

    if(i<palline.size() && collegate(palline[i],palline[i+1],distanzaPalline))
        palline[i]->setDirezione(d);
    
    }
    
    return i;

}

int Serpente::cambiaDirezioneASinistraDi(int fin, DIREZIONE d) // piu' piccolo
{
    int i=fin;

    //cout << "A sinistra di " << i << endl;

    if(i>=0 && i<=palline.size())
    {    palline[i]->setDirezione(d);

    for(;(  (i>=0)  && (i<palline.size()-1)&&(collegate(palline[i],palline[i+1],distanzaPalline)));i++)
        palline[i]->setDirezione(d);

    if(i>0 && collegate(palline[i],palline[i-1],distanzaPalline))
        palline[i]->setDirezione(d);
    }
    return i;
}