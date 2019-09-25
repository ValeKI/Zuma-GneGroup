#include "../header/Pallina.h"

extern int wGlobal;
extern int hGlobal;

// costruttori

Pallina::Pallina(COLORE c, int pos):colore(c),posizione(pos),direzione(AVANTI),velocita(VELOCITAPALLINE), HitBox("../image/Ball.png", 0, 0, 0.036)
{
    setColore(colore);
}

// set

void Pallina::setColore(const COLORE& colore)
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

void Pallina::setDirezione(const DIREZIONE& dir)
{
    direzione = dir;
}

void Pallina::setPosizione(const double& p)
{
    posizione = p;
}

void Pallina::setVelocita(const int& x)
{
    velocita=x;
}

// get

COLORE Pallina::getColore() const
{
    return colore;
}

DIREZIONE Pallina::getDirezione() const
{
    return direzione;
}

double Pallina::getPosizione() const
{
    return this->posizione;
}

int Pallina::getVelocita() const
{
    return velocita;
}

// funzioni

void Pallina::avanza()
{
    if(direzione==AVANTI)
        posizione+=velocita;
    if(direzione==DIETRO)
        posizione-=velocita;
    // altrimenti FERMO
}

void Pallina::invertiDirezione()
{
    if(direzione == AVANTI)
        direzione = DIETRO;
    else if(direzione == DIETRO)
        direzione = AVANTI;
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




