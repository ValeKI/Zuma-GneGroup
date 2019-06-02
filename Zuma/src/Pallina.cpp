#include "../header/Pallina.h"

extern int wGlobal;
extern int hGlobal;


void Pallina::setColore(COLORE colore)
{
    string imm;
    switch(colore)
    {
        case(ROSSO):
            imm="Ball.png";
        break;

        case(BLU):
            imm="Ballblue.png";
        break;


        case(VERDE):
            imm="Ballgreen.png";
        break;


        case(ARANCIONE):
            imm="Ballorange.png";
        break;

        case(GIALLO):
            imm="Ballyellow.png";
        break;

        case(VIOLA):
            imm="Ballviolet.png";
        break;

    }


    distruggiLoad();
    setImmagine("../image/" + imm);
    ricreaLoad();
}

Pallina::Pallina(COLORE c, int pos):colore(c),posizione(pos),direzione(AVANTI),velocita(1), HitBox("../image/Ball.png", 0, 0, 0.036)
{
    setColore(colore);
}


Pallina::~Pallina()
{} 


void Pallina::avanza()
{
    if(direzione==AVANTI)
        posizione+=velocita;
    if(direzione==DIETRO)
        posizione-=velocita;
    // altrimenti FERMO
}


void Pallina::movimento(const pair<int, int>& c)
{
    setX(c.first);
    setY(c.second);
}


void Pallina::stop()
{
    direzione = FERMO;
}


void Pallina::inverti()
{
    if(direzione == AVANTI)
        direzione = DIETRO;
    else if(direzione == DIETRO)
        direzione = AVANTI;
}


COLORE Pallina::getColore() const
{
    return colore;
}



double Pallina::getPosizione() const
{
    return this->posizione;
}

void Pallina::setPosizione(double p)
{
    posizione = p;
}


DIREZIONE Pallina::getDirezione() const
{
    return direzione;
}


void Pallina::setDirezione(DIREZIONE dir)
{
    direzione = dir;
}

void Pallina::setVelocita(int x)
{
    velocita=x;
}


bool collegate(Pallina p1,Pallina p2,int d)
{   
    return (
    (getPosizione()-p.getPosizione() == d && getPosizione()-p.getPosizione() >=0)
    || 
    (p.getPosizione()-getPosizione() == d && p.getPosizione()-getPosizione() >=0));
}