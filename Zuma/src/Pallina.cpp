#include "../header/Pallina.h"

extern int wGlobal;
extern int hGlobal;


Pallina::Pallina(COLORE c, int pos):colore(c),posizione(pos),direzione(AVANTI),velocita(1), HitBox("../image/Ball.png", 0, 0, 0.026)
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

            //cout << "Imm e' " << imm << endl;

    distruggiLoad();
    setImmagine("../image/" + imm);
    ricreaLoad();
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
   // cout << c.first << " " << ((displayW-(wGlobal * scale))/2 ) << endl;
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



int Pallina::getPosizione() const
{
    return this->posizione;
}


DIREZIONE Pallina::getDirezione() const
{
    return direzione;
}


void Pallina::setDirezione(DIREZIONE dir)
{
    direzione = dir;
}