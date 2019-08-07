#include "../header/Serpente.h"
#include <algorithm>

bool collegate(Pallina* p1,Pallina* p2,int d)
{   
    return (
    (p1->getPosizione()   -     p2->getPosizione() == d && p1->getPosizione()-p2->getPosizione() >=0)
    || 
    (p2->getPosizione()-p1->getPosizione() == d && p2->getPosizione()-p1->getPosizione() >=0));
}

void Serpente::fixVelocita()
{
    int sizeCoord = coordinate.size();
    for(int i=palline.size()-1;i>0;i--)
    {
        if(palline[i]->getPosizione()>=0 && palline[i]->getPosizione()<sizeCoord)
        {
            if(i!=0 && palline[i-1]->getPosizione()-palline[i]->getPosizione()<distanzaPalline)
            {
                cout << "aaa\n";
                palline[i-1]->setPosizione(palline[i]->getPosizione()+distanzaPalline);
            }
        }
    }

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
            distanzaPalline = palline[0]->getLunghezza();

        pos-=distanzaPalline;
    } 
    
    palline.front()->movimento(*coordinate.at(palline.front()->getPosizione()));
}

void Serpente::stampa()
{
    int p, sizeCoord=getSizeCoordinate();
    
    fixVelocita();
    for(auto i:palline)
    { 
        i->Pallina::avanza();
        p=i->getPosizione();
        if(p>=0 && p<sizeCoord)
        {               
            i->Pallina::movimento(*coordinate[p]);
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

    for(int i=0; i<coppiaSpari.size(); i++)
        delete coppiaSpari[i];

    delete finta;
}

int Serpente::getSizeCoordinate()
{
    return coordinate.size();
}

int Serpente::cercaIndice(int c, bool first)
{
    for (int i = 0; i < coppiaSpari.size(); i++)
        if ((coppiaSpari[i]->first == c && first ) || (coppiaSpari[i]->second == c && !first)  )
        {
            return i;
        }
    return -2;
}

Serpente::Serpente()
{
    finta = new Pallina (COLORE(0), 0);
}

bool Serpente::collideInTesta(HitBox* obj)
{
    finta->setPosizione(palline.front()->getPosizione() + distanzaPalline);
    if(finta->getPosizione()<coordinate.size())
    {
        finta->Pallina::movimento(*coordinate[finta->getPosizione()]);
        return(finta->collisione(obj));
    }
    return false;
}

bool Serpente::empty()
{
    return palline.empty();
}

bool Serpente::toccaSparo(Pallina* sparo, int j)
{ 

    int indiceCS = cercaIndice(j, false);
    
    if (indiceCS==-2)
    {
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
    else 
    {
 

        int primo = coppiaSpari[indiceCS]->first;
        int secondo = coppiaSpari[indiceCS]->second;

        if(primo != palline.size()-1 && primo!=-1)
        {
           

            int differenzaPosizioni = palline[primo]->getPosizione() - palline[primo+1]->getPosizione();
            int v =  Pallina::VELOCITA * 20;
        

            if ( (differenzaPosizioni + v ) > distanzaPalline*2)
                v =  distanzaPalline*2 - differenzaPosizioni+Pallina::VELOCITA;
            
            if (differenzaPosizioni >= distanzaPalline*2)
            {
                cambiaDirVel(primo, AVANTI,Pallina::VELOCITA);
                
                delete coppiaSpari[indiceCS];
                coppiaSpari.erase(coppiaSpari.begin() + indiceCS);
                
                sparo->setPosizione(palline[primo+1]->getPosizione()+distanzaPalline);
                sparo->setVelocita(Pallina::VELOCITA);

                palline.insert(palline.begin()+(primo+1),dynamic_cast<Pallina*>(sparo));   

                scoppiaPalline(primo+1);

                return true;
            } 
            else 
            {
                cambiaDirVel(primo, AVANTI,v);
            }

        }
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

void Serpente::scoppiaPalline(int p)
{
    COLORE colore = palline[p]->getColore();
    int in=p;
    int fin=p;

    for(;in>=0 && int(palline[in]->getColore())==int(colore) ;in--);
    for(;fin<palline.size() && int(palline[fin]->getColore())==int(colore); fin++);
    
    in++;
    fin--;
    if(in!=fin && fin-in>=2)
    {
        for(int i=in; i<=fin; i++)
        {
            delete palline[i];
        } 

        palline.erase(palline.begin()+in,palline.begin()+(fin+1));
    }


}

void Serpente::stop()
{
    for(int i=0; i<palline.size(); i++)
    {
        palline[i]->setDirezione(FERMO);
    }
}


void Serpente::gestisciMovimento()
{
    stop();
    if(!palline.empty())
    {
        cambiaDirezioneADestraDi(palline.size()-1, AVANTI);
        for(int i=0;i<palline.size()-1;i++)
        {
            palline[i]->setVelocita(Pallina::VELOCITA);
            if(cercaIndice (i,true)==-2 && !collegate(palline[i],palline[i+1],distanzaPalline)  && palline[i]->getColore() == palline[i+1]->getColore() )
            {
                if(find(coloreUguale.begin(), coloreUguale.end(), palline[i]) == coloreUguale.end())
                    coloreUguale.push_back(palline[i]);
                cambiaDirezioneADestraDi(i,DIETRO);
                i=cambiaDirezioneASinistraDi(i+1,FERMO);
            }

            for(int j=0; j<coloreUguale.size(); j++)
                if(coloreUguale[j] == palline[i] && collegate(palline[i],palline[i+1],distanzaPalline))
                {    
                    scoppiaPalline(i);
                    coloreUguale.erase(coloreUguale.begin()+j);
                }
        }
    }
}

int Serpente::cambiaDirezioneADestraDi(int in ,DIREZIONE d) // piu' grande
{
    int i=in;
    int j=0;

    if(i>=0 && i<=palline.size())
    {  
        palline[i]->setDirezione(d);

        for(;((i<palline.size())  && (i>0) && (collegate(palline[i] ,palline[i-1], distanzaPalline)));i--)
        {
            j++;
            palline[i]->setDirezione(d);
        }
        if(i<palline.size()-1 && i>=0 && collegate(palline[i],palline[i+1],distanzaPalline))
            palline[i]->setDirezione(d);
        
    }

    return i;

}

int Serpente::cambiaDirezioneASinistraDi(int fin, DIREZIONE d) // piu' piccolo
{
    int i=fin;

    if(i>=0 && i<=palline.size())
    {    
        palline[i]->setDirezione(d);

        for(;(  (i>=0)  && (i<palline.size()-1) &&(collegate(palline[i],palline[i+1],distanzaPalline)));i++)
            palline[i]->setDirezione(d);

        if(i>0 && collegate(palline[i],palline[i-1],distanzaPalline))
            palline[i]->setDirezione(d);
    }
    return i;
}